#include "c_scene_manager.h"

c_scene_manager::c_scene_manager() {
    // Initialize to null pointer
    root = NULL;
}

c_scene_manager::~c_scene_manager() {
    // De-allocate all of the scene objects
    for (size_t i = 0; i < scene_objects.size(); ++i) {
        delete scene_objects[i];
    }

    delete root;
}

void c_scene_manager::add_to_scene(const c_tikz_obj& source) {
    c_tikz_obj * scene_object = source.clone();
    scene_objects.push_back(scene_object);
}

void c_scene_manager::render_to_file(std::string filename, const c_camera& cam) {

    std::vector<c_tikz_obj*> screen_objects(scene_objects.size());

    // Project everything
    for (size_t i = 0; i < scene_objects.size(); ++i) {
        screen_objects[i] = scene_objects[i]->project(cam);
    }

    std::ofstream sstm;
    sstm.open(filename.c_str());

    sstm << "\\begin{tikzpicture}\n";

    for (size_t i = 0; i < screen_objects.size(); ++i) {
        sstm << "   " << screen_objects[i]->write();
    }

    sstm << "\\end{tikzpicture}";

    sstm.close();

    // De-allocate all of the screen objects
    for (size_t i = 0; i < screen_objects.size(); ++i) {
        delete screen_objects[i];
    }
    screen_objects.resize(0);
}

void c_scene_manager::render_3d_to_file(std::string filename, const c_camera& eye1, const c_camera& eye2) {

    std::ofstream sstm;
    sstm.open(filename.c_str());

    sstm << "\\begin{tikzpicture}\n";

    sstm << "  \\draw (0, 0)--(0,0.01); \n";

    sstm << "\\begin{scope}[transparency group, opacity=0.7]\n";

    std::vector<c_tikz_obj*> screen_objects(scene_objects.size());

    // Project everything for the first eye
    for (size_t i = 0; i < scene_objects.size(); ++i) {
        screen_objects[i] = scene_objects[i]->project(eye1);
    }

    // Write to file
    for (size_t i = 0; i < screen_objects.size(); ++i) {
        screen_objects[i]->color[0] = "red";
        sstm << "   " << screen_objects[i]->write();
    }

    sstm << "\\end{scope}\n";

    sstm << "\\begin{scope}[transparency group, opacity=0.7]";

    // De-allocate all of the screen objects
    for (size_t i = 0; i < screen_objects.size(); ++i) {
        delete screen_objects[i];
    }

    screen_objects.resize(scene_objects.size());

    // Project everything for the second eye
    for (size_t i = 0; i < scene_objects.size(); ++i) {
        screen_objects[i] = scene_objects[i]->project(eye2);
    }

    // Write to file
    for (size_t i = 0; i < screen_objects.size(); ++i) {
        screen_objects[i]->color[0] = "cyan";
        screen_objects[i]->add_param("xshift=0in");
        sstm << "  " << screen_objects[i]->write();
    }

    // De-allocate all of the screen objects
    for (size_t i = 0; i < screen_objects.size(); ++i) {
        delete screen_objects[i];
    }
    screen_objects.resize(0);

    sstm << "\\end{scope}\n";

    sstm << "\\end{tikzpicture}";

    sstm.close();

}

void c_scene_manager::render_cross_to_file(std::string filename, const c_camera& eye_1, const c_camera& eye_2) {

    std::ofstream sstm;
    sstm.open(filename.c_str());

    sstm << "\\begin{tikzpicture}\n";

    sstm << "  \\draw (0, 0)--(0,0.01); \n";

    std::vector<c_tikz_obj*> screen_objects(scene_objects.size());

    // Project everything for the first eye
    for (size_t i = 0; i < scene_objects.size(); ++i) {
        screen_objects[i] = scene_objects[i]->project(eye_1);
    }

    // Write to file
    for (size_t i = 0; i < screen_objects.size(); ++i) {
        screen_objects[i]->add_param("xshift=0in");
        sstm << "   " << screen_objects[i]->write();
        sstm << "\n";
    }

    // De-allocate all of the screen objects
    for (size_t i = 0; i < screen_objects.size(); ++i) {
        delete screen_objects[i];
    }

    screen_objects.resize(scene_objects.size());

    // Project everything for the second eye
    for (size_t i = 0; i < scene_objects.size(); ++i) {
        screen_objects[i] = scene_objects[i]->project(eye_2);
    }

    // Write to file
    for (size_t i = 0; i < screen_objects.size(); ++i) {
        screen_objects[i]->add_param("xshift=4in");
        sstm << "  " << screen_objects[i]->write();
        sstm << "\n";
    }

    // De-allocate all of the screen objects
    for (size_t i = 0; i < screen_objects.size(); ++i) {
        delete screen_objects[i];
    }

    sstm << "\\end{tikzpicture}";

    sstm.close();

}

