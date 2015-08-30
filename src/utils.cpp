#include "utils.h"

#include "c_polygon.h"

char utils::is_located(c_point *point, c_polygon *polygon) {

    c_point normal = polygon->normal();

    real dot = normal*(*point - polygon->c);

    // Above, at, or below?
    if (dot > PRECISION) {
        return 0;
    } else if (dot < PRECISION) {
        return 2;
    } else {
        return 1;
    }

}

c_point utils::project(c_point *point3d, c_camera *cam) {

    return project(point3d->x, point3d->y, point3d->z, cam);

}

c_point utils::project(real _x, real _y, real _z, c_camera *cam) {

    real dx, dy, dz;

    real x = _x - cam->pos_x;
    real y = _y - cam->pos_y;
    real z = _z - cam->pos_z;

    real cx = cos(cam->tx);
    real cy = cos(cam->ty);
    real cz = cos(cam->tz);

    real sx = sin(cam->tx);
    real sy = sin(cam->ty);
    real sz = sin(cam->tz);

    dx = cy*(sz*y + cz*x) - sy*z;
    dy = sx*(cy*z + sy*(sz*y + cz*x)) + cx*(cz*y - sz*x);
    dz = cx*(cy*z + sy*(sz*y + cz*x)) - sx*(cz*y - sz*x);

    real bx = 48*dx/dz;
    real by = 48*dy/dz;

    c_point point(bx, by);

    return point;

}
