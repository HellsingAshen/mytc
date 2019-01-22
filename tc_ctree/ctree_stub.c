#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "ctree.h"
#include "list.h"

typedef struct tagGroup_S
{
    struct ct_node  stNode;
    struct list_head stLink;
    int    iMemberNum;
}Group_S;


struct list_head* tc_get_list_node(int iVal, struct list_head* pstListHead)
{
    struct list_head* pstListPos    = NULL;
    int               iTravelFlag    = 1;
    Group_S*          pstGrp        = NULL;
    
    //list_for_each(pstListPos, pstListHead)
    for (pstListPos = pstListHead; iTravelFlag; (iTravelFlag = !(pstListPos->next == pstListHead)), pstListPos = pstListPos->next)
    {
        pstGrp = container_of(pstListPos, Group_S, stLink);
        if (pstGrp->iMemberNum == iVal)
        {
            break;
        }
        pstGrp = NULL;
    }
    
    return (pstGrp ? &(pstGrp->stLink) : NULL);


}

//Group_S* tc_assign_parent(struct ct_node* pstNode, struct list_head* pstListHead)
struct ct_node* tc_assign_parent(struct list_head* pstLink, struct list_head* pstListHead)
{
    Group_S*        pstGrp          = NULL;
    Group_S*        pstParent       = NULL;
    struct list_head* pstListNode   = NULL;

    pstGrp = container_of(pstLink, Group_S, stLink);
    switch (pstGrp->iMemberNum)
    {
        case 1:
        {
            pstParent = NULL;
            break;
        }

        case 2:
        case 3:
        {
            pstListNode= tc_get_list_node(1, pstListHead);
            pstParent = (pstListHead ? container_of(pstListNode, Group_S, stLink) : NULL);
            break;
        }

        case 4:
        case 5:
        case 6:
        {
            pstListNode= tc_get_list_node(2, pstListHead);
            pstParent = (pstListHead ? container_of(pstListNode, Group_S, stLink) : NULL);
            break;
        }

        case 7:
        case 8:
        case 9:
        case 10:
        {
            pstListNode= tc_get_list_node(3, pstListHead);
            pstParent = (pstListHead ? container_of(pstListNode, Group_S, stLink) : NULL);
            break;
        }

        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        {
            pstListNode= tc_get_list_node(5, pstListHead);
            pstParent = (pstListHead ? container_of(pstListNode, Group_S, stLink) : NULL);
            break;
        }

        case 16:
        {
            pstListNode= tc_get_list_node(8, pstListHead);
            pstParent = (pstListHead ? container_of(pstListNode, Group_S, stLink) : NULL);
            break;
        }
    
        default:
        {
            break;
        }
    }
    
    return (pstParent ? &(pstParent->stNode) : NULL);
}

void travel_node(struct ct_node* node)
{

    Group_S*                pstGrp          = NULL;

    pstGrp = (Group_S*)container_of(node, Group_S, stNode);
    printf("test case *** travel node  -- value = [%d] addr = [%p].\n", pstGrp->iMemberNum, &pstGrp->stNode);

    return;
}

struct ct_node* tc_cn_dfs(struct ct_node* node)
{
    struct ct_node*         child           = NULL;

    travel_node(node);

    for (child = node->child; child; child = child->next)
    {
        tc_cn_dfs(child);
    }
    
    return NULL;    
}


struct ct_node* tc_ct_dfs(const struct ct_root* root)
{
    (void)tc_cn_dfs(root->node); 
    return NULL;
}

struct ct_node* tc_ct_breadth_traveral(const struct ct_root* root)
{
    /* TODO: fix breadth traveral */

    struct ct_node*         last            = NULL;
    struct ct_node*         node            = NULL;
    Group_S*                pstGrp          = NULL;
    int                     is_last         = 1;

    assert(NULL != root);
    last = ct_br_get_last(root);

    for (node = root->node; is_last; node = ct_bt_next(node))
    {
        pstGrp = NULL;
        pstGrp = (Group_S*)container_of(node, Group_S, stNode); 
        printf("test case *** breadth traver  -- value = [%d] addr = [%p].\n", pstGrp->iMemberNum, (&pstGrp->stNode));
        if (ct_is_last_node(node))
        {
            printf("\n"); 
        }
        if (node == last)
        {
            is_last = 0;
        }
        
    }

