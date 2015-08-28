#include "c_polygon.h"

#include "c_camera.h"

c_polygon::c_polygon() {
    //ctor
}

c_polygon::c_polygon(real ax,
                     real ay,
                     real az,
                     real bx,
                     real by,
                     real bz,
                     real cx,
                     real cy,
                     real cz) {

    a.x = ax;
    a.y = ay;
    a.z = az;
    b.x = bx;
    b.y = by;
    b.z = bz;
    c.x = cx;
    c.y = cy;
    c.z = cz;
}

c_polygon::~c_polygon() {
    //dtor
}


c_tikz_obj* c_polygon::project(c_camera *cam) {
    return cam->project(this);
}

std::string c_polygon::write() {
    std::stringstream sstm;

    sstm << "\\fill[";
    if (params.size() > 0) {
        sstm << params[0];
    }
    for (size_t i = 1; i < params.size(); ++i) {
        sstm << ", " << params[i];
    }
    sstm << "] (" << a.x << ", " << a.y << ") -- (" << b.x << ", " << b.y << ") -- (" << c.x << ", " << c.y << ") -- (" << a.x << ", " << a.y << ");\n";

    return sstm.str();
}

c_tikz_obj* c_polygon::clone() {

    c_polygon *polygon = new c_polygon(a.x, a.y, a.z, b.x, b.y, b.z, c.x, c.y, c.z);
    polygon->add_params(params);
    return polygon;

}
