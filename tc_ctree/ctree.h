#ifndef CTREE_H
#define CTREE_H

#ifndef NULL
#define NULL (void*)0
#endif

struct ct_node
{
    struct ct_node *parent;
    struct ct_node *child;          /* first child */
    struct ct_node *prev;           /* prev sibling node. point to tail while node is first node and it's never nil */
    struct ct_node *next;           /* next sibling node. ponit to nil while node is tail. */
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

#define CT_ROOT        (struct ct_root) { NULL, }

extern struct ct_node *ct_next(const struct ct_node *);
extern struct ct_node *ct_prev(const struct ct_node *);

#define API(str) 1
#if API("user use api ")
int ct_parent_insert(
    struct ct_node* parent,
    struct ct_node* node
    );

int ct_sibing_insert(
    struct ct_node* sbiling,
    struct ct_node* node
    );

void ct_init_root(
    struct ct_node* node);

struct ct_node *ct_first_sibling(const struct ct_node *node);

struct ct_node *ct_last_sibling(const struct ct_node *node);

#endif


int ct_is_first_node(const struct ct_node* node);

int ct_is_last_node(const struct ct_node* node);

int ct_is_sole_node(const struct ct_node* node);

int ct_get_deepth(const struct ct_root* ct_root);

int ct_get_node_level(const struct ct_node* node);

int ct_is_bfs_last(
    const struct ct_root* root,
    const struct ct_node* node
    );

struct ct_node* ct_br_get_last(const struct ct_root* root);

struct ct_node *ct_bfs_next(struct ct_node* node);

int ct_get_node_deepth(const struct ct_node* root);

struct ct_node *ct_get_level_first_node_re(struct ct_node* root, int level);

int ct_node_get_deepth(const struct ct_node* ct_node);

struct ct_node *ct_get_level_first_node(const struct ct_root* root, int level);

struct ct_node *ct_get_root(struct ct_node* node);

void ct_erase_subtree(struct ct_root* root);

struct ct_node *ct_get_level_next(const struct ct_node* node);
#endif
