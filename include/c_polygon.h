#ifndef C_POLYGON_H
#define C_POLYGON_H

#include "common.h"
#include "c_tikz_obj.h"

class c_polygon : public c_tikz_obj
{
    public:
        c_polygon();
        virtual ~c_polygon();

        std::string write(std::string params);
        c_tikz_obj* project(c_camera *cam);
        c_tikz_obj* clone();
    protected:
    private:
};

#endif // C_POLYGON_H
