#ifndef C_NODE_H
#define C_NODE_H

#include <string>

#include "common.h"
#include "c_tikz_obj.h"

class c_node : public c_tikz_obj
{
    public:
        c_node();
        virtual ~c_node();

        std::string write(std::string params);
        c_tikz_obj* project(c_camera *cam);
        c_tikz_obj* clone();
    protected:
    private:
        std::string text;
};

#endif // C_NODE_H
