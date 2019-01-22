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
        /* add tail */
        first_child->prev->next = node;
        node->prev = first_child->prev;        
        first_child->prev = node;
    }

    node->parent = (parent ? parent : sbiling->parent);
    node->next = NULL;
    
    return ret;
}

int ct_parent_insert(
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

int ct_sibing_insert(
    struct ct_node* sbiling,
    struct ct_node* node
    )
{
    assert((NULL != sbiling) && (NULL != node));

    return ct_insert_node((sbiling->parent) ? (sbiling->parent) : NULL, sbiling, node);
}

struct ct_node *ct_first_sibling(const struct ct_node *node)
{
    struct ct_node*   first_node         = NULL;
    assert(node);

    if (node->parent)
    {
        return node->parent->child;
    }
    else
    {
        for (first_node = (struct ct_node*)node; first_node->prev->next; first_node = first_node->prev);
    } 
    
    return first_node;
}

struct ct_node *ct_last_sibling(const struct ct_node *node)
{
    return (ct_first_sibling(node))->prev;
}

int ct_is_first_node(const struct ct_node* node)
{
    assert(node);
    return (NULL == node->prev->next);
}

int ct_is_last_node(const struct ct_node* node)
{
    assert(node);
    return (NULL == node->next);
}

int ct_is_sole_node(const struct ct_node* node)
{
    return (node == node->prev);
}

/*
 * @ desc : Recursive implementation of getting first node whose level is equal to level under node parent .
 * @ in   :  
 *          parent  -- parent node
 *          level   -- specifed level
 * @ out  : 
 *          return value :target node 
 * @ cautious:  first means the 1th at all node whose level is equal level;
 */
struct ct_node *ct_get_level_first_node_re(struct ct_node* parent, int level)
{

    struct ct_node*         child           = NULL;
    struct ct_node*         target          = NULL;
    if (level == 0)
    {
        return parent;
    } 
    for (child = parent->child; child; child = child->next)
    {
        if ((level - 1) <= (ct_node_get_deepth(child) - 1))
        {
            target = ct_get_level_first_node_re(child, level - 1);
            break;
        }
    }
    
    return target;
}

/*
 * @ desc : get first node whose level is equal to level in common tree root.
 * @ in   :  
 *          root  -- ct_root
 *          level -- specifed level
 * @ out  : 
 *          return value :target node 
 * @ cautious:  first means the 1th at all node whose level is equal level;
 */
struct ct_node *ct_get_level_first_node(const struct ct_root* root, int level)
{
    struct ct_node*         first           = NULL;
    struct ct_node*         node            = NULL;
    struct ct_node*         target          = NULL;
    int                     deepth          = 0;
    deepth = ct_get_deepth(root);
    if (level > deepth - 1)
    {
        return NULL;
    }

    if (!level)
    {
        return root->node;
    }

    first = root->node; 

    /* get first sub tree whose deepth is equal to level + 1 */
    for (; first; first = first->next)
    {
        if (level <= ct_node_get_deepth(first) - 1)
        {
            node = first;
            break;
        }
    }

    target = ct_get_level_first_node_re(node, level);

    return target;
}

struct ct_node *ct_get_root(struct ct_node* node)
{
    struct ct_node*         parent          = NULL;
    
    for (parent = node; parent->parent; parent = parent->parent);
    
    return parent;
}


/*
 * @ desc : get next node which is under the same level of node 
 * @ in:
 * @ out:
 * @ cautious:
 */
struct ct_node *ct_get_level_next(const struct ct_node* node)
{
    struct ct_node*         parent          = NULL;
    struct ct_node*         cousion          = NULL;
    if (node->next)
    {
        return node->next;
    }

    parent = node->parent;
    if (!parent)
    {
        return NULL;
    }

    for (parent = parent->next; parent; parent = parent->next)
    {
        if (parent->child)
        {
            return parent->child;
        }
    }
    
    parent = ct_last_sibling(node->parent);
    for (cousion = ct_get_level_next(parent); cousion; cousion = ct_get_level_next(cousion))
    {
        if (cousion->child)
        {
            return cousion->child;
        }
    }
    return NULL;
}


#define MAX_INT(a, b) ((a > b) ? a : b)
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
        sub_deepth = ct_node_get_deepth(node);
        deepth = MAX_INT(sub_deepth, deepth);
    }
    
    return deepth;
}

