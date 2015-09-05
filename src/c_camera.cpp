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

c_tikz_obj* c_camera::project(const c_point& point3d) const {

    c_point proj = utils::project(point3d, *this);

    c_point * projection = (c_point*) point3d.clone();
    projection->x = proj.x;
    projection->y = proj.y;
    projection->z = proj.z;
    projection->twod = true;

    return projection;

}

c_tikz_obj* c_camera::project(const c_line& line3d) const {

    c_point s = utils::project(line3d.sx, line3d.sy, line3d.sz, *this);
    c_point e = utils::project(line3d.ex, line3d.ey, line3d.ez, *this);

    c_line *projection = (c_line*) line3d.clone();

    projection->set_points(s, e);

    return projection;

}

c_tikz_obj* c_camera::project(const c_polygon& polygon3d) const {

    c_point a = utils::project(polygon3d.a.x, polygon3d.a.y, polygon3d.a.z, *this);
    c_point b = utils::project(polygon3d.b.x, polygon3d.b.y, polygon3d.b.z, *this);
    c_point c = utils::project(polygon3d.c.x, polygon3d.c.y, polygon3d.c.z, *this);

    c_polygon *projection = (c_polygon*) polygon3d.clone();
    projection->a = a;
    projection->b = b;
    projection->c = c;

    return projection;

}

c_tikz_obj* c_camera::project(const c_node& node3d) const {

    c_point loc = utils::project(node3d.x, node3d.y, node3d.z, *this);

    c_node *projection = (c_node*) node3d.clone();

    projection->x = loc.x;
    projection->y = loc.y;
    projection->z = loc.z;

    return projection;

}