    return NULL;
}

int tc_ct_insert()
{
    int             iRet            = 0;
    struct ct_node* pstParent       = NULL;
    Group_S*        pstGrp          = NULL;
    struct list_head *pstListHead   = NULL;
    struct list_head *pstListPos    = NULL;

    struct ct_node*  pstFirstChild  = NULL;
    struct ct_node*  pstTmpNode     = NULL;
    struct list_head* pstTmpLink    = NULL;
    struct ct_root  stRoot          = CT_ROOT;
    
    int             iTravelFlag     = 1;


    int             i               = 0;

    /* 1 | 2 3 | 4 5 6 | 7 8 9 10 || 11 12 13 14 15 16 */
    /* construct a tree like this :
     *
     * case 1:
     *          1
     *      2       3
     *    4 5 6   7 8 9
     *      11->15  
     *
     * case 2:
     *          1
     *      2       3
     *    4 5 6   7 8 9
     *      11->15  16
     */
#define CASE_2 1
    int             aiValue[]       = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
 #define CASE_1 0
    //int             aiValue[]       = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    //int             aiValue[]       = {1, 2, 3};

    for (; i < sizeof(aiValue)/sizeof(int); i++){
        pstGrp = malloc(sizeof(Group_S));
        pstGrp->iMemberNum  = aiValue[i];

        if (0 == i)
        {
            INIT_LIST_HEAD(&pstGrp->stLink);
            pstListHead = &pstGrp->stLink;
            stRoot.node = &pstGrp->stNode;
            ct_init_root(&pstGrp->stNode);
        }
        else 
        {
            list_add_tail(&pstGrp->stLink, pstListHead);
        }
    }

    /* list_for_each(pstListPos, pstListHead)  we cann't use list_for_each api because our list have no list_head . our list has no end flag.*/
    for(pstListPos = pstListHead; iTravelFlag ; pstListPos = pstListPos->next)
    {
        if (pstListPos->next == pstListHead)
        {
            iTravelFlag = 0;
        }
        pstGrp = container_of(pstListPos, Group_S, stLink);
        pstParent = tc_assign_parent(pstListPos, pstListHead);
printf("==== insert value[%d] addr = [%p].\n", pstGrp->iMemberNum, &pstGrp->stNode);
        ct_parent_insert_node(pstParent, &pstGrp->stNode);
    }

#if 0
    pstFirstChild = ct_first(&stRoot);
    printf("test case -- ct_first -- value = [%d].\n", ((Group_S*)container_of(pstFirstChild, Group_S, stNode))->iMemberNum);

    pstFirstChild = ct_last(&stRoot);
    printf("test case -- ct_last -- value = [%d].\n", ((Group_S*)container_of(pstFirstChild, Group_S, stNode))->iMemberNum);
#endif

    pstTmpLink= tc_get_list_node(7, pstListHead);
    pstFirstChild = ct_first_node(&((Group_S*)container_of(pstTmpLink, Group_S, stLink))->stNode);    
    printf("test case -- ct_first_node -- value 7 = [%d].\n", ((Group_S*)container_of(pstFirstChild, Group_S, stNode))->iMemberNum);
    assert(7 == ((Group_S*)container_of(pstFirstChild, Group_S, stNode))->iMemberNum);

    pstTmpLink= tc_get_list_node(8, pstListHead);
    pstFirstChild = ct_first_node(&((Group_S*)container_of(pstTmpLink, Group_S, stLink))->stNode);    
    printf("test case -- ct_first_node -- value 8 = [%d].\n", ((Group_S*)container_of(pstFirstChild, Group_S, stNode))->iMemberNum);
    assert(7 == ((Group_S*)container_of(pstFirstChild, Group_S, stNode))->iMemberNum);

    pstTmpLink= tc_get_list_node(10, pstListHead);
    pstFirstChild = ct_first_node(&((Group_S*)container_of(pstTmpLink, Group_S, stLink))->stNode);    
    printf("test case -- ct_first_node -- value 10 = [%d].\n", ((Group_S*)container_of(pstFirstChild, Group_S, stNode))->iMemberNum);
    assert(7 == ((Group_S*)container_of(pstFirstChild, Group_S, stNode))->iMemberNum);


    pstTmpLink= tc_get_list_node(10, pstListHead);
    pstFirstChild = ct_last_node(&((Group_S*)container_of(pstTmpLink, Group_S, stLink))->stNode);    
    printf("test case -- ct_last_node -- value = [%d].\n", ((Group_S*)container_of(pstFirstChild, Group_S, stNode))->iMemberNum);

    pstTmpLink= tc_get_list_node(8, pstListHead);
    pstFirstChild = ct_last_node(&((Group_S*)container_of(pstTmpLink, Group_S, stLink))->stNode);    
    printf("test case -- ct_last_node -- value = [%d].\n", ((Group_S*)container_of(pstFirstChild, Group_S, stNode))->iMemberNum);

    pstTmpLink= tc_get_list_node(7, pstListHead);
    pstFirstChild = ct_last_node(&((Group_S*)container_of(pstTmpLink, Group_S, stLink))->stNode);    
    printf("test case -- ct_last_node -- value = [%d].\n", ((Group_S*)container_of(pstFirstChild, Group_S, stNode))->iMemberNum);


    pstTmpLink= tc_get_list_node(7, pstListHead);
    iRet = ct_is_first_node(&((Group_S*)container_of(pstTmpLink, Group_S, stLink))->stNode);    
    printf("test case -- ct_is_first_node -- value = [%s].\n", (iRet != 0) ? "is" : "not");

    pstTmpLink= tc_get_list_node(10, pstListHead);
    iRet = ct_is_first_node(&((Group_S*)container_of(pstTmpLink, Group_S, stLink))->stNode);    
    printf("test case -- ct_is_first_node -- value = [%s].\n", (iRet != 0) ? "is" : "not");

    pstTmpLink= tc_get_list_node(10, pstListHead);
    iRet = ct_is_last_node(&((Group_S*)container_of(pstTmpLink, Group_S, stLink))->stNode);    
    printf("test case -- ct_is_last_node -- value = [%s].\n", (iRet != 0) ? "is" : "not");

    pstTmpLink= tc_get_list_node(8, pstListHead);
    iRet = ct_is_last_node(&((Group_S*)container_of(pstTmpLink, Group_S, stLink))->stNode);    
    printf("test case -- ct_is_last_node -- value = [%s].\n", (iRet != 0) ? "is" : "not");
        
    pstTmpLink= tc_get_list_node(7, pstListHead);
    iRet = ct_is_last_node(&((Group_S*)container_of(pstTmpLink, Group_S, stLink))->stNode);    
    printf("test case -- ct_is_last_node -- value = [%s].\n", (iRet != 0) ? "is" : "not");

    pstTmpLink= tc_get_list_node(4, pstListHead);
    iRet = ct_is_last_node(&((Group_S*)container_of(pstTmpLink, Group_S, stLink))->stNode);    
    printf("test case ** ct_is_last_node -- value 4 = [%s].\n", (iRet != 0) ? "is" : "not");

    pstTmpLink= tc_get_list_node(6, pstListHead);
    iRet = ct_is_last_node(&((Group_S*)container_of(pstTmpLink, Group_S, stLink))->stNode);    
    printf("test case ** ct_is_last_node -- value 6 = [%s].\n", (iRet != 0) ? "is" : "not");


    pstTmpLink= tc_get_list_node(3, pstListHead);
    iRet = ct_is_last_node(&((Group_S*)container_of(pstTmpLink, Group_S, stLink))->stNode);    
    printf("test case ** ct_is_last_node -- value 3 = [%s].\n", (iRet != 0) ? "is" : "not");

    pstTmpLink= tc_get_list_node(7, pstListHead);
    //printf("val = [%d]\n", ((Group_S*)container_of(pstTmpLink, Group_S, stLink))->iMemberNum);

    iRet = ct_is_sole_node(&((Group_S*)container_of(pstTmpLink, Group_S, stLink))->stNode);    
    printf("test case -- ct_is_sole_node -- value = [%s].\n", (iRet != 0) ? "is" : "not");

    iRet = ct_is_sole_node(stRoot.node);
    printf("test case -- ct_is_sole_node -- value = [%s].\n", (iRet != 0) ? "is" : "not");

    iRet = ct_get_deepth(&stRoot);
    printf("test case -- ct_get_deepth -- value = [%d].\n", iRet);

    iRet = ct_get_node_level(stRoot.node);
    printf("test case -- ct_get_node_level root node-- value = [%d].\n", iRet);

    pstTmpLink= tc_get_list_node(7, pstListHead);
    iRet = ct_get_node_level(&((Group_S*)container_of(pstTmpLink, Group_S, stLink))->stNode);    
    printf("test case -- ct_get_node_level 7-- value = [%d].\n", iRet);

    pstTmpLink= tc_get_list_node(7, pstListHead);
    iRet = ct_is_br_last(&stRoot, &((Group_S*)container_of(pstTmpLink, Group_S, stLink))->stNode);
    printf("test case -- ct_is_br_last -- value = [%d].\n", iRet);
    
    pstTmpLink= tc_get_list_node(10, pstListHead);
    iRet = ct_is_br_last(&stRoot, &((Group_S*)container_of(pstTmpLink, Group_S, stLink))->stNode);
    printf("test case -- ct_is_br_last -- value = [%d].\n", iRet);

    pstTmpLink= tc_get_list_node(6, pstListHead);
    iRet = ct_is_last_node(&((Group_S*)container_of(pstTmpLink, Group_S, stLink))->stNode);    
    printf("test case *** ct_is_last_node -- value 6 = [%s].\n", (iRet != 0) ? "is" : "not");

    pstTmpLink= tc_get_list_node(5, pstListHead);
    iRet = ct_is_last_node(&((Group_S*)container_of(pstTmpLink, Group_S, stLink))->stNode);    
    pstGrp = (Group_S*)container_of(pstTmpLink, Group_S, stLink); 
    printf("test case *** ct_is_last_node -- value 5 = [%s].\n", (iRet != 0) ? "is" : "not");

    pstTmpLink= tc_get_list_node(15, pstListHead);
    pstGrp = (Group_S*)container_of(pstTmpLink, Group_S, stLink); 
    iRet = ct_is_br_last(&stRoot, &((Group_S*)container_of(pstTmpLink, Group_S, stLink))->stNode);
    printf("test case *** ct_is_br_last_node -- value 15 = [%s].\n", (iRet != 0) ? "is" : "not");

    pstTmpLink= tc_get_list_node(16, pstListHead);
    pstGrp = (Group_S*)container_of(pstTmpLink, Group_S, stLink); 
    iRet = ct_is_br_last(&stRoot, &((Group_S*)container_of(pstTmpLink, Group_S, stLink))->stNode);
    printf("test case *** ct_is_br_last_node -- value 16 = [%s].\n", (iRet != 0) ? "is" : "not");

    pstTmpLink= tc_get_list_node(16, pstListHead);
    pstGrp = (Group_S*)container_of(pstTmpLink, Group_S, stLink); 
    iRet = ct_node_get_deepth(&pstGrp->stNode);
    printf("test case *** ct_node_get_deepth -- value 16 = [%d].\n", iRet);

    pstTmpLink= tc_get_list_node(8, pstListHead);
    pstGrp = (Group_S*)container_of(pstTmpLink, Group_S, stLink); 
    iRet = ct_node_get_deepth(&pstGrp->stNode);
    printf("test case *** ct_node_get_deepth -- value 8 = [%d].\n", iRet);

    pstTmpLink= tc_get_list_node(3, pstListHead);
    pstGrp = (Group_S*)container_of(pstTmpLink, Group_S, stLink); 
    iRet = ct_node_get_deepth(&pstGrp->stNode);
    printf("test case *** ct_node_get_deepth -- value 3 = [%d].\n", iRet);

    pstTmpLink= tc_get_list_node(7, pstListHead);
    pstGrp = (Group_S*)container_of(pstTmpLink, Group_S, stLink); 
    iRet = ct_node_get_deepth(&pstGrp->stNode);
    printf("test case *** ct_node_get_deepth -- value 7 = [%d].\n", iRet);

    pstTmpLink= tc_get_list_node(4, pstListHead);
    pstGrp = (Group_S*)container_of(pstTmpLink, Group_S, stLink); 
    iRet = ct_node_get_deepth(&pstGrp->stNode);
    //assert(2 == iRet);

    pstGrp = NULL;
    pstTmpNode = ct_br_get_last(&stRoot);
    pstGrp = (Group_S*)container_of(pstTmpNode, Group_S, stNode); 
    printf("test case *** ct_br_get_last -- value = [%d] addr = [%p].\n", pstGrp->iMemberNum, &pstGrp->stNode);

    pstGrp = NULL;
    pstTmpNode = ct_first_level_node(&stRoot, 0);
    pstGrp = (Group_S*)container_of(pstTmpNode, Group_S, stNode); 
    printf("test case *** ct_first_level_node 0 -- value = [%d] addr = [%p].\n", pstGrp->iMemberNum, &pstGrp->stNode);

    pstGrp = NULL;
    pstTmpNode = ct_first_level_node(&stRoot, 1);
    pstGrp = (Group_S*)container_of(pstTmpNode, Group_S, stNode); 
    printf("test case *** ct_first_level_node 1 -- value = [%d] addr = [%p].\n", pstGrp->iMemberNum, &pstGrp->stNode);

    pstGrp = NULL;
    pstTmpNode = ct_first_level_node(&stRoot, 2);
    pstGrp = (Group_S*)container_of(pstTmpNode, Group_S, stNode); 
    printf("test case *** ct_first_level_node 2 -- value = [%d] addr = [%p].\n", pstGrp->iMemberNum, &pstGrp->stNode);
    
    pstGrp = NULL;
    pstTmpNode = ct_first_level_node(&stRoot, 3);
    pstGrp = (Group_S*)container_of(pstTmpNode, Group_S, stNode); 
    printf("test case *** ct_first_level_node 3 -- value = [%d] addr = [%p].\n", pstGrp->iMemberNum, &pstGrp->stNode);

    printf("test case *** tc_ct_breadth_traveral start.\n");
    tc_ct_breadth_traveral(&stRoot);
    printf("test case *** tc_ct_breadth_traveral end.\n");

    printf("test case *** tc_ct_dfs start.\n");
    tc_ct_dfs(&stRoot);
    printf("test case *** tc_ct_ffs end.\n");


    struct ct_root stSubRoot;

    printf("test case ### tc_ct_breadth_traveral start.\n");
    pstTmpLink= tc_get_list_node(4, pstListHead);
    pstGrp = (Group_S*)container_of(pstTmpLink, Group_S, stLink); 
    stSubRoot.node = &pstGrp->stNode;
    (void)ct_erase_subtree(&stSubRoot);
    tc_ct_breadth_traveral(&stRoot);
    printf("test case ### ct_earse_subtree value = 4\n");
    printf("test case ### tc_ct_breadth_traveral end.\n");


    printf("test case ### tc_ct_breadth_traveral start.\n");
    pstTmpLink= tc_get_list_node(5, pstListHead);
    pstGrp = (Group_S*)container_of(pstTmpLink, Group_S, stLink); 
    stSubRoot.node = &pstGrp->stNode;
    (void)ct_erase_subtree(&stSubRoot);
    tc_ct_breadth_traveral(&stRoot);
    printf("test case ### ct_earse_subtree value = 5\n");
    printf("test case ### tc_ct_breadth_traveral end.\n");
    
    printf("test case ### tc_ct_breadth_traveral start.\n");
    pstTmpLink= tc_get_list_node(6, pstListHead);
    pstGrp = (Group_S*)container_of(pstTmpLink, Group_S, stLink); 
    stSubRoot.node = &pstGrp->stNode;
    (void)ct_erase_subtree(&stSubRoot);
    tc_ct_breadth_traveral(&stRoot);
    printf("test case ### ct_earse_subtree value = 6\n");
    printf("test case ### tc_ct_breadth_traveral end.\n");

    return iRet;
}

int main ()
{
    int             iRet            = 0;
    printf("hello c.\n");
    iRet = tc_ct_insert();
    
    return iRet;
}
