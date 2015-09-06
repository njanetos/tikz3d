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

        /**
         *  2Camera constructor.
         *
         *  \param pos_x X coordinate of camera.
         *  \param pos_y Y coordinate of camera.
         *  \param pos_z Z coordinate of camera.
         *  \param tx X Tait-Bryan angle for rotation.
         *  \param ty Y Tait-Bryan angle for rotation.
         *  \param tz Z Tait-Bryan angle for rotation.
         */
        c_camera(real pos_x, real pos_y, real pos_z, real tx, real ty, real tz);

        virtual ~c_camera();

        void point_at(const c_point& point);

        /**
         *  Visitor pattern method for projecting a 3D point.
         *
         *  \param point3d The object to project.
         *  \return Pointer to the projected object.
         */
        c_tikz_obj* project(const c_point& point3d) const;

        /**
         *  Visitor pattern method for projecting a 3D line.
         *
         *  \param point3d The object to project.
         *  \return Pointer to the projected object.
         */
        c_tikz_obj* project(const c_line& line3d) const;

        /**
         *  Visitor pattern method for projecting a 3D polygon.
         *
         *  \param point3d The object to project.
         *  \return Pointer to the projected object.
         */
        c_tikz_obj* project(const c_polygon& polygon3d) const;

        /**
         *  Visitor pattern method for projecting a 3D node.
         *
         *  \param point3d The object to project.
         *  \return Pointer to the projected object.
         */
        c_tikz_obj* project(const c_node& node3d) const;

        real pos_x, pos_y, pos_z, tx, ty, tz;
};

#endif // C_CAMERA_H
