#include "c_scene_manager.h"

#include "c_tikz_obj.h"

c_scene_manager::c_scene_manager() {
    //ctor
}

c_scene_manager::~c_scene_manager() {
    // De-allocate all of the scene objects
    for (size_t i = 0; i < scene_objects.size(); ++i) {
        delete scene_objects[i];
    }
}

void c_scene_manager::add_to_scene(c_tikz_obj *source) {
    c_tikz_obj * scene_object = source->clone();
    scene_objects.push_back(scene_object);
}

void c_scene_manager::render_to_file(std::string filename, c_camera *cam) {

    std::vector<c_tikz_obj*> screen_objects(scene_objects.size());

    // Project everything
    for (size_t i = 0; i < scene_objects.size(); ++i) {
        screen_objects[i] = scene_objects[i]->project(cam);
    }

    std::ofstream sstm;
    sstm.open(filename);

    sstm << "\\begin{tikzpicture}\n";

    sstm << "\\draw (0, 0)--(0,0.01);";

    for (size_t i = 0; i < screen_objects.size(); ++i) {
        sstm << "   " << screen_objects[i]->write("ultra thick");
        sstm << "\n";
    }

    sstm << "\\end{tikzpicture}";

    sstm.close();

    // De-allocate all of the screen objects
    for (size_t i = 0; i < screen_objects.size(); ++i) {
        delete screen_objects[i];
    }
}

void c_scene_manager::render_3d_to_file(std::string filename, c_camera *eye1, c_camera *eye2) {

    std::ofstream sstm;
    sstm.open(filename);

    sstm << "\\begin{tikzpicture}\n";

    sstm << "  \\draw (0, 0)--(0,0.01); \n";

    std::vector<c_tikz_obj*> screen_objects(scene_objects.size());

    // Project everything for the first eye
    for (size_t i = 0; i < scene_objects.size(); ++i) {
        screen_objects[i] = scene_objects[i]->project(eye1);
    }

    // Write to file
    for (size_t i = 0; i < screen_objects.size(); ++i) {
        sstm << "   " << screen_objects[i]->write("ultra thick, color=green, opacity=0.5");
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
        sstm << "  " << screen_objects[i]->write("ultra thick, color=red, opacity=0.5");
        sstm << "\n";
    }

    // De-allocate all of the screen objects
    for (size_t i = 0; i < screen_objects.size(); ++i) {
        delete screen_objects[i];
    }

    sstm << "\\end{tikzpicture}";

    sstm.close();



}
