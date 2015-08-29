#ifndef C_LINE_H
#define C_LINE_H

#include "common.h"
#include "c_tikz_obj.h"

class c_point;
class c_node;
class c_polygon;

class c_line : public c_tikz_obj
{
    public:

        /**
         *  Empty constructor.
         */
        c_line();

        /**
         *  Line constructor.
         *
         *  \param sx Start X coordinate.
         *  \param sy Start Y coordinate.
         *  \param sz Start Z coordinate.
         *  \param ex End X coordinate.
         *  \param ey End Y coordinate.
         *  \param ez End Z coordinate.
         */
        c_line(real sx, real sy, real sz, real ex, real ey, real ez);

        virtual ~c_line();

        std::vector<c_tikz_obj*> split(c_tikz_obj *obj);
        std::vector<c_tikz_obj*> split(c_polygon *obj);
        std::vector<c_tikz_obj*> split(c_line *obj);
        std::vector<c_tikz_obj*> split(c_point *obj);
        std::vector<c_tikz_obj*> split(c_node *obj);

        std::string write();
        c_tikz_obj* project(c_camera *cam);
        c_tikz_obj* clone();

        real sx, sy, sz, ex, ey, ez;
};

#endif // C_LINE_H
