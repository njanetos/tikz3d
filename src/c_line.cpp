#include "c_line.h"

#include "c_camera.h"
#include "c_point.h"
#include "c_polygon.h"

c_line::c_line() {
    sx = 0;
    sy = 0;
    sz = 0;
    ex = 0;
    ey = 0;
    ez = 0;
}

c_line::c_line(real sx, real sy, real sz, real ex, real ey, real ez) {
    this->sx = sx;
    this->sy = sy;
    this->sz = sz;
    this->ex = ex;
    this->ey = ey;
    this->ez = ez;
}

c_line::~c_line() {
    //dtor
}

c_tikz_obj* c_line::project(c_camera *cam) {
    return cam->project(this);
}

std::string c_line::write() {

    std::stringstream sstm;

    sstm << "\\draw[";
    if (params.size() > 0) {
        sstm << params[0];
    }
    for (size_t i = 1; i < params.size(); ++i) {
        sstm << ", " << params[i];
    }
    sstm << "] (" << sx << ", " << sy << ") -- (" << ex << ", " << ey << ");";

    return sstm.str();
}

c_tikz_obj* c_line::clone() {
    c_line *line = new c_line(sx, sy, sz, ex, ey, ez);
    line->add_params(params);
    return line;
}

std::vector< std::vector<c_tikz_obj*> > c_line::split(c_polygon *against) {

    int loc_s, loc_e;

    loc_s = utils::is_located(sx, sy, sz, against);
    loc_e = utils::is_located(ex, ey, ez, against);

    std::vector< std::vector<c_tikz_obj*> > ret(3);

    if (loc_s == loc_e) {
        // Either entirely above, entirely behind, or entirely contained within.
        ret[loc_s].push_back(clone());
        return ret;
    } else if (loc_s == 1) {
        // The start barely touches but is still behind / below
        ret[loc_e].push_back(clone());
    } else if (loc_e == 1) {
        // The end just barely touches but it is still behind / below
        ret[loc_e].push_back(clone());
    }

    // loc_s != loc_e, and neither equals 1.

    real t;

    t = -1*utils::det4(1, 1, 1, 1,
                       against->a.x, against->b.x, against->c.x, sx,
                       against->a.y, against->b.y, against->c.y, sy,
                       against->a.z, against->b.z, against->c.z, sz);

    t = t / utils::det4(1, 1, 1, 0,
                        against->a.x, against->b.x, against->c.x, ex - sx,
                        against->a.y, against->b.y, against->c.y, ey - sy,
                        against->a.z, against->b.z, against->c.z, ez - sz);

    real int_x, int_y, int_z;

    int_x = (1-t)*sx + t*ex;
    int_y = (1-t)*sy + t*ey;
    int_z = (1-t)*sz + t*ez;

    c_line *line_start = new c_line();
    c_line *line_end = new c_line();

    line_start->sx = sx;
    line_start->sy = sy;
    line_start->sz = sz;
    line_start->ex = int_x;
    line_start->ey = int_y;
    line_start->ez = int_z;

    line_end->sx = int_x;
    line_end->sy = int_y;
    line_end->sz = int_z;
    line_end->ex = ex;
    line_end->ey = ey;
    line_end->ez = ez;

    // Add the splitted guys to the correct position in the vector.
    // Add the splitted guys to the correct position in the vector.
    ret[loc_e].push_back(line_start);
    ret[loc_s].push_back(line_end);

    return ret;
}

void c_line::set_points(c_point s, c_point e) {
    sx = s.x;
    sy = s.y;
    sz = s.z;
    ex = e.x;
    ey = e.y;
    ez = e.z;
}

bool c_line::can_split_against() {
    return true;
}

c_polygon c_line::get_plane() {
    c_point point1(sx, sy, sz);
    c_point point2(ex, ey, ez);
    c_polygon polygon(sx, sy, sz, ex, ey, ez, 0, 0, 0);
    return polygon;
}

std::ostream& operator<< (std::ostream& stream, const c_line& obj) {
    stream << "c_line: (" << obj.sx << ", " << obj.sy << ", " << obj.sz << ") -- (" << obj.ex << ", " << obj.ey << ", " << obj.ez << ").\n";
    return stream;
}
