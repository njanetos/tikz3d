#include "c_node.h"

#include "c_camera.h"

c_node::c_node() {
    //ctor
}

c_node::c_node(real x, real y, real z, std::string text) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->text = text;
}

c_node::~c_node() {
    //dtor
}

c_tikz_obj* c_node::project(c_camera *cam) {
    return cam->project(this);
}

std::string c_node::write() {
    std::stringstream sstm;

    sstm << "\\node[";
    if (params.size() > 0) {
        sstm << params[0];
    }
    for (size_t i = 1; i < params.size(); ++i) {
        sstm << ", " << params[i];
    }
    sstm << "] at (" << x << ", " << y << ") {" << text << "};\n";

    return sstm.str();
}

c_tikz_obj* c_node::clone() {

    c_node *node = new c_node(x, y, z, text);
    node->add_params(params);
    return node;

}

std::vector<std::vector<c_tikz_obj*>> c_node::split(c_polygon *against) {

    std::vector<std::vector<c_tikz_obj*>> ret(3);

    char loc = utils::is_located(x, y, z, against);

    ret[loc].push_back(clone());

    return ret;
}

