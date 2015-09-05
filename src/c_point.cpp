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


c_tikz_obj* c_point::project(const c_camera& cam) const {
    return cam.project(*this);
}

std::string c_point::write() const {

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

c_tikz_obj* c_point::clone() const {
    c_point* c = new c_point(x, y, z);
    c->add_params(params);
    return c;
}

std::vector< std::vector<c_tikz_obj*> > c_point::split(const c_polygon& against) const {

    std::vector< std::vector<c_tikz_obj*> > ret(3);

    char loc = utils::is_located(*this, against);

    ret[loc].push_back(clone());

    return ret;
}

bool c_point::can_split_against() const {
    return false;
}

c_polygon c_point::get_plane() const {
    c_polygon polygon;
    return polygon;
}

c_point c_point::normalize() const {
    return *this/length();
}

real c_point::length() const {
    return sqrt(x*x + y*y + z*z);
}

bool c_point::can_light() const {
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
