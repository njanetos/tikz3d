#ifndef C_POINT_H
#define C_POINT_H

#include <sstream>

#include "common.h"
#include "c_tikz_obj.h"

class c_line;
class c_node;
class c_polygon;

class c_point : public c_tikz_obj
{
    public:

        /**
         *  Empty constructor.
         */
        c_point();

        /**
         *  2D point constructor.
         *
         *  \param x X coordinate of point.
         *  \param y Y coordinate of point.
         */
        c_point(real x, real y);

        /**
         *  3D point constructor.
         *
         *  \param x X coordinate of point.
         *  \param y Y coordinate of point.
         *  \param z Z coordinate of point.
         */
        c_point(real x, real y, real z);

        virtual ~c_point();

        std::string write();
        c_tikz_obj* project(c_camera *cam);
        c_tikz_obj* clone();

        std::vector< std::vector<c_tikz_obj*> > split(c_polygon *against);
        std::ostream& print(std::ostream& stream);

        bool can_split_against();
        c_polygon get_plane();

        c_point operator+(const c_point& c) {
            c_point point(this->x + c.x, this->y + c.y, this->z + c.z);
            return point;
        }

        c_point operator-(const c_point& c) {
            c_point point(this->x - c.x, this->y - c.y, this->z - c.z);
            return point;
        }

        real operator*(const c_point& c) {
            return this->x * c.x + this->y * c.y + this->z * c.z;
        }

        real x, y, z;
        bool twod;
};

std::ostream& operator<< (std::ostream& stream, const c_point& obj);

#endif // C_POINT_H
