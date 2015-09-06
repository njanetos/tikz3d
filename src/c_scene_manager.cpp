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

    sstm << "\\draw (0, 0)--(0,0.01);";

    for (size_t i = 0; i < screen_objects.size(); ++i) {
        sstm << "   " << screen_objects[i]->write();
        sstm << "\n";
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
        screen_objects[i]->color[0] = "green";
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
        screen_objects[i]->color[0] = "red";
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

    sstm << "  \\draw (0, 0)--(0,0.01); \n";

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

    for (size_t i = 0; i < scene_objects.size(); ++i) {
        if (scene_objects[i]->can_light()) {
            scene_objects[i]->light[0] = (int) 100*(devs[i]-min_l)/(max_l - min_l);
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
