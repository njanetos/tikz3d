#ifndef C_SCENE_MANAGER_H
#define C_SCENE_MANAGER_H

#include <string>
#include <fstream>

#include "c_camera.h"
#include "c_tikz_obj.h"
#include "c_polygon.h"
#include "c_line.h"
#include "c_tree_node.h"

using namespace std;

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
        void add_to_scene(const c_tikz_obj& source);

        /**
         *  Renders all objects in the scene to a file.
         *
         *  \param filename Where to render it to.
         *  \param cam The camera to project against.
         */
        void render_to_file(std::string filename, const c_camera& cam);

        /**
         *  Renders all objects in the scene to a file, twice,
         *  once in green for camera eye_1, and once in red for
         *  camera eye_2.
         *
         *  \param filename Where to render it to.
         *  \param eye1 The camera representing the left eye.
         *  \param eye2 The camera representing the right eye.
         */
        void render_3d_to_file(std::string filename, const c_camera& eye1, const c_camera& eye2);

        void render_cross_to_file(std::string filename, const c_camera& eye_1, const c_camera& eye_2);

        void light(c_point& sun);

        void axis(real x, real y, real z);

        void compile_bsp();

        void render_bsp(std::string filename, c_camera& cam);

        void plot(real (*func)(real x, real y), real start_x, real start_y,  real end_x, real end_y, size_t xdim, size_t ydim);

        void add_box(real sx, real sy, real sz, real ex, real ey, real ez, vector<string> params, string color);

        void add_rectangle_z(real sx, real sy, real ex, real ey, real z, vector<string> params, string color, bool flip);
        void add_rectangle_y(real sx, real sz, real ex, real ez, real y, vector<string> params, string color, bool flip);
        void add_rectangle_x(real sy, real sz, real ey, real ez, real x, vector<string> params, string color, bool flip);

        void add_fan(std::vector<c_point> points, vector<string> params, string color);

        c_tree_node *root;

    private:

        /**
         *  Vector of objects in the scene. Deallocated when destructed.
         */
        std::vector<c_tikz_obj*> scene_objects;
        std::vector<c_tikz_obj*> bsp_objects;

};

#endif // C_SCENE_MANAGER_H
