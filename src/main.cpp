#include <fstream>
#include <iostream>
#include <regex>
#include <QString>
#include <QRegularExpression>

#include "c_scene_manager.h"
#include "c_polygon.h"
#include "c_point.h"

using namespace std;

int main (int argc, char *argv[]) {

    c_scene_manager scene_manager;

    bool bsp = false;

    fstream file(argv[1]);

    vector<QString> lines;
    string line;

    while (std::getline(file, line)) {
        if (line.compare("") != 0) {
            lines.push_back(QString::fromUtf8(line.c_str()));
            //lines[lines.size()-1].replace(" ", "");
            lines[lines.size()-1].replace(";", "");
            lines[lines.size()-1].replace("\\", "");
        }
    }

    QRegularExpression first_reg(".+?(?=\\[|\\()");
    QRegularExpression param_reg("\\[.*\\]");
    QRegularExpression point_reg("(?<=\\(|\\,)(.*?)(?=\\,|\\))");
    QRegularExpression param_split_reg("(?<=\\[|\\,)(.*?)(?=\\,|\\])");

    // Default camera, sun
    c_camera camera(48, 48, 48, -3.14/4, 0, -3.14/4);
    c_point sun(0.5, 1, 1.5);

    for (size_t i = 0; i < lines.size(); ++i) {
        // Extract the type
        QRegularExpressionMatch match_type = first_reg.match(lines[i]);
        QString type = match_type.captured(0);

        QRegularExpressionMatch match_param = param_reg.match(lines[i]);
        QString param = match_param.captured(0);

        QRegularExpressionMatchIterator match_point = point_reg.globalMatch(lines[i]);

        vector<double> points;

        while(match_point.hasNext()) {
            QRegularExpressionMatch match = match_point.next();
            QString temp = match.captured(0);
            points.push_back(atof(temp.toStdString().c_str()));

        }

        // Pull out the parameters
        QRegularExpressionMatchIterator match_params_split = param_split_reg.globalMatch(param);

        vector<QString> params;

        while(match_params_split.hasNext()) {
            QRegularExpressionMatch match = match_params_split.next();
            params.push_back(match.captured(0));
        }

        // Decide what to add

        if (QString::compare(type, "filldraw") == 0) {

            // Add a polygon
            vector<c_point> to_add(0);

            for(size_t j = 0; j < points.size()/3; ++j) {
                c_point point(points[3*j], points[3*j+1], points[3*j+2]);
                to_add.push_back(point);
            }

            c_polygon polygon;
            polygon.a = to_add[0];
            polygon.b = to_add[1];
            polygon.c = to_add[2];

            // Add the params, checking if any is a color param
            for(size_t j = 0; j < params.size(); ++j) {
                if (params[j].contains("color")) {
                    params[j].replace(" ", "");
                    params[j].replace("color=", "");
                    polygon.color[0] = params[j].toStdString();
                } else {
                    polygon.add_param(params[j].toStdString());
                }
            }

            scene_manager.add_to_scene(polygon);
        } else if (QString::compare(type, "draw") == 0) {
            // Add a line
            vector<c_line> to_add(0);

            for(size_t j = 0; j < points.size()/3-1; ++j) {
                c_line line(points[3*j], points[3*j+1], points[3*j+2], points[3*j+3], points[3*j+4], points[3*j+5]);
                to_add.push_back(line);
            }

            // Add the params, checking if any is a color param
            for(size_t j = 0; j < params.size(); ++j) {
                if (params[j].contains("color=")) {
                    params[j].replace("color=", "");
                    for (size_t k = 0; k < points.size()/3-1; ++k) {
                        to_add[k].color[0] = params[j].toStdString();
                    }
                } else {
                    for (size_t k = 0; k < points.size()/3-1; ++k) {
                        to_add[k].add_param(params[j].toStdString());
                    }
                }
            }

            for (size_t j = 0; j < to_add.size(); ++j) {
                scene_manager.add_to_scene(to_add[j]);
            }

        } else if (QString::compare(type, "box") == 0) {
            // Add a line

            // Get color
            string color;
            vector<string> params_str(0);
            for(size_t j = 0; j < params.size(); ++j) {
                if (params[j].contains("color=")) {
                    params[j].replace("color=", "");
                    color = params[j].toStdString();
                    params.erase(params.begin()+j);
                }
            }

            for(size_t j = 0; j < params.size(); ++j) {
                params_str.push_back(params[j].toStdString());
            }

            scene_manager.add_box(points[0], points[1], points[2], points[3], points[4], points[5], params_str, color);

        } else if (QString::compare(type, "rectangle_x") == 0) {

            // Get color
            string color;
            vector<string> params_str(0);
            for(size_t j = 0; j < params.size(); ++j) {
                if (params[j].contains("color=")) {
                    params[j].replace("color=", "");
                    color = params[j].toStdString();
                    params.erase(params.begin()+j);
                }
            }

            for(size_t j = 0; j < params.size(); ++j) {
                params_str.push_back(params[j].toStdString());
            }

            bool flip = (points[0] > points[2]);

            scene_manager.add_rectangle_x(points[0], points[1], points[2], points[3], points[4], params_str, color, flip);

        } else if (QString::compare(type, "rectangle_y") == 0) {

            // Get color
            string color;
            vector<string> params_str(0);
            for(size_t j = 0; j < params.size(); ++j) {
                if (params[j].contains("color=")) {
                    params[j].replace("color=", "");
                    color = params[j].toStdString();
                    params.erase(params.begin()+j);
                }
            }

            for(size_t j = 0; j < params.size(); ++j) {
                params_str.push_back(params[j].toStdString());
            }

            bool flip = (points[0] > points[2]);

            scene_manager.add_rectangle_y(points[0], points[1], points[2], points[3], points[4], params_str, color, flip);

        } else if (QString::compare(type, "rectangle_z") == 0) {

            // Get color
            string color;
            vector<string> params_str(0);
            for(size_t j = 0; j < params.size(); ++j) {
                if (params[j].contains("color=")) {
                    params[j].replace("color=", "");
                    color = params[j].toStdString();
                    params.erase(params.begin()+j);
                }
            }

            for(size_t j = 0; j < params.size(); ++j) {
                params_str.push_back(params[j].toStdString());
            }

            bool flip = (points[0] > points[2]);

            scene_manager.add_rectangle_z(points[0], points[1], points[2], points[3], points[4], params_str, color, flip);

        } else if (type.contains("sun")) {
            sun.x = points[0];
            sun.y = points[1];
            sun.z = points[2];
        } else if (type.contains("camera")) {
            c_camera camera(points[0], points[1], points[2], points[3], points[4], points[5]);
        } else if (type.contains("bsp")) {
            bsp = true;
        }
    }

    scene_manager.light(sun);

    if (bsp) {
        scene_manager.compile_bsp();
        scene_manager.render_bsp("output.tex", camera);
        cout << "BSP";
    } else {
        scene_manager.render_to_file("output.tex", camera);
    }

}
