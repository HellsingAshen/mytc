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

int ct_sibing_insert_node(
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
        for (first_node = node; first_node->prev->next; first_node = first_node->prev);
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

struct ct_node *ct_first_level_node_re(struct ct_node* root, int level)
{

    struct ct_node*         child           = NULL;
    struct ct_node*         target          = NULL;
    if (level == 0)
    {
        return root;
    } 
    for (child = root->child; child; child = child->next)
    {
        if ((level - 1) <= (ct_get_node_deepth(child) - 1))
        {
            target = ct_first_level_node_re(child, level - 1);
            break;
        }
    }
    
    return target;
}

struct ct_node *ct_first_level_node(const struct ct_root* root, int level)
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

    for (; first; first = first->next)
    {
        if (level <= ct_get_node_deepth(first) - 1)
        {
            node = first;
            break;
        }
    }

    target = ct_first_level_node_re(node, level);

    return target;
}


struct ct_node *ct_get_root(struct ct_node* node)
{
    struct ct_node*         parent          = NULL;
    struct ct_node*         target          = NULL;
    
    for (parent = node->parent, target = node; parent; target = parent, parent = parent->parent);
    
    return target;
}

struct ct_node *ct_bt_child_next(const struct ct_node* node)
{
    struct ct_node*         parent          = NULL;

    assert(NULL != node);
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
    return NULL;
    
}


struct ct_node *ct_bt_get_parent_next_sibling(struct ct_node* node)
{
    struct ct_node*         parent          = NULL;
    struct ct_node*         root            = NULL;

    if (node->next)
    {
        return node;
    }
    
    root = ct_get_root(node);
    parent = node->parent;

    /* grandfather and greadddddfather ...*/
    for (; parent != root; parent = ct_bt_get_parent_next_sibling(parent));

    return (parent ? parent->child : NULL);

}

struct ct_node *ct_bt_get_parent_next(struct ct_node* node)
{
    struct ct_node*         parent          = NULL;
    struct ct_node*         prev            = NULL;

    if (node->next)
    {
        return node->next;
    }
    
    parent = node->parent;

    if (!parent)
    {
        return NULL;
    }

    /* grandfather and greadddddfather ...*/
    for (prev = parent, parent = parent->next; parent; prev = parent, parent = ct_bt_get_parent_next(parent))
    {
        if (ct_node_get_deepth(prev) == ct_node_get_deepth(parent))
        {
            return parent->child; 
        }
    }
    
    return NULL;
}

/* for Breadth traversal */
struct ct_node *ct_bt_next(struct ct_node* node)
{
    struct ct_node*         parent          = NULL;
    struct ct_node*         start           = NULL;
    struct ct_node*         root_node       = NULL;
    struct ct_root          root;
    int                     level           = 0;

    root_node = ct_get_root(node);
    assert(NULL != node);
    if (node->next)
    {
        return node->next;
    }

    parent = node->parent;
    if (!parent)
    {
        goto next_level;
    }

    for (parent = ct_bt_get_parent_next(parent); parent; parent = ct_bt_get_parent_next(parent))
    {
        if (parent->child)
        {
            return parent->child;
        }
    }
    
next_level:
    /* travel at end and travel next level */
    level = ct_get_node_level(node);
    root.node = root_node;

    if (!parent)
    {
        for (start = ct_first_level_node(&root, level); start; start = ct_bt_child_next(start))
        {
            if (start->child)
            {
                return start->child;
            }
        }
    }

    return NULL;
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

#if 0
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
#endif

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

    node = ct_br_sub_get_last(target_node);

    return node;
}


struct ct_node* ct_br_get_last(const struct ct_root* root)
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
    
    return NULL;
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
        next = ct_first_node(node);
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

int ct_merge_tree(
    struct ct_root* root, 
    struct ct_root* sub)
{
    return 0;
}

#define travel(node) 

struct ct_node* ct_node_dfs(struct ct_node* root)
{
    struct ct_node*         child           = NULL;
    if (!root)
    {
        return NULL;
    }

    /* TODO: add your code  to process root */
    travel(root);
    for (child = root->child; child; child = child->next)
    {
        ct_node_dfs(child);
    }

    return NULL;
    
}

struct ct_node* ct_node_bfs(struct ct_root* root)
{
    struct ct_node*         last            = NULL;
    struct ct_node*         node            = NULL;
    int                     is_last         = 1;

    assert(NULL != root);
    last = ct_br_get_last(root);

    for (node = root->node; is_last; node = ct_bt_next(node))
    {
        /* TODO: add code to process node here */
        travel(node);
        
        if (node == last)
        {
            is_last = 0;
        }
    }

    return NULL;
}
#undef travel
