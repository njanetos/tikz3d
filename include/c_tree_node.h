#ifndef C_TREE_NODE_H
#define C_TREE_NODE_H

#include "common.h"
#include "utils.h"

class c_tikz_obj;
class c_camera;

class c_tree_node
{
    public:
        c_tree_node(std::vector<c_tikz_obj*> process, size_t depth);
        virtual ~c_tree_node();

        c_tree_node *left;
        c_tree_node *right;

        std::vector<c_tikz_obj*> my_objs;
        std::vector<c_tikz_obj*> proj_objs;

        std::ostream& render(std::ostream& stream, c_camera& cam) const;

        void project(c_camera& cam);

        size_t depth;
    protected:
    private:

};

std::ostream& operator<< (std::ostream& stream, const c_tree_node& obj);

#endif // C_TREE_NODE_H
