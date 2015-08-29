#ifndef C_POLYGON_H
#define C_POLYGON_H

#include "common.h"
#include "c_tikz_obj.h"
#include "c_point.h"

class c_line;
class c_node;

class c_polygon : public c_tikz_obj
{
    public:

        c_polygon();

        /**
         *  Polygon constructor.
         *
         *  \param ax X coordinate of 1st point.
         *  \param ay Y coordinate of 1st point.
         *  \param az Z coordinate of 1st point.
         *  \param bx X coordinate of 2st point.
         *  \param by Y coordinate of 2st point.
         *  \param bz Z coordinate of 2st point.
         *  \param cx X coordinate of 3st point.
         *  \param cy Y coordinate of 3st point.
         *  \param cz Z coordinate of 3st point.
         */
        c_polygon(real ax, real ay, real az, real bx, real by, real bz, real cx, real cy, real cz);

        virtual ~c_polygon();

        std::vector<c_tikz_obj*> split(c_tikz_obj *obj);
        std::vector<c_tikz_obj*> split(c_polygon *obj);
        std::vector<c_tikz_obj*> split(c_line *obj);
        std::vector<c_tikz_obj*> split(c_point *obj);
        std::vector<c_tikz_obj*> split(c_node *obj);
        std::string write();
        c_tikz_obj* project(c_camera *cam);
        c_tikz_obj* clone();

        c_point a, b, c;
    protected:
    private:
};

#endif // C_POLYGON_H
