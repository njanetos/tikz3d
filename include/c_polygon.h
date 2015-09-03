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

        c_polygon(c_point a, c_point b, c_point c);

        virtual ~c_polygon();

        std::string write();

        c_point normal();

        c_tikz_obj* project(c_camera *cam);
        c_tikz_obj* clone();
        std::vector< std::vector<c_tikz_obj*> > split(c_polygon *against);

        bool can_split_against();
        c_polygon get_plane();

        c_point a, b, c;

};

std::ostream& operator<< (std::ostream& stream, const c_polygon& obj);

#endif // C_POLYGON_H
