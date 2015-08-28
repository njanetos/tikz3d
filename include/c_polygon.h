#ifndef C_POLYGON_H
#define C_POLYGON_H

#include "common.h"
#include "c_tikz_obj.h"
#include "c_point.h"

class c_polygon : public c_tikz_obj
{
    public:
        c_polygon();
        c_polygon(real ax, real ay, real az, real bx, real by, real bz, real cx, real cy, real cz);
        virtual ~c_polygon();

        std::string write();
        c_tikz_obj* project(c_camera *cam);
        c_tikz_obj* clone();

        c_point a, b, c;
    protected:
    private:
};

#endif // C_POLYGON_H
