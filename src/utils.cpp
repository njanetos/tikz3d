#include "utils.h"

#include "c_polygon.h"
#include "c_line.h"

real utils::det2(real a, real b,
                 real c, real d) {
    return a*d - b*c;
}

real utils::det3(real a, real b, real c,
                 real d, real e, real f,
                 real g, real h, real k) {
    return a*det2(e, f, h, k) - b*det2(d, f, g, k) + c*det2(d, e, g, h);
}

real utils::det4(real a, real b, real c, real d,
                 real e, real f, real g, real h,
                 real i, real j, real k, real l,
                 real m, real n, real o, real p) {
    return a*det3(f, g, h, j, k, l, n, o, p) - b*det3(e, g, h, i, k, l, m, o, p) + c*det3(e, f, h, i, j, l, m, n, p) - d*det3(e, f, g, i, j, k, m, n, o);
}

char utils::is_located(const c_point& point, const c_polygon& polygon) {

    c_point normal = polygon.normal();

    real dot = normal*(point - polygon.c);

    // Above, at, or below?
    if (dot > PRECISION) {
        return 0;
    } else if (dot < -1*PRECISION) {
        return 2;
    } else {
        return 1;
    }

}

char utils::is_located(real x, real y, real z, const c_polygon& polygon) {

    c_point point(x, y, z);

    return is_located(point, polygon);

}

real utils::get_split_point(const c_line& line, const c_polygon& polygon) {

    real t;

    t = -1*utils::det4(1, 1, 1, 1,
                       polygon.a.x, polygon.b.x, polygon.c.x, line.sx,
                       polygon.a.y, polygon.b.y, polygon.c.y, line.sy,
                       polygon.a.z, polygon.b.z, polygon.c.z, line.sz);

    t = t / utils::det4(1, 1, 1, 0,
                        polygon.a.x, polygon.b.x, polygon.c.x, line.ex - line.sx,
                        polygon.a.y, polygon.b.y, polygon.c.y, line.ey - line.sy,
                        polygon.a.z, polygon.b.z, polygon.c.z, line.ez - line.sz);

    return t;
}

c_point utils::project(const c_point& point3d, const c_camera& cam) {

    return project(point3d.x, point3d.y, point3d.z, cam);

}

c_point utils::project(real _x, real _y, real _z, const c_camera& cam) {

    real dx, dy, dz;

    real x = _x - cam.pos_x;
    real y = _y - cam.pos_y;
    real z = _z - cam.pos_z;

    real cx = cos(cam.tx);
    real cy = cos(cam.ty);
    real cz = cos(cam.tz);

    real sx = sin(cam.tx);
    real sy = sin(cam.ty);
    real sz = sin(cam.tz);

    dx = cy*(sz*y + cz*x) - sy*z;
    dy = sx*(cy*z + sy*(sz*y + cz*x)) + cx*(cz*y - sz*x);
    dz = cx*(cy*z + sy*(sz*y + cz*x)) - sx*(cz*y - sz*x);

    real bx = 48*dx/dz;
    real by = 48*dy/dz;

    c_point point(bx, by);

    return point;

}
