#ifndef _SLIST_H
#define _SLIST_H

#include <stdlib.h>
#include <stdio.h>
#include "list.h"

typedef struct tagSlist_S
{
    int                 iAge;
    char                acName[128];
    struct list_head    stNode;
}Slist_S;

int main()
{
    int i    = 0;
    Slist_S* pstNewPeople = NULL;
    Slist_S stPeople;
    Slist_S* pstTmp;
    
    struct list_head*   pstNode = NULL;
    struct list_head*   pstPos  = NULL;
    Slist_S* pstEntry   = NULL;
    

    printf("hello list .\n");
    INIT_LIST_HEAD(&stPeople.stNode);

    for (i = 0; i < 10; i++)
    {
        pstNewPeople = (Slist_S*)malloc(sizeof(Slist_S)); 
        pstNewPeople->iAge = i;
        list_add_tail(&pstNewPeople->stNode, &stPeople.stNode);
    }

    /** scan list  use entry **/
    list_for_each_entry(pstTmp, &stPeople.stNode, stNode)
    {
       printf("iAge is = [%d].\n", pstTmp->iAge); 
    }


    /** for test list_for_each **/
    list_for_each(pstPos, &stPeople.stNode)
    {
        pstEntry = list_entry(pstPos, typeof(*(pstEntry)), stNode); 
        
        printf("entry iAge is = [%d].\n", pstEntry->iAge); 

    }

    return 0;

}














#endif
