#ifndef C_SCENE_MANAGER_H
#define C_SCENE_MANAGER_H

#include <string>
#include <fstream>

#include "c_camera.h"
#include "c_tikz_obj.h"

class c_tikz_obj;

class c_scene_manager {
    public:
        c_scene_manager();
        virtual ~c_scene_manager();

        void add_to_scene(c_tikz_obj *source);
        void render_to_file(std::string filename, c_camera *cam);
        void render_3d_to_file(std::string filename, c_camera *eye1, c_camera *eye2);
    protected:
    private:
        std::vector<c_tikz_obj*> scene_objects;
};

#endif // C_SCENE_MANAGER_H
