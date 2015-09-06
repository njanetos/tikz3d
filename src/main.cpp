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

    fstream file(argv[1]);

    vector<QString> lines;
    string line;

    while (std::getline(file, line)) {
        if (line.compare("") != 0) {
            lines.push_back(QString::fromUtf8(line.c_str()));
            lines[lines.size()-1].replace(" ", "");
            lines[lines.size()-1].replace("-", "");
            lines[lines.size()-1].replace(";", "");
            lines[lines.size()-1].replace("\\", "");
        }
    }

    QRegularExpression first_reg(".+?(?=\\[|\\()");
    QRegularExpression param_reg("(?<=\\[)(.*)(?=\\])");
    QRegularExpression point_reg("(?<=\\(|\\,)(.*?)(?=\\,|\\))");

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

        // Decide what to add

        if (QString::compare(type, "filldraw", Qt::CaseInsensitive) == 0) {

            // Add a polygon
            vector<c_point> to_add(0);

            for(size_t j = 0; j < points.size()/3; ++j) {
                c_point point(points[3*j], points[3*j+1], points[3*j+2]);
                to_add.push_back(point);
            }

            c_polygon polygon;
            polygon.color[0] = param.toStdString();
            polygon.a = to_add[0];
            polygon.b = to_add[1];
            polygon.c = to_add[2];

            scene_manager.add_to_scene(polygon);
        } else if (QString::compare(type, "sun", Qt::CaseInsensitive) == 0) {
            sun.x = points[0];
            sun.y = points[1];
            sun.z = points[2];
        } else if (QString::compare(type, "camera", Qt::CaseInsensitive) == 0) {
            c_camera camera(points[0], points[1], points[2], points[3], points[4], points[5]);
        }

    }

    scene_manager.light(sun);
    scene_manager.render_to_file("output.tex", camera);

}
