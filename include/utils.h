#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <iostream>

#include "c_camera.h"
#include "c_point.h"

class utils
{
    public:
        static c_point project(c_point *point3d, c_camera *cam);
        static c_point project(real _x, real _y, real _z, c_camera *cam);
    protected:
    private:
};

#endif // UTILS_H
