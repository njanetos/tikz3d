#include "c_tree_node.h"

#include "c_tikz_obj.h"
#include "c_polygon.h"

c_tree_node::c_tree_node(std::vector<c_tikz_obj*> process, size_t depth) {

    this->depth = depth;

    // Nothing yet allocated
    left_alloc = false;
    right_alloc = false;

    // Take all the stuff in 'process', split it up, create the appropriate nodes, (keeping the first one), delete the rest.

    // Find the first split-againstable object
    int index = -1;
    for (size_t i = 0; i < process.size(); ++i) {
        if (process[i]->can_split_against()) {
            index = i;
            break;
        }
    }

    // Are there no splittable objects remaining?
    // Keep them all
    if (index == -1) {
        for (size_t i = 0; i < process.size(); ++i) {
            my_objs.push_back(process[i]);
        }
    } else {
        // We have a splittable object.
        // Add it to my objects.
        my_objs.push_back(process[index]);

        // Get my plane
        c_polygon plane = my_objs[0]->get_plane();

        // Split the rest against me
        for (size_t i = 0; i < process.size(); ++i) {
            if ((int) i != index) {
                std::vector< std::vector<c_tikz_obj*> > splitted = process[i]->split(&plane);
                // Send everything behind me to the left node
                left = new c_tree_node(splitted[0], depth+1);
                left_alloc = true;

                // Send everything in front of me to the right node
                right = new c_tree_node(splitted[2], depth+1);
                right_alloc = true;

                // Add everything at my position to my objects
                for (size_t j = 0; j < splitted[1].size(); ++j) {
                    my_objs.push_back(splitted[1][j]);
                }

                // Delete the splitted object
                delete process[i];
            }
        }
    }
}

c_tree_node::~c_tree_node() {
    if (left_alloc) {
        delete left;
    }
    if (right_alloc) {
        delete right;
    }

    // Delete my own objects
    for (size_t i = 0; i < my_objs.size(); ++i) {
        delete my_objs[i];
    }
}

std::ostream& operator<< (std::ostream& stream, const c_tree_node& obj) {

    for (size_t i = 0; i < obj.depth; ++i) {
        stream << "-";
    }

    stream << "Node size: " << obj.my_objs.size() << "\n";

    for (size_t i = 0; i < obj.my_objs.size(); ++i) {
        stream << *(obj.my_objs[i]);
    }

    if (obj.left_alloc) {
        stream << "Node size: " << obj.my_objs.size() << "\n" << *obj.left << *obj.right;
    } else {
        stream << "Node size: " << obj.my_objs.size() << "\n";
    }

    return stream;
}
