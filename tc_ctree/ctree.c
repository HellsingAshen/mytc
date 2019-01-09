#include <assert.h>
#include "ctree.h"

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
        sbiling = node;
        return 0;
    }

    /* find 1th child */
    if (parent)
    {
        first_child = parent->child;
    }
    else
    {
        for (first_child = sbiling->prev; first_child->next; first_child = first_child->prev);
    }

    /* if node is 1th node */
    if (!first_child)
    {
        parent->child = node;
        node->prev = node;
    }
    else
    {
        node->prev = first_child->prev;        
        first_child->prev->next = node;
        first_child->prev = node;
    }

    node->parent = parent;
    node->next = NULL;
    
    return ret;
}

int ct_insert_sbiling(
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

/* for Breadth traversal */
struct ct_node *ct_bt_next(const struct ct_node* node)
{
    struct ct_node*         pstNode         = NULL;

    assert(NULL != node);

    return ((node->next) ? node->next : (pstNode = ct_first_node(node), pstNode->child));
}

struct ct_node *ct_bt_prev(const struct ct_node* node)
{
    struct ct_node*         pstNode         = NULL;

    assert(NULL != node);

    return ((node->prev && (node->prev != node)) ? node->prev : (pstNode = ct_last_node(node), pstNode->parent));

}

struct ct_node *ct_first(const struct ct_root* ct_root)
{
    struct ct_node*         node            = NULL;
    struct ct_node*         parent_node     = NULL;
    
    assert((NULL != ct_root) && (NULL != ct_root->node));

    for (node = ct_root->node; node; parent_node = node, node = node->child);

    return parent_node;
}

struct ct_node *ct_last(const struct ct_root* ct_root)
{
    struct ct_node*         node            = NULL;
    struct ct_node*         last_node       = NULL;
    struct ct_node*         parent_node     = NULL;
    
    assert((NULL != ct_root) && (NULL != ct_root->node));

    for (node = ct_root->node, last_node = ct_last_node(node); 
        last_node; 
        node = last_node->child, last_node = ct_last_node(node), parent_node = last_node);

    return parent_node;
}

struct ct_node* ct_depth_traveral(const struct ct_root* root)
{
    /* TODO: fix  depth traveral */
    return NULL;
}
struct ct_node* ct_breadth_traveral(const struct ct_root* root)
{

    /* TODO: fix breadth traveral */
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
