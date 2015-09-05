#include "c_point.h"

#include "c_camera.h"
#include "c_polygon.h"

c_point::c_point() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->twod = false;
}

c_point::c_point(real x, real y) {
    this->x = x;
    this->y = y;
    this->z = 0;
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

std::string c_point::write() {

    std::stringstream sstm;

    sstm << "\\draw[";
    if (params.size() > 0) {
        sstm << params[0];
    }
    for (size_t i = 1; i < params.size(); ++i) {
        sstm << ", " << params[i];
    }
    sstm << "] (" << x << ", " << y << ") circ (1)";

    return sstm.str();
}

c_tikz_obj* c_point::clone() {
    c_point* c = new c_point(x, y, z);
    c->add_params(params);
    return c;
}

std::vector< std::vector<c_tikz_obj*> > c_point::split(c_polygon *against) {

    std::vector< std::vector<c_tikz_obj*> > ret(3);

    char loc = utils::is_located(this, against);

    ret[loc].push_back(clone());

    return ret;
}

bool c_point::can_split_against() {
    return false;
}

c_polygon c_point::get_plane() {
    c_polygon polygon;
    return polygon;
}

c_point c_point::normalize() {
    return *this/length();
}

real c_point::length() {
    return sqrt(x*x + y*y + z*z);
}

bool c_point::can_light() {
    return false;
}

std::ostream& c_point::print(std::ostream& stream) const {
    stream << "c_point: (" << x << ", " << y << ", " << z << ").\n";
    return stream;
}

std::ostream& operator<< (std::ostream& stream, const c_point& obj) {
    obj.print(stream);
    return stream;
}
