#include <fstream>
#include <iostream>
#include <regex>

#include "c_scene_manager.h"
#include "c_polygon.h"

using namespace std;

int main (int argc, char *argv[]) {

    typedef istreambuf_iterator<char> buf_iter;

    fstream file(argv[1]);
    stringstream curr;
    double val;

    c_polygon * polygon = new c_polygon();
    std::vector<double> points;

    c_scene_manager scene_manager;

    for(buf_iter i(file), e; i != e; ++i){
        char c = *i;

        // Check the current state
        if (c == '\\') {
            points.resize(0);
            curr.clear();
            curr.str(std::string());
        } else if (c == '(') {
            curr.clear();
            curr.str(std::string());
        } else if (c == ',' || c == ')') {
            val = 0;
            curr >> val;
            points.push_back(val);
            curr.clear();
            curr.str(std::string());
        } else if (c == '[') {
            delete polygon;
            polygon = new c_polygon();
            curr.clear();
            curr.str(std::string());
        } else if (c == ']') {
            polygon->color[0] = curr.str();
            curr.clear();
            curr.str(std::string());
        } else if (c == ';') {

            // Read in the polygon
            std::vector<c_point> point(3);
            for (size_t j = 0; j < 3; ++j) {
                point[j].x = points[3*j];
                point[j].y = points[3*j+1];
                point[j].z = points[3*j+2];
            }

            polygon->a = point[0];
            polygon->b = point[1];
            polygon->c = point[2];

            scene_manager.add_to_scene(*polygon);

            curr.clear();
            curr.str(std::string());
        } else {
            curr << c;
        }
    }

    c_camera camera(48, 48, 48, -3.14/4, 0, -3.14/4);
    c_point sun(0.5, 1, 1.5);
    scene_manager.light(sun);

    scene_manager.render_to_file("output.tex", camera);

}
