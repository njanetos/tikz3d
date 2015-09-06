#include "c_node.h"

#include "c_camera.h"
#include "c_polygon.h"

c_node::c_node() {
    color.push_back("black");
    light.push_back(100);
}

c_node::c_node(real x, real y, real z, std::string text) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->text = text;
    color.push_back("black");
    light.push_back(100);
}

c_node::~c_node() {
    //dtor
}

c_tikz_obj* c_node::project(const c_camera& cam) const {
    return cam.project(*this);
}

std::string c_node::write() const {
    std::stringstream sstm;

    sstm << "\\node[";
    if (params.size() > 0) {
        sstm << params[0];
    }
    for (size_t i = 1; i < params.size(); ++i) {
        sstm << ", " << params[i];
    }
    sstm << ", " << color[0] << "!" << light[0];
    sstm << "] at (" << x << ", " << y << ") {" << text << "};\n";

    return sstm.str();
}

c_tikz_obj* c_node::clone() const {

    c_node *node = new c_node(x, y, z, text);
    node->add_params(params);
    return node;

}

std::vector< std::vector<c_tikz_obj*> > c_node::split(const c_polygon& against) const {

    std::vector< std::vector<c_tikz_obj*> > ret(3);

    char loc = utils::is_located(x, y, z, against);

    ret[loc].push_back(clone());

    return ret;
}

bool c_node::can_split_against() const {
    return false;
}

c_polygon c_node::get_plane() const {
    c_polygon polygon;
    return polygon;
}

bool c_node::can_light() const {
    return false;
}

bool c_node::will_split(const c_polygon& against) const {
    return true;
}


std::ostream& c_node::print(std::ostream& stream) const {
    return stream;
}

std::ostream& operator<< (std::ostream& stream, const c_node& obj) {
    obj.print(stream);
    return stream;
}
