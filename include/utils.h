#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <iostream>

#include "c_camera.h"
#include "c_point.h"

class utils {
    /**
    *  @brief Utility math class for projections.
    */
    public:

        /**
         *  Projects a point onto the plane using the camera.
         *
         *  \param point3d The point to project.
         *  \param cam The camera to project against.
         *  \return The projected point.
         */
        static c_point project(c_point *point3d, c_camera *cam);

        /**
         *  Projects a point onto the plane using the camera.
         *
         *  \param _x The x coordinate of the point to project.
         *  \param _y The y coordinate of the point to project.
         *  \param _z The z coordinate of the point to project.
         *  \param cam The camera to project against.
         *  \return The projected point.
         */
        static c_point project(real _x, real _y, real _z, c_camera *cam);

        static std::vector<c_tikz_obj*> split(c_point *obj1, c_point *obj2);
        static std::vector<c_tikz_obj*> split(c_line *obj1, c_point *obj2);
        static std::vector<c_tikz_obj*> split(c_node *obj1, c_point *obj2);
        static std::vector<c_tikz_obj*> split(c_polygon *obj1, c_point *obj2);
        static std::vector<c_tikz_obj*> split(c_point *obj1, c_line *obj2);
        static std::vector<c_tikz_obj*> split(c_line *obj1, c_line *obj2);
        static std::vector<c_tikz_obj*> split(c_node *obj1, c_line *obj2);
        static std::vector<c_tikz_obj*> split(c_polygon *obj1, c_line *obj2);
        static std::vector<c_tikz_obj*> split(c_point *obj1, c_node *obj2);
        static std::vector<c_tikz_obj*> split(c_line *obj1, c_node *obj2);
        static std::vector<c_tikz_obj*> split(c_node *obj1, c_node *obj2);
        static std::vector<c_tikz_obj*> split(c_polygon *obj1, c_node *obj2);
        static std::vector<c_tikz_obj*> split(c_point *obj1, c_polygon *obj2);
        static std::vector<c_tikz_obj*> split(c_line *obj1, c_polygon *obj2);
        static std::vector<c_tikz_obj*> split(c_node *obj1, c_polygon *obj2);
        static std::vector<c_tikz_obj*> split(c_polygon *obj1, c_polygon *obj2);

        static bool is_above(c_point *point, c_polygon *polygon);

};

#endif // UTILS_H
