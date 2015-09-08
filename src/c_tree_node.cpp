#include "c_tree_node.h"

#include "c_tikz_obj.h"
#include "c_polygon.h"

c_tree_node::c_tree_node(std::vector<c_tikz_obj*> process, size_t depth) {

    left = NULL;
    right = NULL;

    this->depth = depth;

    // Take all the stuff in 'process', split it up, create the appropriate nodes, (keeping the first one), delete the rest.

    // Find all split-againstable objects
    std::vector<c_tikz_obj*> split_againstable;
    for (size_t i = 0; i < process.size(); ++i) {
        if (process[i]->can_split_against()) {
            split_againstable.push_back(process[i]);
        }
    }

    // Are there no splittable objects remaining?
    // Keep them all
    if (split_againstable.size() == 0) {
        for (size_t i = 0; i < process.size(); ++i) {
            my_objs.push_back(process[i]->clone());
        }
    } else {

        // We need to figure out which splittable object to use
        size_t index;

        // Check against the rest to see which splits
        size_t best_index = 0;
        size_t best_val = -1;
        for (size_t i = 0; i < split_againstable.size(); ++i) {
            size_t val = 0;
            c_polygon plane = split_againstable[i]->get_plane();
            for (size_t j = 0; j < process.size(); ++j) {
                if (process[j] != split_againstable[i]) {
                    if (process[j]->will_split(plane)) {
                        ++val;
                    }
                }
            }
            if (val < best_val) {
                best_index = i;
                best_val = val;
            }

            if (val < process.size()/20) {
                best_index = i;
                break;
            }
        }

        index = best_index;

        // We have a splittable object.
        // Add it to my objects.
        my_objs.push_back(process[index]->clone());

        // Get my plane
        c_polygon plane = my_objs[0]->get_plane();

        std::vector<c_tikz_obj*> to_left;
        std::vector<c_tikz_obj*> to_right;

        // Split the rest against me
        for (size_t i = 0; i < process.size(); ++i) {
            if (i != index) {
                std::vector< std::vector<c_tikz_obj*> > splitted = process[i]->split(plane);

                for (size_t j = 0; j < splitted[0].size(); ++j) {
                    to_left.push_back(splitted[0][j]);
                }

                for (size_t j = 0; j < splitted[2].size(); ++j) {
                    to_right.push_back(splitted[2][j]);
                }

                // Add everything at my position to my objects
                for (size_t j = 0; j < splitted[1].size(); ++j) {
                    my_objs.push_back(splitted[1][j]);
                }
            }
        }

        // Send everything we need to to the left and right nodes
        // They will be cloned and deleted

        if (to_left.size() > 0) {
            left = new c_tree_node(to_left, depth+1);
        }

        if (to_right.size() > 0) {
            right = new c_tree_node(to_right, depth+1);
        }


    }

    // Delete all processed objects
    for (size_t i = 0; i < process.size(); ++i) {
        delete process[i];
    }
}

c_tree_node::~c_tree_node() {
    delete left;
    delete right;

    // Delete my own objects
    for (size_t i = 0; i < my_objs.size(); ++i) {
        delete my_objs[i];
    }

    for (size_t i = 0; i < proj_objs.size(); ++i) {
        delete proj_objs[i];
    }
}

std::ostream& c_tree_node::render(std::ostream& stream, c_camera& cam) const {

    // Are we a leaf node?
    if (left == NULL && right == NULL) {
        // Render everything in me
        for (size_t i = 0; i < proj_objs.size(); ++i) {
            stream << proj_objs[i]->write();
        }
    } else {
        // Otherwise, we need to do more work
        c_polygon plane = my_objs[0]->get_plane();
        char loc = utils::is_located(cam.pos_x, cam.pos_y, cam.pos_z, plane);

        // If we're in front render everything in the left node first
        if (loc == 2) {
            if (left != NULL) {
                left->render(stream, cam);
            }
            for (size_t i = 0; i < proj_objs.size(); ++i) {
                stream << proj_objs[i]->write();
            }
            if (right != NULL) {
                right->render(stream, cam);
            }
        } else if (loc == 0) {
            // Otherwise, render everything in the right node first
            if (right != NULL) {
                right->render(stream, cam);
            }
            for (size_t i = 0; i < proj_objs.size(); ++i) {
                stream << proj_objs[i]->write();
            }
            if (left != NULL) {
                left->render(stream, cam);
            }
        } else {
            // Otherwise, don't render anything at my node!
            if (right != NULL) {
                right->render(stream, cam);
            }
            if (left != NULL) {
                left->render(stream, cam);
            }
        }
    }

    return stream;
}

void c_tree_node::project(c_camera& cam) {

    // Delete current projection
    for (size_t i = 0; i < proj_objs.size(); ++i) {
        delete proj_objs[i];
    }
    proj_objs.resize(0);

    // New projection
    for (size_t i = 0; i < my_objs.size(); ++i) {
        // Backface culling
        if (my_objs[i]->can_split_against()) {
            c_point norm = my_objs[i]->get_plane().normal();
            c_point cam_point(cam.pos_x, cam.pos_y, cam.pos_z);

            if (cam_point*norm < 0) {
                proj_objs.push_back(my_objs[i]->project(cam));
            }
        } else {
            proj_objs.push_back(my_objs[i]->project(cam));
        }

    }

    // Project mah children
    if (left != NULL) {
        left->project(cam);
    }
    if (right != NULL) {
        right->project(cam);
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

    if (obj.left != NULL) {
        stream << *obj.left;
    }
    if (obj.right != NULL) {
        stream << *obj.right;
    }

    return stream;
}