void c_scene_manager::compile_bsp() {

    delete root;

    // Clone all the scene objects for the tree
    std::vector<c_tikz_obj*> objs_for_processing(scene_objects.size());
    for (size_t i = 0; i < scene_objects.size(); ++i) {
        objs_for_processing[i] = scene_objects[i]->clone();
    }

    root = new c_tree_node(objs_for_processing, 0);

}

void c_scene_manager::render_bsp(std::string filename, c_camera& cam) {

    if (root == NULL) {
        compile_bsp();
    }

    std::ofstream sstm;
    sstm.open(filename.c_str());

    sstm << "\\begin{tikzpicture}\n";

    root->project(cam);
    root->render(sstm, cam);

    sstm << "\\end{tikzpicture}\n";

    sstm.close();

}

void c_scene_manager::light(c_point& sun) {

    c_point norm_sun = sun.normalize();

    c_polygon plane;
    c_point normal;

    real max_l, min_l;
    max_l = 0;
    min_l = 100;

    std::vector<real> devs(scene_objects.size());

    for (size_t i = 0; i < scene_objects.size(); ++i) {
        if (scene_objects[i]->can_light()) {
            plane = scene_objects[i]->get_plane();
            normal = plane.normal();
            devs[i] = (normal*norm_sun+1)/2;
            if (devs[i] > max_l) {
                max_l = devs[i];
            }
            if (devs[i] < min_l) {
                min_l = devs[i];
            }
        }
    }

    //if (max_l == min_l) {
        min_l = 0;
        max_l = 1;
    //}

    for (size_t i = 0; i < scene_objects.size(); ++i) {
        if (scene_objects[i]->can_light()) {
            scene_objects[i]->light[0] = (int) 100*devs[i];
        }
    }



}

void c_scene_manager::plot(real (*func)(real x, real y), real start_x, real start_y,  real end_x, real end_y, size_t xdim, size_t ydim) {

    std::vector< std::vector<real> > vals(xdim, std::vector<real>(ydim));

    std::vector<real> x(xdim);
    std::vector<real> y(ydim);

    // Initialize the domain
    for (size_t i = 0; i < xdim; ++i) {
        x[i] = start_x + ((real) i)*(end_x - start_x)/((real) xdim);
    }
    for (size_t i = 0; i < ydim; ++i) {
        y[i] = start_y + ((real) i)*(end_y - start_y)/((real) ydim);
    }

    // Compute the function
    for (size_t i = 0; i < xdim; ++i) {
        for (size_t j = 0; j < ydim; ++j) {
            vals[i][j] = func(x[i], y[j]);
        }
    }

    // Add all the right polygons, 2*(N-1)*(M-1) of them!
    c_point a, b, c, d;
    c_polygon poly1, poly2;

    std::vector< std::vector< c_tikz_obj*> > temp_polys(2*(xdim-1), std::vector<c_tikz_obj*>(ydim-1));
    for (size_t i = 0; i < xdim-1; ++i) {
        for (size_t j = 0; j < ydim-1; ++j) {
            a.x = x[i];
            a.y = y[j];
            a.z = vals[i][j];

            b.x = x[i];
            b.y = y[j+1];
            b.z = vals[i][j+1];

            c.x = x[i+1];
            c.y = y[j];
            c.z = vals[i+1][j];

            d.x = x[i+1];
            d.y = y[j+1];
            d.z = vals[i+1][j+1];

            poly1.a = b;
            poly1.b = c;
            poly1.c = a;

            poly2.a = d;
            poly2.b = c;
            poly2.c = b;

            temp_polys[2*i][j] = poly1.clone();
            temp_polys[2*i+1][j] = poly2.clone();
        }
    }

    // Add them to the scene and light them properly
    c_point normal;
    for (size_t i = 0; i < xdim-1; ++i) {
        for (size_t j = 0; j < ydim-1; ++j) {
            add_to_scene(*temp_polys[2*i][j]);
            add_to_scene(*temp_polys[2*i+1][j]);
            delete temp_polys[2*i][j];
            delete temp_polys[2*i+1][j];
        }
    }
}

