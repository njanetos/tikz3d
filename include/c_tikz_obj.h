#ifndef C_TIKZ_OBJ_H
#define C_TIKZ_OBJ_H

#include "common.h"

class c_camera;

class c_tikz_obj {
    public:
        virtual ~c_tikz_obj();
        virtual std::string write() =0;
        virtual c_tikz_obj* project(c_camera *cam) =0;
        virtual c_tikz_obj* clone() =0;
        std::vector<std::string> params;
        void add_param(std::string param);
        void add_params(std::vector<std::string> params);
};

#endif // C_TIKZ_OBJ_H