/* @ cautious: start form 1 and we don't care sibling 
 *   down ...
 */

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
        sub_deepth = ct_node_get_deepth(node);
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
 * @ desc: erase subtree include child does not include sibling
 * @ in  :
 * @ out :
 * @ cautious:
 */
void _ct_erase(struct ct_node *node)
{
    struct ct_node*         prev            = NULL;
    struct ct_node*         next            = NULL;
    int                     is_last,is_first      = 0;

    if (ct_is_sole_node(node) && node->parent)
    {
        node->parent->child = NULL;
        node->parent = NULL;
        return;
    }
    
    if (ct_is_last_node(node))
    {
        is_last = 1;
    }
    if (ct_is_first_node(node))
    {
        is_first = 1;
    }

    /* process sibling */
    prev = node->prev;
    next = node->next;

    prev->next = next;
    if (is_last)
    {
        next = ct_first_sibling(node);
    }
    next->prev = prev;

    if ( is_last || is_first)
    {
        prev->next = NULL;
    }

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


#define travel(node) 

struct ct_node* ct_node_dfs(struct ct_node* root)
{
    struct ct_node*         child           = NULL;
    if (!root)
    {
        return NULL;
    }

    /* TODO: add your code  to process node */
    travel(root);
    for (child = root->child; child; child = child->next)
    {
        ct_node_dfs(child);
    }

    return NULL;
    
}

void _bfs_travel_level(int level, struct ct_root* root)
{
    struct ct_node* first           = NULL;
    for (first = ct_get_level_first_node(root, level); first; first = ct_get_level_next(first))
    {
        travel(first);
    }
    return;
}

struct ct_node* ct_node_bfs(struct ct_root* root)
{
    int             height          = 0;
    int             i               = 0;
    
    height = ct_get_deepth(root);
    
    for (; i < height; i++)
    {
        _bfs_travel_level(i, root);
    }

    return NULL;
}
#undef travel

#ifndef DESC
#define DESC(str) 0
/* for bfs */
struct ct_node *ct_bfs_next(struct ct_node* node)
{
    return NULL;
}
/* recursive */
int ct_is_bfs_last_re(
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

    ret = ct_is_bfs_last_re(node->parent);
    return ret;

}

int ct_is_bfs_last(
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
    ret = ct_is_bfs_last_re(node->parent);
    return ret;
    
}

/* get deepth sub */
struct ct_node* ct_bfs_sub_get_last(const struct ct_node* root)
{
    struct ct_node*         child           = NULL;
    struct ct_node*         node            = NULL;
    struct ct_node*         target_node     = NULL;
    int                     deepth          = 0;
    int                     max_deepth      = 0;

    assert (NULL != root);

    if (!root->child)
    {
        return (struct ct_node*)root;
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

    node = ct_bfs_sub_get_last(target_node);

    return node;
}


struct ct_node* ct_bfs_get_last(const struct ct_root* root)
{
    struct ct_node*         target_node     = NULL;
    struct ct_node*         node            = NULL;
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

    target_node = ct_bfs_sub_get_last(node);

    return target_node;
}


struct ct_node* ct_depth_traveral(const struct ct_root* root)
{
    /* TODO: fix  depth traveral */
    return NULL;
}

/* here need add your code here. */
struct ct_node* ct_breadth_traveral(const struct ct_root* root)
{
    /* TODO: fix breadth traveral */
    
    return NULL;
}

int ct_merge_tree(
    struct ct_root* root, 
    struct ct_root* sub)
{
    /* TODO : */
    return 0;
}

#endif