void c_scene_manager::axis(real x, real y, real z) {
    c_line linex(0, 0, 0, x, 0, 0);
    c_line liney(0, 0, 0, 0, y, 0);
    c_line linez(0, 0, 0, 0, 0, z);

    linex.add_param("thick");
    liney.add_param("thick");
    linez.add_param("thick");

    add_to_scene(linex);
    add_to_scene(liney);
    add_to_scene(linez);

}

void c_scene_manager::add_box(real sx, real sy, real sz, real ex, real ey, real ez, vector<string> params, string color) {

    add_rectangle_z(ex, ey, sx, sy, sz, params, color, true);
    add_rectangle_y(sx, sz, ex, ez, sy, params, color, false);
    add_rectangle_x(sy, sz, ey, ez, sx, params, color, false);

    add_rectangle_z(sx, sy, ex, ey, ez, params, color, false);
    add_rectangle_y(ex, ez, sx, sz, ey, params, color, true);
    add_rectangle_x(ey, ez, sy, sz, ex, params, color, true);

}

void c_scene_manager::add_rectangle_z(real sx, real sy, real ex, real ey, real z, vector<string> params, string color, bool flip) {

    c_point point1(sx, sy, z);
    c_point point2(sx, ey, z);
    c_point point3(ex, ey, z);
    c_point point4(ex, sy, z);

    std::vector<c_point> points(4);
    points[0] = point1;
    points[1] = point2;
    points[2] = point3;
    points[3] = point4;

    if (flip) {
        points[1] = points[3];
        points[3] = point2;
    }

    add_fan(points, params, color);

}

void c_scene_manager::add_rectangle_y(real sx, real sz, real ex, real ez, real y, vector<string> params, string color, bool flip) {

    c_point point1(sx, y, sz);
    c_point point2(sx, y, ez);
    c_point point3(ex, y, ez);
    c_point point4(ex, y, sz);

    std::vector<c_point> points(4);
    points[0] = point1;
    points[1] = point2;
    points[2] = point3;
    points[3] = point4;

    if (flip) {
        points[1] = points[3];
        points[3] = point2;
    }

    add_fan(points, params, color);

}

void c_scene_manager::add_rectangle_x(real sy, real sz, real ey, real ez, real x, vector<string> params, string color, bool flip) {

    c_point point1(x, sy, sz);
    c_point point2(x, ey, sz);
    c_point point3(x, ey, ez);
    c_point point4(x, sy, ez);

    std::vector<c_point> points(4);
    points[0] = point1;
    points[1] = point2;
    points[2] = point3;
    points[3] = point4;

    if (flip) {
        points[1] = points[3];
        points[3] = point2;
    }

    add_fan(points, params, color);

}

void c_scene_manager::add_fan(std::vector<c_point> points, vector<string> params, string color) {

    if (points.size() < 3) {
        return;
    }

    c_polygon polygon;

    polygon.a = points[0];
    polygon.b = points[1];
    polygon.c = points[2];

    polygon.color[0] = color;
    polygon.add_params(params);

    add_to_scene(polygon);

    for (size_t i = 3; i < points.size(); ++i) {
        polygon.a = points[0];
        polygon.b = points[i-1];
        polygon.c = points[i];

        add_to_scene(polygon);

    }

}
