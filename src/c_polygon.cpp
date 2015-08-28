#include "c_polygon.h"

#include "c_camera.h"

c_polygon::c_polygon()
{
    //ctor
}

c_polygon::~c_polygon()
{
    //dtor
}


c_tikz_obj* c_polygon::project(c_camera *cam) {
    return cam->project(this);
}

std::string c_polygon::write(std::string params) {
    return "";
}

c_tikz_obj* c_polygon::clone() {

}
