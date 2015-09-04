#include "c_tree_node.h"

#include "c_tikz_obj.h"
#include "c_polygon.h"

c_tree_node::c_tree_node(std::vector<c_tikz_obj*> process, size_t depth) {

    left = nullptr;
    right = nullptr;

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

                if (splitted[0].size() > 0) {
                    // Send everything behind me to the left node
                    left = new c_tree_node(splitted[0], depth+1);
                }
                if (splitted[2].size() > 0) {
                    // Send everything in front of me to the right node
                    right = new c_tree_node(splitted[2], depth+1);
                }

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
    if (!my_objs[0]->can_split_against()) {
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
            if (left != nullptr) {
                left->render(stream, cam);
            }
            for (size_t i = 0; i < proj_objs.size(); ++i) {
                stream << proj_objs[i]->write();
            }
            if (right != nullptr) {
                right->render(stream, cam);
            }
        } else if (loc == 0) {
            // Otherwise, render everything in the right node first
            if (right != nullptr) {
                right->render(stream, cam);
            }
            for (size_t i = 0; i < proj_objs.size(); ++i) {
                stream << proj_objs[i]->write();
            }
            if (left != nullptr) {
                left->render(stream, cam);
            }
        } else {
            // Otherwise, don't render anything at my node!
            if (right != nullptr) {
                right->render(stream, cam);
            }
            if (left != nullptr) {
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

    // New projection
    for (size_t i = 0; i < my_objs.size(); ++i) {
        proj_objs.push_back(my_objs[i]->project(&cam));
    }

    // Project mah children
    if (left != nullptr) {
        left->project(cam);
    }
    if (right != nullptr) {
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
