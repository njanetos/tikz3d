#include "c_tree_node.h"

#include "c_tikz_obj.h"
#include "c_polygon.h"

c_tree_node::c_tree_node(std::vector<c_tikz_obj*> process) {

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
                left = new c_tree_node(splitted[0]);

                // Send everything in front of me to the right node
                right = new c_tree_node(splitted[2]);

                // Add everything at my position to my objects
                for (size_t j = 0; j < splitted[1].size(); ++j) {
                    my_objs.push_back(splitted[1][j]);
                }
            }
        }
    }
}

c_tree_node::~c_tree_node() {
    delete left;
    delete right;

    // Delete my own objects
    for (size_t i = 0; i < my_objs.size(); ++i) {
        delete my_objs[i];
    }
}
