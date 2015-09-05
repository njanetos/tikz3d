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
         *  Finds the determinant of a 2x2 matrix.
         *
         *  \param a In position 11.
         *  \param b In position 12.
         *  \param c In position 21.
         *  \param d In position 22.
         *  \return The determinant.
         */
        static real det2(real a, real b, real c, real d);

        /**
         *  Finds the determinant of a 3x3 matrix.
         *
         *  \param x1 In position 11.
         *  \param x2 In position 12.
         *  \param x3 In position 13.
         *  \param y1 In position 21.
         *  \param y2 In position 22.
         *  \param y3 In position 23.
         *  \param z1 In position 31.
         *  \param z2 In position 32.
         *  \param z3 In position 33.
         *  \return The determinant.
         */
        static real det3(real x1, real x2, real x3, real y1, real y2, real y3, real z1, real z2, real z3);

        /**
         *  Finds the determinant of a 4x4 matrix.
         *
         *  \param a In position 11.
         *  \param b In position 12.
         *  \param c In position 13.
         *  \param d In position 14.
         *  \param e In position 21.
         *  \param f In position 22.
         *  \param g In position 23.
         *  \param h In position 24.
         *  \param i In position 31.
         *  \param j In position 32.
         *  \param k In position 33.
         *  \param l In position 34.
         *  \param m In position 41.
         *  \param n In position 42.
         *  \param o In position 43.
         *  \param p In position 44.
         *  \return The determinant.
         */
        static real det4(real a, real b, real c, real d, real e, real f, real g, real h, real i, real j, real k, real l, real m, real n, real o, real p);

        /**
         *  If s, e are the start and end points, finds the value t so that
         *  t*s + (1-t)*e  intersects with the plane.
         *
         *  \param line
         *  \param polygon
         *  \return Intersection.
         */
        static real get_split_point(const c_line& line, const c_polygon& polygon);

        /**
         *  Finds whether the point is above, below, or at the polygon.
         *
         *  \param point
         *  \param polygon
         *  \return 0 if below, 1 if at, 2 if above.
         */
        static char is_located(const c_point& point, const c_polygon& polygon);

        /**
         *  Finds whether the point is above, below, or at the polygon.
         *
         *  \param x
         *  \param y
         *  \param z
         *  \param polygon
         *  \return 0 if below, 1 if at, 2 if above.
         */
        static char is_located(real x, real y, real z, const c_polygon& polygon);

        /**
         *  Projects a point onto the plane using the camera.
         *
         *  \param point3d The point to project.
         *  \param cam The camera to project against.
         *  \return The projected point.
         */
        static c_point project(const c_point& point3d, const c_camera& cam);

        /**
         *  Projects a point onto the plane using the camera.
         *
         *  \param _x The x coordinate of the point to project.
         *  \param _y The y coordinate of the point to project.
         *  \param _z The z coordinate of the point to project.
         *  \param cam The camera to project against.
         *  \return The projected point.
         */
        static c_point project(real _x, real _y, real _z, const c_camera& cam);

};

#endif // UTILS_H
