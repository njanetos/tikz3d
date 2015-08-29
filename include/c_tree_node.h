#ifndef C_TREE_NODE_H
#define C_TREE_NODE_H

#include "common.h"

class c_tikz_obj;

class c_tree_node
{
    public:
        c_tree_node();
        virtual ~c_tree_node();

        void split_me();

        c_tree_node *left;
        c_tree_node *right;
        size_t id;
        std::vector<c_tikz_obj*> objs;
    protected:
    private:
};

#endif // C_TREE_NODE_H
