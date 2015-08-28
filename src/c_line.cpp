#include "c_line.h"

#include "c_camera.h"
#include "c_point.h"

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
