#ifndef C_TIKZ_OBJ_H
#define C_TIKZ_OBJ_H

#include "common.h"

class c_camera;

class c_tikz_obj {
    public:
        virtual ~c_tikz_obj();
        virtual std::string write(std::string params) =0;
        virtual c_tikz_obj* project(c_camera *cam) =0;
        virtual c_tikz_obj* clone() =0;
    protected:
        std::string params;
    private:
};

#endif // C_TIKZ_OBJ_H
