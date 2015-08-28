#include "c_camera.h"

#include <iostream>

#include "c_point.h"
#include "c_line.h"
#include "c_polygon.h"

c_camera::c_camera(real pos_x, real pos_y, real pos_z, real tx, real ty, real tz) {
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->pos_z = pos_z;
    this->tx = tx;
    this->ty = ty;
    this->tz = tz;
}

c_camera::~c_camera() {
    //dtor
}

c_tikz_obj* c_camera::project(c_point * point3d) {

    c_point proj = utils::project(point3d, this);

    c_point *projection = new c_point(proj.x, proj.y, proj.z);

    return projection;

}

c_tikz_obj* c_camera::project(c_line * line3d) {

    c_point s = utils::project(line3d->sx, line3d->sy, line3d->sz, this);
    c_point e = utils::project(line3d->ex, line3d->ey, line3d->ez, this);

    c_line * projection = new c_line(s.x, s.y, s.z, e.x, e.y, e.z);

    return projection;

}

c_tikz_obj* c_camera::project(c_polygon * polygon3d) {

}

c_tikz_obj* c_camera::project(c_node * node3d) {

}
