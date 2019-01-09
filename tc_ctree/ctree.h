#ifndef CTREE_H
#define CTREE_H

#ifndef NULL
#define NULL (void*)0
#endif

#if 0
struct ctree_node{
    struct ctree_node* parent;
    struct ctree_node* child;
    struct ctree_node* prev;
    struct ctree_node* next;
};
#endif
#if 0
struct tagCTreeNode_S{
    struct tagCTreeNode_S* pstParent;
    struct tagCTreeNode_S* pstChild;
    struct tagCTreeNode_S* pstPrev;
    struct tagCTreeNode_S* pstNext;
};

typedef tagCTreeNode_S  CTreeNode_S;
#endif

struct ct_node
{
    struct ct_node *parent;
    struct ct_node *child;          /* first child */
    struct ct_node *prev;           /* prev node. point to tail while node is first node and it's never nil */
    struct ct_node *next;           /* next node. ponit to nil while node is tail. */
};

struct ct_root
{
    struct ct_node* node;
};

#ifndef offsetof
#define offsetof(type, member) (size_t)&(((type*)0)->member)
#endif

#ifndef container_of
#define container_of(ptr, type, member) ({ \
     const typeof( ((type *)0)->member ) *__mptr = (ptr); \
     (type *)( (char *)__mptr - offsetof(type,member) );})
#endif

#define CT_EMPTY_ROOT(root) ((root)->rb_node == NULL)

extern struct ct_node *ct_next(const struct ct_node *);
extern struct ct_node *ct_prev(const struct ct_node *);
extern struct ct_node *ct_first(const struct ct_root *);
extern struct ct_node *ct_last(const struct ct_root *);
#endif
