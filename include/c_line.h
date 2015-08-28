#ifndef C_LINE_H
#define C_LINE_H

#include "common.h"
#include "c_tikz_obj.h"

class c_line : public c_tikz_obj
{
    public:
        c_line();
        c_line(real sx, real sy, real sz, real ex, real ey, real ez);
        virtual ~c_line();

        real sx, sy, sz, ex, ey, ez;

        std::string write();
        c_tikz_obj* project(c_camera *cam);
        c_tikz_obj* clone();
    protected:
    private:
};

#endif // C_LINE_H
