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

        static real det2(real a, real b, real c, real d);

        static real det3(real x1, real x2, real x3, real y1, real y2, real y3, real z1, real z2, real z3);

        static real det4(real a, real b, real c, real d, real e, real f, real g, real h, real i, real j, real k, real l, real m, real n, real o, real p);

        static real get_split_point(const c_line& line, const c_polygon& polygon);

        static char is_located(c_point* point, c_polygon* polygon);

        static char is_located(real x, real y, real z, c_polygon *polygon);

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

};

#endif // UTILS_H
