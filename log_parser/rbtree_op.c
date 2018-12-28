#if 0
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include "rbtree.h"
#include "parser.h"
#endif

#include "rbtree_op.h"


LineEntry_S*  SerachNode(struct rb_root* pstRoot, const char* pcKey)
{
    struct rb_node *pstNode = pstRoot->rb_node;
    LineEntry_S *pstEntryNode      = NULL;
    assert((NULL != pstRoot) || (NULL != pcKey));

    while (pstNode)
    {
        pstEntryNode = container_of(pstNode, LineEntry_S, stNode);
        if (strcmp(pstEntryNode->acKey, pcKey) > 0)
        {
            pstNode = pstNode->rb_left;
        }
        else if (strcmp(pstEntryNode->acKey, pcKey) < 0)
        {
            pstNode = pstNode->rb_right;
        }
        else
        {
            return pstEntryNode;
        }
    }
    
    return NULL;
    
}
#define REFRESHNODEBYNEW(po, pn, ep) \
    do { \
        if (pn->ep) \
        { \
          if (!po->ep) \
          { \
              po->ep = pn->ep; \
              pn->ep = NULL; \
          } \
          else \
          { \
          } \
        } \
    } while (0)

int RefreshNode(LineEntry_S* pstNew, LineEntry_S* pstOld)
{
    int             iRet            = 0;
    assert(NULL != pstNew || NULL != pstOld);

    memset(pstOld->acEndDate, 0, sizeof(pstOld->acEndDate));
    memset(pstOld->acEndTime, 0, sizeof(pstOld->acEndTime));
    strcpy(pstOld->acEndTime, pstNew->acEndTime);
    strcpy(pstOld->acEndDate, pstNew->acEndDate);

    assert(NULL != pstOld->pstLnCtt || NULL != pstNew->pstLnCtt);

    REFRESHNODEBYNEW(pstOld->pstLnCtt, pstNew->pstLnCtt, pcTranCode);

    REFRESHNODEBYNEW(pstOld->pstLnCtt, pstNew->pstLnCtt, pcRetCode);
    REFRESHNODEBYNEW(pstOld->pstLnCtt, pstNew->pstLnCtt, pcRetDesc);
    REFRESHNODEBYNEW(pstOld->pstLnCtt, pstNew->pstLnCtt, pcAppSrc); 
    REFRESHNODEBYNEW(pstOld->pstLnCtt, pstNew->pstLnCtt, pcAppDst); 
    REFRESHNODEBYNEW(pstOld->pstLnCtt, pstNew->pstLnCtt, pcNodeSrc);
    REFRESHNODEBYNEW(pstOld->pstLnCtt, pstNew->pstLnCtt, pcNodeDst);
    REFRESHNODEBYNEW(pstOld->pstLnCtt, pstNew->pstLnCtt, pcDstFile);
    REFRESHNODEBYNEW(pstOld->pstLnCtt, pstNew->pstLnCtt, pcSeqNo);  
    REFRESHNODEBYNEW(pstOld->pstLnCtt, pstNew->pstLnCtt, pcSrcIp);  
    REFRESHNODEBYNEW(pstOld->pstLnCtt, pstNew->pstLnCtt, pcDstIp);  
    REFRESHNODEBYNEW(pstOld->pstLnCtt, pstNew->pstLnCtt, pcDstPort);

    REFRESHNODEBYNEW(pstOld->pstLnCtt, pstNew->pstLnCtt, pcBasePath);

#if 0
    if ((strlen(pstNew->acEndDate) > 0) && (strlen(pstNew->acEndTime) > 0))
    {
        memset(pstOld->acEndDate, 0, sizeof(pstOld->acEndDate));
        memset(pstOld->acEndTime, 0, sizeof(pstOld->acEndTime));
        strcpy(pstOld->acEndDate, pstOld->acEndDate);
        strcpy(pstOld->acEndTime, pstOld->acEndTime);
    }
#endif

    REFRESHNODEBYNEW(pstOld->pstLnCtt, pstNew->pstLnCtt, pcDst);  
    REFRESHNODEBYNEW(pstOld->pstLnCtt, pstNew->pstLnCtt, pcSrc);
    return iRet;

}
#undef REFRESHNODEBYNEW

/**
 * @ desc   :  update tree, if  not exist , do insert. if exist , do update.
 * @ in     :
 *              pstRoot     -- root
 *              pstEntryNew -- changed entry
 * @ out    :  
 * @ cautious: 
 **/ 
