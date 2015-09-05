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

        std::string write() const;
        c_tikz_obj* project(const c_camera& cam) const;
        c_tikz_obj* clone() const;

        std::vector< std::vector<c_tikz_obj*> > split(const c_polygon& against) const;

        bool can_split_against() const;
        bool can_light() const;
        c_polygon get_plane() const;

        c_point operator+(const c_point& c) const {
            c_point point(this->x + c.x, this->y + c.y, this->z + c.z);
            return point;
        }

        c_point operator-(const c_point& c) const {
            c_point point(this->x - c.x, this->y - c.y, this->z - c.z);
            return point;
        }

        c_point operator*(const real c) const {
            c_point point(this->x*c, this->y*c, this->z*c);
            return point;
        }

        c_point operator/(const real c) const {
            c_point point(this->x/c, this->y/c, this->z/c);
            return point;
        }

        real operator*(const c_point& c) const {
            return this->x * c.x + this->y * c.y + this->z * c.z;
        }

        c_point normalize() const;

        real length() const;

        std::ostream& print(std::ostream& stream) const;

        real x, y, z;
        bool twod;
};

std::ostream& operator<< (std::ostream& stream, const c_point& obj);

#endif // C_POINT_H
