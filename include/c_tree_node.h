#ifndef C_TREE_NODE_H
#define C_TREE_NODE_H

#include "common.h"

class c_tikz_obj;

class c_tree_node
{
    public:
        c_tree_node(std::vector<c_tikz_obj*> process);
        virtual ~c_tree_node();

        c_tree_node *left;
        c_tree_node *right;

        std::vector<c_tikz_obj*> my_objs;

    protected:
    private:
};

#endif // C_TREE_NODE_H
