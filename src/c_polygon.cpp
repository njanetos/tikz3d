#include "c_polygon.h"

#include "c_camera.h"
#include "c_line.h"

c_polygon::c_polygon() {
    //ctor
}

c_polygon::c_polygon(real ax,
                     real ay,
                     real az,
                     real bx,
                     real by,
                     real bz,
                     real cx,
                     real cy,
                     real cz) {

    a.x = ax;
    a.y = ay;
    a.z = az;
    b.x = bx;
    b.y = by;
    b.z = bz;
    c.x = cx;
    c.y = cy;
    c.z = cz;
}

c_polygon::c_polygon(c_point a, c_point b, c_point c) {
    this->a = a;
    this->b = b;
    this->c = c;
}

c_polygon::~c_polygon() {
    //dtor
}


c_tikz_obj* c_polygon::project(c_camera *cam) {
    return cam->project(this);
}

std::string c_polygon::write() {
    std::stringstream sstm;

    sstm << "\\filldraw[";
    if (params.size() > 0) {
        sstm << params[0];
    }
    for (size_t i = 1; i < params.size(); ++i) {
        sstm << ", " << params[i];
    }
    sstm << "] (" << a.x << ", " << a.y << ") -- (" << b.x << ", " << b.y << ") -- (" << c.x << ", " << c.y << ") -- (" << a.x << ", " << a.y << ");\n";

    return sstm.str();
}

c_tikz_obj* c_polygon::clone() {

    c_polygon *polygon = new c_polygon(a.x, a.y, a.z, b.x, b.y, b.z, c.x, c.y, c.z);
    polygon->add_params(params);
    return polygon;

}

c_point c_polygon::normal() {
    real x, y, z;

    x = (a.y - c.y)*(b.z - c.z) - (a.z - c.z)*(b.y - c.y);
    y = -1*((a.x - c.x)*(b.z - c.z) - (a.z - c.z)*(b.x - c.x));
    z = (a.x - c.x)*(b.y - c.y) - (a.y - c.y)*(b.x - c.x);

    c_point point(x, y, z);
    return point.normalize();
}

