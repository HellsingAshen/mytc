#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include "rbtree.h"

typedef struct tagScore_S
{
    struct  rb_node stNode;
    int     iScore;     
}Score_S;

Score_S*  SerachScore(struct rb_root* pstRoot, int iScore)
{
    struct rb_node *pstNode = pstRoot->rb_node;
    Score_S *pstScNode      = NULL;

    while (pstNode)
    {
        pstScNode = container_of(pstNode, Score_S, stNode);
        if (pstScNode->iScore > iScore)
        {
            pstNode = pstNode->rb_left;
        }
        else if (pstScNode->iScore < iScore)
        {
            pstNode = pstNode->rb_right;
        }
        else
        {
            return pstScNode;
        }
    }
    
    return NULL;
    
}

int InsertScore(struct rb_root* pstRoot, Score_S* pstScNew)
{
    struct rb_node  ** ppstNode = &(pstRoot->rb_node);
    struct rb_node  *  pstPNode = NULL;
    Score_S*           pstScNode = NULL;
    
    /** get position **/
    while (*ppstNode)
    {
        pstScNode = container_of(*ppstNode, Score_S, stNode);
	    pstPNode = *ppstNode;
        if (pstScNode->iScore > pstScNew->iScore)
        {
            ppstNode = &((*ppstNode)->rb_left);
        }
        else if (pstScNode->iScore < pstScNew->iScore)
        {
            ppstNode = &((*ppstNode)->rb_right);
        }
        else
        {
            return -1;
        }
    }
  
    rb_link_node(&pstScNew->stNode, pstPNode, ppstNode);
    rb_insert_color(&pstScNew->stNode, pstRoot);

    return 0; 
    
}


void DeleteScore(struct rb_root* pstRoot, int iScore)
{
    Score_S*            pstScNode = NULL;
    pstScNode   = SerachScore(pstRoot, iScore);
    if (!pstScNode)
    {
        fprintf(stderr, "No data found.\n");
        return;
    }

    rb_erase(&pstScNode->stNode, pstRoot);
    free(pstScNode);

    return;
}


void PrtTreeAsce(struct rb_root* pstRoot)
{
    if (!pstRoot) return;
    struct rb_node* pstNode = pstRoot->rb_node;
    for (pstNode = rb_first(pstRoot); pstNode;  pstNode = rb_next(pstNode))
    {
        printf(" value is = [%d].\n", (container_of(pstNode, Score_S, stNode))->iScore);
    }
    printf("------------------------\n");

    return;
}
int main()
{
    printf("hello c.\n");
    int aiArrSc[] = {5,4, 3, 2, 1, 9, 8, 7};
    Score_S* pstScNew  = NULL;
    struct rb_root stScTree = RB_ROOT;
    int i = 0;
    for (; i < sizeof(aiArrSc)/sizeof(int); i++)
    {
        pstScNew = malloc(sizeof(Score_S));
        pstScNew ->iScore = aiArrSc[i];
        InsertScore(&stScTree, pstScNew);
    }
    PrtTreeAsce(&stScTree);

    DeleteScore(&stScTree, 5);
    PrtTreeAsce(&stScTree);
    DeleteScore(&stScTree, 2);
    PrtTreeAsce(&stScTree);

    return 0;
}


