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

void c_scene_manager::add_to_scene(c_tikz_obj *source) {
    c_tikz_obj * scene_object = source->clone();
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

    std::vector<c_tikz_obj*> screen_objects(scene_objects.size());

    // Project everything for the first eye
    for (size_t i = 0; i < scene_objects.size(); ++i) {
        screen_objects[i] = scene_objects[i]->project(eye1);
    }

    // Write to file
    for (size_t i = 0; i < screen_objects.size(); ++i) {
        screen_objects[i]->add_param("color=green");
        screen_objects[i]->add_param("opacity=0.5");
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
        screen_objects[i] = scene_objects[i]->project(eye2);
    }

    // Write to file
    for (size_t i = 0; i < screen_objects.size(); ++i) {
        screen_objects[i]->add_param("color=red");
        screen_objects[i]->add_param("opacity=0.5");
        sstm << "  " << screen_objects[i]->write();
        sstm << "\n";
    }

    // De-allocate all of the screen objects
    for (size_t i = 0; i < screen_objects.size(); ++i) {
        delete screen_objects[i];
    }
    screen_objects.resize(0);

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

    real dev;
    c_polygon plane;
    c_point normal;

    for (size_t i = 0; i < scene_objects.size(); ++i) {
        if (scene_objects[i]->can_light()) {
            plane = scene_objects[i]->get_plane();
            normal = plane.normal();
            dev = normal*norm_sun;
        }

        std::stringstream sstm;
        sstm << "black!" << (int) 100*(dev+1)/2;
        scene_objects[i]->add_param(sstm.str());
    }

}
