#ifndef C_CAMERA_H
#define C_CAMERA_H

#include <cmath>
#include <vector>
#include <typeinfo>

#include "common.h"
#include "utils.h"

class c_point;
class c_line;
class c_polygon;
class c_node;
class c_tikz_obj;

class c_camera
{
    public:
        c_camera(real pos_x, real pos_y, real pos_z, real tx, real ty, real tz);
        virtual ~c_camera();

        c_tikz_obj* project(c_point * point3d);
        c_tikz_obj* project(c_line * line3d);
        c_tikz_obj* project(c_polygon * polygon3d);
        c_tikz_obj* project(c_node * node3d);
        real pos_x, pos_y, pos_z, tx, ty, tz;
};

#endif // C_CAMERA_H
