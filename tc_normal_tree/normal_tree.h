#ifndef NORMAL_TREE_H
#define NORMAL_TREE_H

struct nt_node{
    struct nt_node* parent;
    struct nt_node* child;
    struct nt_node* prev;
    struct nt_node* next;
};

struct nt_node* nt_get_root(struct nt_node* node);

#endif
