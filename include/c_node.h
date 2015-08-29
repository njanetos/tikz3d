#ifndef C_NODE_H
#define C_NODE_H

#include <string>
#include <sstream>

#include "common.h"
#include "c_tikz_obj.h"

class c_point;
class c_line;
class c_polygon;

class c_node : public c_tikz_obj
{
    public:

        /**
         *  Empty constructor.
         */
        c_node();

        /**
         *  Node constructor.
         *
         *  \param x X coordinate of node.
         *  \param y Y coordinate of node.
         *  \param z Z coordinate of node.
         *  \param text The text to display.
         */
        c_node(real x, real y, real z, std::string text);

        virtual ~c_node();

        std::vector<c_tikz_obj*> split(c_tikz_obj *obj);
        std::vector<c_tikz_obj*> split(c_polygon *obj);
        std::vector<c_tikz_obj*> split(c_line *obj);
        std::vector<c_tikz_obj*> split(c_point *obj);
        std::vector<c_tikz_obj*> split(c_node *obj);
        std::string write();
        c_tikz_obj* project(c_camera *cam);
        c_tikz_obj* clone();

        real x, y, z;
        std::string text;
};

#endif // C_NODE_H
