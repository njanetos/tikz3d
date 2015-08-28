#include "c_node.h"

#include "c_camera.h"

c_node::c_node() {
    //ctor
}

c_node::c_node(real x, real y, std::string text) {
    this->x = x;
    this->y = y;
    this->text = text;
}

c_node::~c_node() {
    //dtor
}

c_tikz_obj* c_node::project(c_camera *cam) {
    return cam->project(this);
}

std::string c_node::write(std::string params) {
    std::stringstream sstm;

    sstm << "\\node[" << params << "] at (" << x << ", " << y << ") {" << text << "};\n";

    return sstm.str();
}

c_tikz_obj* c_node::clone() {

}
