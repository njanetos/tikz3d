#include "c_point.h"

#include "c_camera.h"

c_point::c_point() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->twod = false;
}

c_point::c_point(real x, real y) {
    this->x = x;
    this->y = y;
    this->twod = false;
}

c_point::c_point(real x, real y, real z) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->twod = true;
}

c_point::~c_point() {
    //dtor
}


c_tikz_obj* c_point::project(c_camera *cam) {
    return cam->project(this);
}

std::string c_point::write(std::string params) {

    std::stringstream sstm;

    sstm << "\\draw[" << params << "] (" << x << ", " << y << ") circ (1)";

    return sstm.str();
}

c_tikz_obj* c_point::clone() {
    c_point* c = new c_point(x, y, z);
    return c;
}