int UpdateTree(struct rb_root* pstRoot, LineEntry_S* pstEntryNew)
{

    int             iRet            = 0;
    LineEntry_S*    pstLineEntry    = NULL;
    if (!pstEntryNew)
    {
        return 0;
    }

    /* do serach */
    pstLineEntry = SerachNode(pstRoot, pstEntryNew->acKey);

    /* insert if not exist */
    if (!pstEntryNew){
        iRet    = InsertNode(pstRoot, pstEntryNew);
        RETURN_IF_ERR(iRet);
    }
    else
    {
        iRet    = RefreshNode(pstEntryNew, pstLineEntry);
        RETURN_IF_ERR(iRet);
    }
    
    return iRet;
}

int InsertNode(struct rb_root* pstRoot, LineEntry_S* pstEntryNew)
{
    struct rb_node  ** ppstNode     = &(pstRoot->rb_node);
    struct rb_node  *  pstPNode     = NULL;
    LineEntry_S*    pstEntryNode    = NULL;
    
    /** get position **/
    while (*ppstNode)
    {
        pstEntryNode = container_of(*ppstNode, LineEntry_S, stNode);
	    pstPNode = *ppstNode;
        if (strcmp(pstEntryNode->acKey, pstEntryNew->acKey) > 0)
        {
            ppstNode = &((*ppstNode)->rb_left);
        }
        else if (strcmp(pstEntryNode->acKey, pstEntryNew->acKey) < 0)
        {
            ppstNode = &((*ppstNode)->rb_right);
        }
        else
        {
            return -1;
        }
    }
  
    rb_link_node(&pstEntryNew->stNode, pstPNode, ppstNode);
    rb_insert_color(&pstEntryNew->stNode, pstRoot);

    return 0; 
    
}


void DeleteNode(struct rb_root* pstRoot, const char* pcKey)
{
    LineEntry_S*            pstEntryNode = NULL;
    pstEntryNode   = SerachNode(pstRoot, pcKey);
    if (!pstEntryNode)
    {
        fprintf(stderr, "No data found.\n");
        return;
    }

    rb_erase(&pstEntryNode->stNode, pstRoot);
    free(pstEntryNode);

    return;
}


void PrtTreeAsce(struct rb_root* pstRoot)
{
    if (!pstRoot) return;
    struct rb_node* pstNode = pstRoot->rb_node;
    for (pstNode = rb_first(pstRoot); pstNode;  pstNode = rb_next(pstNode))
    {
        printf(" value is = [%s].\n", (container_of(pstNode, LineEntry_S, stNode))->acKey);
    }
    printf("------------------------\n");

    return;
}
void DumpTree2File(struct rb_root* pstRoot, char* pcPath)
{
    FILE*               fp              = NULL;      
    struct rb_node*     pstNode         = NULL;
    LineEntry_S*        pstEntry        = NULL;
    
    if (!pstRoot || !pcPath)
    {
        return;
    }
    fp = fopen(pcPath, "a+");
    if (!fp)
    {
        printf("open file [%s] failed.\n", pcPath);
    }
    for (pstNode = rb_first(pstRoot); pstNode;  pstNode = rb_next(pstNode))
    {
        pstEntry    = (container_of(pstNode, LineEntry_S, stNode));
        fprintf(fp, "%s\n", pstEntry->acKey);
    }

    fclose(fp);
    return;
}


int FuzzySerachNode(
    struct rb_root* pstRoot, 
    LineEntry_S*    pstEntry, 
    LineEntry_S**   ppstLineEntry
    )
{
    int             iRet                = 0;
    struct rb_node* pstNode             = NULL;
    LineEntry_S*    pstCurEntry         = NULL;

    
    if ( !pstEntry)
    {
        return -1;
    }

    pstNode = pstRoot->rb_node;
    *ppstLineEntry  = NULL;

    for (pstNode = rb_last(pstRoot); pstNode;  pstNode = rb_prev(pstNode))
    {
        pstCurEntry = container_of(pstNode, LineEntry_S, stNode);
        if (!strncmp(pstCurEntry->acKey + 18, pstEntry->acKey + 18, 8)) /* get it */
        {
            *ppstLineEntry  = pstCurEntry;
            break;
        }
    }

    return iRet;
}





#if 0
int main1()
{
    printf("hello c.\n");
    int aiArrSc[] = {5,4, 3, 2, 1, 9, 8, 7};
    LineEntry_S* pstEntryNew  = NULL;
    struct rb_root stScTree = RB_ROOT;
    int i = 0;
    for (; i < sizeof(aiArrSc)/sizeof(int); i++)
    {
        pstEntryNew = malloc(sizeof(LineEntry_S));
        pstEntryNew->acKey = aiArrSc[i];
        InsertScore(&stScTree, pstEntryNew);
    }
    PrtTreeAsce(&stScTree);

    DeleteScore(&stScTree, 5);
    PrtTreeAsce(&stScTree);
    DeleteScore(&stScTree, 2);
    PrtTreeAsce(&stScTree);

    return 0;
}

#endif

