#include "c_tree_node.h"

#include "c_tikz_obj.h"
#include "c_polygon.h"

c_tree_node::c_tree_node(std::vector<c_tikz_obj*> process, size_t depth) {

    left = NULL;
    right = NULL;

    this->depth = depth;

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
    if (index == -1 || process.size() == 1) {
        for (size_t i = 0; i < process.size(); ++i) {
            my_objs.push_back(process[i]->clone());
        }
    } else {
        // We have a splittable object.
        // Add it to my objects.
        my_objs.push_back(process[index]->clone());

        // Get my plane
        c_polygon plane = my_objs[0]->get_plane();

        std::vector<c_tikz_obj*> to_left;
        std::vector<c_tikz_obj*> to_right;

        // Split the rest against me
        for (size_t i = 0; i < process.size(); ++i) {
            if ((int) i != index) {
                std::vector< std::vector<c_tikz_obj*> > splitted = process[i]->split(&plane);

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
        char loc = utils::is_located(cam.pos_x, cam.pos_y, cam.pos_z, &plane);

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
        proj_objs.push_back(my_objs[i]->project(&cam));
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

    if (obj.left != nullptr) {
        stream << *obj.left;
    }
    if (obj.right != nullptr) {
        stream << *obj.right;
    }

    return stream;
}
