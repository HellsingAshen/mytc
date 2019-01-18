#include <assert.h>
#include "ctree.h"

void ct_init_root(
    struct ct_node* node)
{
    node->prev = node;
    node->next = node->child = node->parent = NULL;
    return;
}

int ct_insert_node(
    struct ct_node* parent,
    struct ct_node* sbiling,
    struct ct_node* node
    )
{
    int                 ret                 = 0;
    struct ct_node*     first_child         = NULL;

    /* empty tree and insert node as root*/
    if (!parent && !sbiling)
    {
        ct_init_root(node);
        return 0;
    }

    /* find 1th child */
    if (parent)
    {
        first_child = parent->child;
    }
    else
    {
        for (first_child = sbiling; first_child->prev->next; first_child = first_child->prev);
    }

    /* if node is 1th node */
    if (!first_child)
    {
        parent->child = node;
        node->prev = node;
    }
    else
    {
        first_child->prev->next = node;
        node->prev = first_child->prev;        
        first_child->prev = node;
    }

    node->parent = parent;
    node->next = NULL;
    
    return ret;
}

int ct_parent_insert_node(
    struct ct_node* parent,
    struct ct_node* node
    )
{
    if (!parent && node)
    {
        /* insert as root */
        ct_init_root(node);
        return 0;
    }

    return  (ct_insert_node(parent, parent->child, node));
}

int ct_sibing_insert_sbiling(
    struct ct_node* sbiling,
    struct ct_node* node
    )
{
    assert((NULL != sbiling) && (NULL != node));

    return ct_insert_node((sbiling->parent) ? (sbiling->parent) : NULL, sbiling, node);
}



struct ct_node *ct_first_node(const struct ct_node *node)
{

    struct ct_node*         first_node         = NULL;

    if (!node)
    {
        return NULL;
    }

    if (node->parent)
    {
        return node->parent->child;
    }
    else
    {
        for (first_node = node->prev; first_node->next; first_node = first_node->prev);
    } 
    
    return first_node;
    
}

struct ct_node *ct_last_node(const struct ct_node *node)
{
    struct ct_node*         first_node         = NULL;

    if (!node)
    {
        return NULL;
    }

    first_node = ct_first_node(node);

    return first_node->prev;
}

int ct_is_first_node(const struct ct_node* node)
{
    return (NULL == node->prev->next);
}

int ct_is_last_node(const struct ct_node* node)
{
    return (NULL == node->next);
}

int ct_is_sole_node(const struct ct_node* node)
{
    return (node == node->prev);
}


struct ct_node *ct_bt_get_first_node(const struct ct_node* node)
{
    struct ct_node*         start           = NULL;
    
    for (start = node; start; start = start->next)
    {
        if (start->child)
        {
            break;
        }
    }
    
/* TODO: @0118 */
    return start->child;
}

/* for Breadth traversal */
struct ct_node *ct_bt_next(const struct ct_node* node)
{
    assert(NULL != node);

    return ((node->next) ? node->next : ct_bt_get_first_node(node));
}

struct ct_node *ct_bt_prev(const struct ct_node* node)
{
    struct ct_node*         pstNode         = NULL;

    assert(NULL != node);

    return ((node->prev && (node->prev != node)) ? node->prev : (pstNode = ct_last_node(node), pstNode->parent));

}


#define MAX_INT(a, b) ((a > b) ? a : b)
int ct_get_node_deepth(const struct ct_node* root)
{
    int                     deepth          = 0;
    int                     sub_deepth      = 0;
    struct ct_node*         child           = NULL;

    
    
    if (!root->child)
    {
        return 1;
    }
    
    for (child = root->child; child; child = child->next)
    {
        sub_deepth = ct_get_node_deepth(child);
        deepth = MAX_INT(sub_deepth, deepth);
    }

    return deepth + 1;
}

/*
 *  @ desc: get ctree deepth 
 *  @ causious: start from 0
 */
int ct_get_deepth(const struct ct_root* ct_root)
{
    int                     deepth          = 0;
    int                     sub_deepth      = 0;
    struct ct_node*         node            = NULL;
    
    assert(NULL != ct_root);

    /* only a root node */
    if (!ct_root->node && ct_is_sole_node(ct_root->node))
    {
        return 0;
    }

    for (node = ct_root->node; node; node = node->next)
    {
        sub_deepth = ct_get_node_deepth(node);
        deepth = MAX_INT(sub_deepth, deepth);
    }
    
    return deepth;
}

/* start form 1 and we don't care sibling */
int ct_node_get_deepth(const struct ct_node* ct_node)
{
    int                     deepth          = 0;
    int                     sub_deepth      = 0;
    struct ct_node*         node            = NULL;
    
    if (!ct_node)
    {
        return 0;
    }

    /* only a root node */
    if (!ct_node->child)
    {
        return 1;
    }

    for (node = ct_node->child; node; node = node->next)
    {
        sub_deepth = ct_get_node_deepth(node);
        deepth = MAX_INT(sub_deepth, deepth);
    }
    
    return (deepth + 1);
}
#undef MAX_INT

int ct_get_node_level(const struct ct_node* node)
{
    int                     level           = 0;
    
    for (; node->parent;  node = node->parent,++level);
    
    return level;
}


