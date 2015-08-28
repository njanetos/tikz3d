#ifndef C_NODE_H
#define C_NODE_H

#include <string>
#include <sstream>

#include "common.h"
#include "c_tikz_obj.h"

class c_node : public c_tikz_obj
{
    public:
        c_node();
        c_node(real x, real y, real z, std::string text);
        virtual ~c_node();

        std::string write(std::string params);
        c_tikz_obj* project(c_camera *cam);
        c_tikz_obj* clone();
        real x, y, z;
        std::string text;
};

#endif // C_NODE_H
