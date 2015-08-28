#ifndef C_SCENE_MANAGER_H
#define C_SCENE_MANAGER_H

#include <string>
#include <fstream>

#include "c_camera.h"
#include "c_tikz_obj.h"

class c_tikz_obj;

class c_scene_manager {
    public:

        /**
         *  Scene constructor.
         */
        c_scene_manager();

        /**
         *  Scene destructor. Deallocates all scene objects.
         */
        virtual ~c_scene_manager();

        /**
         *  Clones the object, and adds it to the scene.
         *
         *  \param source The object to be cloned and added to the scene.
         */
        void add_to_scene(c_tikz_obj *source);

        /**
         *  Renders all objects in the scene to a file.
         *
         *  \param filename Where to render it to.
         *  \param cam The camera to project against.
         */
        void render_to_file(std::string filename, c_camera *cam);

        /**
         *  Renders all objects in the scene to a file, twice,
         *  once in green for camera eye_1, and once in red for
         *  camera eye_2.
         *
         *  \param filename Where to render it to.
         *  \param eye1 The camera representing the left eye.
         *  \param eye2 The camera representing the right eye.
         */
        void render_3d_to_file(std::string filename, c_camera *eye1, c_camera *eye2);

        void render_cross_to_file(std::string filename, c_camera *cam);

    private:

        /**
         *  Vector of objects in the scene. Deallocated when destructed.
         */
        std::vector<c_tikz_obj*> scene_objects;

};

#endif // C_SCENE_MANAGER_H