/*
 * @ desc:  get ctree first left node
 * @ cautious:  It is not necessarily the deepest node
 */
struct ct_node *ct_first(const struct ct_root* ct_root)
{
    struct ct_node*         node            = NULL;
    struct ct_node*         parent_node     = NULL;
    
    assert((NULL != ct_root) && (NULL != ct_root->node));

    for (node = ct_root->node; node; parent_node = node, node = node->child);

    return parent_node;
}

/*
 * @ desc:  get ctree last  node
 * @ cautious:  It is not necessarily the deepest node
 */
struct ct_node *ct_last(const struct ct_root* ct_root)
{
    struct ct_node*         node            = NULL;
    struct ct_node*         last_node       = NULL;
    struct ct_node*         parent_node     = NULL;
    
    assert((NULL != ct_root) && (NULL != ct_root->node));

    for (node = ct_root->node, last_node = ct_last_node(node); 
        last_node; 
        node = last_node->child, last_node = ct_last_node(node), (last_node ? (parent_node = last_node) : (parent_node = parent_node)));

    return parent_node;
}

#define TRUE    1
#define FALSE   0
/* recursive */
int ct_is_br_last_re(
    struct ct_node* node
    )
{
    int                     ret             = 1;
    struct ct_node*         next            = NULL; 

    if (!node)
    {
        return 1;
    }
    
    if (!ct_is_last_node(node))
    {
        for (next = node->next; next; next = next->next)
        {
            if (next->child)
            {
                /* brother has child */
                return 0;
            }
        }
    }

    ret = ct_is_br_last_re(node->parent);
    return ret;

}


int ct_is_br_last(
    const struct ct_root* root,
    const struct ct_node* node
    )
{
    int                     ret             = 0;
    int                     deepth          = 0;
    int                     level           = 0;
    
    if (!ct_is_last_node(node))
    {
        return 0;
    }
    
    deepth = ct_get_deepth(root);
    level  = ct_get_node_level(node);

    if (level != deepth - 1)
    {
        return 0;
    }

    /* recursive */
    ret = ct_is_br_last_re(node->parent);
    return ret;
    
}

/* get deepth sub */
#define MAX_INT(a, b) ((a > b) ? a : b)
struct ct_node* ct_br_sub_get_last(const struct ct_node* root)
{
    struct ct_node*         child           = NULL;
    struct ct_node*         node            = NULL;
    struct ct_node*         target_node     = NULL;
    int                     deepth          = 0;
    int                     max_deepth      = 0;

    assert (NULL != root);

    if (!root->child)
    {
        return root;
    }

    for (child = root->child; child; child = child->next)
    {
       
        deepth = ct_node_get_deepth(child);
        if (deepth >= max_deepth)
        {
            max_deepth = deepth;
            target_node = child;
        }
    }

    node = ct_br_sub_get_last(target_node);

    return node;
}


struct ct_node* ct_br_get_last(const struct ct_root* root)
{
    struct ct_node*         target_node     = NULL;
    struct ct_node*         node            = NULL;
    struct ct_node*         child           = NULL;
    int                     deepth          = 0;
    int                     max_deepth      = 0;

    node = root->node;
    /* if root has sibling, start from first node */
    if (!ct_is_sole_node(node))     
    {
        for (; node; node = node->next)
        {
            deepth = ct_node_get_deepth(node);
            if (deepth >= max_deepth)
            {
                max_deepth = deepth;
                target_node = node;
            }
        }
    }

    target_node = ct_br_sub_get_last(node);

    return target_node;
}
#undef MAX_INT
#undef TRUE
#undef FALSE


struct ct_node* ct_depth_traveral(const struct ct_root* root)
{
    /* TODO: fix  depth traveral */
    return NULL;
}

/* here need add your code here. */
struct ct_node* ct_breadth_traveral(const struct ct_root* root)
{
    /* TODO: fix breadth traveral */
    
    struct ct_node*         last            = NULL;
    struct ct_node*         next            = NULL;
    struct ct_node*         node            = NULL;

    assert(NULL != root);
    last = ct_br_get_last(root->node);
    
    for (node = root->node; node != last; node = ct_bt_next(node))
    {

    }
    
    return NULL;
}

/*
 * @ desc: erase parent prev next
 * @ in  :
 * @ out :
 * @ cautious:
 */
void _ct_erase(struct ct_node *node)
{
    struct ct_node*         prev            = NULL;
    struct ct_node*         next            = NULL;

    if (ct_is_sole_node(node) && node->parent)
    {
        node->parent->child = NULL;
        node->parent = NULL;
        return;
    }

    /* process sibling */
    prev = node->prev;
    next = node->next;

    prev->next = next;

    if (ct_is_last_node(node))
    {
        next = ct_first_node(node);
    }
    next->prev = prev;


    if (ct_is_first_node(node) && node->parent)
    {
        node->parent->child = next;
    }

    node->parent = NULL;
    node->prev = NULL;
    node->next = NULL;
    
    return;
}

void ct_erase_subtree(struct ct_root* root)
{
    _ct_erase((root->node));

    return;
}

void ct_erase_leaf(struct ct_node *node)
{
    assert(NULL == node->child);

    _ct_erase(node);

    return;
}

int ct_merge_tree(
    struct ct_root* root, 
    struct ct_root* sub)
{
    return 0;
}
