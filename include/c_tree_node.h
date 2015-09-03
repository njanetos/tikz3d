#ifndef C_TREE_NODE_H
#define C_TREE_NODE_H

#include "common.h"

class c_tikz_obj;

class c_tree_node
{
    public:
        c_tree_node(std::vector<c_tikz_obj*> process, size_t depth);
        virtual ~c_tree_node();

        c_tree_node *left;
        c_tree_node *right;

        std::vector<c_tikz_obj*> my_objs;

        bool left_alloc, right_alloc;
        size_t depth;
    protected:
    private:

};

std::ostream& operator<< (std::ostream& stream, const c_tree_node& obj);

#endif // C_TREE_NODE_H