std::vector< std::vector<c_tikz_obj*> > c_polygon::split(c_polygon *against) {

    std::vector< std::vector<c_tikz_obj*> > ret(3);

    // Check each point individually

    char loc_a, loc_b, loc_c;

    loc_a = utils::is_located(&a, against);
    loc_b = utils::is_located(&b, against);
    loc_c = utils::is_located(&c, against);

    // Check if we're above or below or inside
    if (loc_a == loc_b && loc_b == loc_c) {
        ret[loc_a].push_back(clone());
        return ret;
    }

    // Check if point a is barely touching
    if (loc_a == 1 && loc_b == loc_c) {
        ret[loc_b].push_back(clone());
        return ret;
    }

    // Check if point b is barely touching
    if (loc_b == 1 && loc_a == loc_c) {
        ret[loc_c].push_back(clone());
        return ret;
    }

    // Check if point c is barely touching
    if (loc_c == 1 && loc_b == loc_a) {
        ret[loc_a].push_back(clone());
        return ret;
    }

    // Check if a and b are barely touching
    if (loc_a == 1 && loc_b == 1) {
        ret[loc_c].push_back(clone());
        return ret;
    }

    // Check if a and c are barely touching
    if (loc_a == 1 && loc_c == 1) {
        ret[loc_b].push_back(clone());
        return ret;
    }

    // Check if b and c are barely touching
    if (loc_b == 1 && loc_c == 1) {
        ret[loc_a].push_back(clone());
        return ret;
    }

    // Check if 1 point touching, one above, one below
    if (loc_a == 1 || loc_b == 1 || loc_c == 1) {
        c_line line;
        c_point split1, split2;
        if (loc_a == 1) {
            split1 = b;
            split2 = c;
        }
        if (loc_b == 1) {
            split1 = a;
            split2 = c;
        }
        if (loc_c == 1) {
            split1 = a;
            split2 = b;
        }

        line.set_points(split1, split2);

        // Split the line
        real split_pos = utils::get_split_point(line, *against);

        c_point split_point = split1*split_pos + split2*(1-split_pos);

        c_polygon * polygon1 = (c_polygon*) this->clone();
        c_polygon * polygon2 = (c_polygon*) this->clone();

        if (loc_a == 1) {
            polygon1->a = a;
            polygon1->b = b;
            polygon1->c = split_point;
            polygon2->a = a;
            polygon2->b = c;
            polygon2->c = split_point;
        }
        if (loc_b == 1) {
            polygon1->a = b;
            polygon1->b = c;
            polygon1->c = split_point;
            polygon2->a = b;
            polygon2->b = a;
            polygon2->c = split_point;
        }
        if (loc_c == 1) {
            polygon1->a = c;
            polygon1->b = b;
            polygon1->c = split_point;
            polygon2->a = c;
            polygon2->b = a;
            polygon2->c = split_point;
        }

        ret[0].push_back(polygon1);
        ret[2].push_back(polygon2);

        return ret;
    }

    // Remaining cases: Two points above, one point below
    c_line line1, line2;
    bool two_above;

    if (loc_a == 0 && loc_b == 2 && loc_c == 2) {
        // Split ba and ca against the polygon
        line1.set_points(b, a);
        line2.set_points(c, a);
        two_above = true;
    }

    if (loc_a == 2 && loc_b == 0 && loc_c == 2) {
        // Split ab and cb against the polygon
        line1.set_points(a, b);
        line2.set_points(c, b);
        two_above = true;
    }

    if (loc_a == 2 && loc_b == 2 && loc_c == 0) {
        // Split ac and bc against the polygon
        line1.set_points(a, c);
        line2.set_points(b, c);
        two_above = true;
    }

    if (loc_a == 2 && loc_b == 0 && loc_c == 0) {
        // Split ba and ca against the polygon
        line1.set_points(b, a);
        line2.set_points(c, a);
        two_above = false;
    }

    if (loc_a == 0 && loc_b == 2 && loc_c == 0) {
        // Split ab and cb against the polygon
        line1.set_points(a, b);
        line2.set_points(c, b);
        two_above = false;
    }

    if (loc_a == 0 && loc_b == 0 && loc_c == 2) {
        // Split ac and bc against the polygon
        line1.set_points(a, c);
        line2.set_points(b, c);
        two_above = false;
    }

    std::vector< std::vector<c_tikz_obj*> > line1_split(3);
    std::vector< std::vector<c_tikz_obj*> > line2_split(3);

    line1_split = line1.split(against);
    line2_split = line2.split(against);

    int loc;
    if (two_above) {
        loc = 2;
    } else {
        loc = 0;
    }

    c_point point_top(((c_line*)line1_split[loc][0])->ex,
                      ((c_line*)line1_split[loc][0])->ey,
                      ((c_line*)line1_split[loc][0])->ez);

    c_point point_left(((c_line*)line1_split[loc][0])->sx,
                       ((c_line*)line1_split[loc][0])->sy,
                       ((c_line*)line1_split[loc][0])->sz);

    c_point point_right(((c_line*)line2_split[loc][0])->sx,
                        ((c_line*)line2_split[loc][0])->sy,
                        ((c_line*)line2_split[loc][0])->sz);

    c_point bottom_left(((c_line*)line1_split[2-loc][0])->sx,
                        ((c_line*)line1_split[2-loc][0])->sy,
                        ((c_line*)line1_split[2-loc][0])->sz);

    c_point bottom_right(((c_line*)line2_split[2-loc][0])->sx,
                         ((c_line*)line2_split[2-loc][0])->sy,
                         ((c_line*)line2_split[2-loc][0])->sz);

    c_polygon * polygon1 = (c_polygon*) this->clone();
    c_polygon * polygon2 = (c_polygon*) this->clone();
    c_polygon * polygon3 = (c_polygon*) this->clone();

    polygon1->a = point_top;
    polygon1->b = point_left;
    polygon1->c = point_right;

    polygon2->a = bottom_left;
    polygon2->b = point_left;
    polygon2->c = point_right;

    polygon3->a = bottom_right;
    polygon3->b = bottom_left;
    polygon3->c = point_right;

    ret[2-loc].push_back(polygon1);
    ret[loc].push_back(polygon2);
    ret[loc].push_back(polygon3);

    return ret;
}

bool c_polygon::can_split_against() {
    return true;
}

c_polygon c_polygon::get_plane() {
    c_polygon polygon(a, b, c);
    return polygon;
}

bool c_polygon::can_light() {
    return true;
}

std::ostream& c_polygon::print(std::ostream& stream) const {
    stream << "c_polygon: (" << a.x << ", " << a.y << ", " << a.z << ") -- (" << b.x << ", " << b.y << ", " << b.z << ") -- (" << c.x << ", " << c.y << ", " << c.z << ").\n";
    return stream;
}

std::ostream& operator<< (std::ostream& stream, const c_polygon& obj) {
    obj.print(stream);
    return stream;
}

