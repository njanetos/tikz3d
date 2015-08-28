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
    this->params = "";
}

c_line::c_line(real sx, real sy, real sz, real ex, real ey, real ez) {
    this->sx = sx;
    this->sy = sy;
    this->sz = sz;
    this->ex = ex;
    this->ey = ey;
    this->ez = ez;
    this->params = "";
}

c_line::c_line(real sx, real sy, real sz, real ex, real ey, real ez, std::string params) {
    this->sx = sx;
    this->sy = sy;
    this->sz = sz;
    this->ex = ex;
    this->ey = ey;
    this->ez = ez;
    this->params = params;
}


c_line::~c_line() {
    //dtor
}


c_tikz_obj* c_line::project(c_camera *cam) {
    return cam->project(this);
}

std::string c_line::write(std::string params) {

    std::stringstream sstm;

    sstm << "\\draw[" << params << this->params << "] (" << sx << ", " << sy << ") -- (" << ex << ", " << ey << ");";

    return sstm.str();
}

c_tikz_obj* c_line::clone() {
    c_line *c = new c_line(sx, sy, sz, ex, ey, ez);
    return c;
}
