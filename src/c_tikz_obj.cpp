#include "c_tikz_obj.h"

c_tikz_obj::~c_tikz_obj() {
    //dtor
}

void c_tikz_obj::add_param(std::string param) {
    params.push_back(param);
}

void c_tikz_obj::add_params(std::vector<std::string> params) {
    for (size_t i = 0; i < params.size(); ++i) {
        this->params.push_back(params[i]);
    }
}

std::ostream& c_tikz_obj::print(std::ostream& stream) {
    stream << "Abstract type, cannot print.\n";
    return stream;
}

std::ostream& operator<< (std::ostream& stream, const c_tikz_obj& obj) {
    return obj.print(stream);
}
