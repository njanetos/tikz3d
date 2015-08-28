#include "c_camera.h"

#include <iostream>

#include "c_point.h"
#include "c_line.h"
#include "c_polygon.h"
#include "c_node.h"

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

    c_point a = utils::project(polygon3d->a.x, polygon3d->a.y, polygon3d->a.z, this);
    c_point b = utils::project(polygon3d->b.x, polygon3d->b.y, polygon3d->b.z, this);
    c_point c = utils::project(polygon3d->c.x, polygon3d->c.y, polygon3d->c.z, this);

    c_polygon * projection = new c_polygon(a.x, a.y, a.z, b.x, b.y, b.z, c.x, c.y, c.z);

    return projection;

}

c_tikz_obj* c_camera::project(c_node * node3d) {

    c_point loc = utils::project(node3d->x, node3d->y, node3d->z, this);

    c_node * projection = new c_node(loc.x, loc.y, loc.z, node3d->text);

    return projection;

}
