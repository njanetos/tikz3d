#include "c_node.h"

#include "c_camera.h"

c_node::c_node()
{
    //ctor
}

c_node::~c_node()
{
    //dtor
}


c_tikz_obj* c_node::project(c_camera *cam) {
    return cam->project(this);
}

std::string c_node::write(std::string params) {
    return "";
}

c_tikz_obj* c_node::clone() {

}
