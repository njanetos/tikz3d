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

        std::vector<c_tikz_obj*> split(c_tikz_obj *obj);
        std::vector<c_tikz_obj*> split(c_polygon *obj);
        std::vector<c_tikz_obj*> split(c_line *obj);
        std::vector<c_tikz_obj*> split(c_point *obj);
        std::vector<c_tikz_obj*> split(c_node *obj);
        std::string write();
        c_tikz_obj* project(c_camera *cam);
        c_tikz_obj* clone();

        real x, y, z;
        bool twod;
    protected:
    private:
};

#endif // C_POINT_H
