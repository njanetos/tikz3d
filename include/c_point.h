#ifndef C_POINT_H
#define C_POINT_H

#include <sstream>

#include "common.h"
#include "c_tikz_obj.h"

class c_point : public c_tikz_obj
{
    public:
        c_point();
        c_point(real x, real y);
        c_point(real x, real y, real z);
        virtual ~c_point();

        std::string write();
        c_tikz_obj* project(c_camera *cam);
        c_tikz_obj* clone();

        real x, y, z;
        bool twod;
    protected:
    private:
};

#endif // C_POINT_H
