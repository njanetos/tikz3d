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

        std::string write() const;
        c_tikz_obj* project(const c_camera& cam) const;
        c_tikz_obj* clone() const;

        void set_points(c_point s, c_point e);

        std::vector< std::vector<c_tikz_obj*> > split(const c_polygon& against) const;
        std::ostream& print(std::ostream& stream) const;

        bool can_split_against() const;
        bool can_light() const;
        c_polygon get_plane() const;

        real sx, sy, sz, ex, ey, ez;
};

std::ostream& operator<< (std::ostream& stream, const c_line& obj);

#endif // C_LINE_H
