#include "utils.h"

#include "c_polygon.h"

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

std::vector<c_tikz_obj*> utils::split(c_point *obj1, c_point *obj2) {
    std::vector<c_tikz_obj*> emp(0);
    return emp;
}

std::vector<c_tikz_obj*> utils::split(c_line *obj1, c_point *obj2) {
    std::vector<c_tikz_obj*> emp(0);
    return emp;
}

std::vector<c_tikz_obj*> utils::split(c_node *obj1, c_point *obj2) {
    std::vector<c_tikz_obj*> emp(0);
    return emp;
}

std::vector<c_tikz_obj*> utils::split(c_polygon *obj1, c_point *obj2) {
    std::vector<c_tikz_obj*> emp(0);
    return emp;
}

std::vector<c_tikz_obj*> utils::split(c_point *obj1, c_line *obj2) {
    std::vector<c_tikz_obj*> emp(0);
    return emp;
}

std::vector<c_tikz_obj*> utils::split(c_line *obj1, c_line *obj2) {
    std::vector<c_tikz_obj*> emp(0);
    return emp;
}

std::vector<c_tikz_obj*> utils::split(c_node *obj1, c_line *obj2) {
    std::vector<c_tikz_obj*> emp(0);
    return emp;
}

std::vector<c_tikz_obj*> utils::split(c_polygon *obj1, c_line *obj2) {
    std::vector<c_tikz_obj*> emp(0);
    return emp;
}

std::vector<c_tikz_obj*> utils::split(c_point *obj1, c_node *obj2) {
    std::vector<c_tikz_obj*> emp(0);
    return emp;
}

std::vector<c_tikz_obj*> utils::split(c_line *obj1, c_node *obj2) {
    std::vector<c_tikz_obj*> emp(0);
    return emp;
}

std::vector<c_tikz_obj*> utils::split(c_node *obj1, c_node *obj2) {
    std::vector<c_tikz_obj*> emp(0);
    return emp;
}

std::vector<c_tikz_obj*> utils::split(c_polygon *obj1, c_node *obj2) {
    std::vector<c_tikz_obj*> emp(0);
    return emp;
}

std::vector<c_tikz_obj*> utils::split(c_point *obj1, c_polygon *obj2) {
    std::vector<c_tikz_obj*> emp(0);
    return emp;
}

std::vector<c_tikz_obj*> utils::split(c_line *obj1, c_polygon *obj2) {
    std::vector<c_tikz_obj*> emp(0);
    return emp;
}

std::vector<c_tikz_obj*> utils::split(c_node *obj1, c_polygon *obj2) {
    std::vector<c_tikz_obj*> emp(0);
    return emp;
}

std::vector<c_tikz_obj*> utils::split(c_polygon *obj1, c_polygon *obj2) {
    std::vector<c_tikz_obj*> emp(0);

    bool a, b, c;
    a = is_above(&obj1->a, obj2);
    b = is_above(&obj1->b, obj2);
    c = is_above(&obj1->c, obj2);

    // Check if obj1 is above obj2, or obj2 is above obj1, otherwise, split 'em
    if (a && b && c) {
        emp.push_back(obj1);
        emp.push_back(obj2);
    } else if (!a && !b && !c) {
        emp.push_back(obj2);
        emp.push_back(obj1);
    } else {
        // find the loner
        char loner = 0;
        if (a && !b && !c) {
            loner = 0;
        } else if (!a && b && !c) {
            loner = 1;
        } else if (!a && !b && c) {
            loner = 2;
        } else if (!a && b && c) {
            loner = 0;
        } else if (a && !b && c) {
            loner = 1;
        } else if (a && b && !c) {
            loner = 2;
        }

    }

    return emp;
}

bool utils::is_above(c_point *point, c_polygon *polygon) {

    c_point normal = polygon->normal();

    real dot = normal*(*point - polygon->c);

    return (dot > 0);

}

