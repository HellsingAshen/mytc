#include "map.h"
#include <assert.h>

#if  DESC("op_tree")
void DestructNode(
    struct rb_node* pstRoot
    )
{
    Key_S*          pstKey          = NULL;

    if (!pstRoot) return;
    if (pstRoot->rb_left)
    {
        DestructNode(pstRoot->rb_left);
        pstRoot->rb_left = NULL;
    }

    if (pstRoot->rb_right)
    {
        DestructNode(pstRoot->rb_right);
        pstRoot->rb_right = NULL;
    }

    pstKey = container_of(pstRoot, Key_S, stNode);
    if (STRING == pstKey->enType)
    {
        FREE(pcvkey(pstKey));
    }
    FREE(pstKey);
    return;
}

/* 
 * desc : destructed key-root
 * in   :  
 *          pstKeyRoot ---- destructed root
 * out  :
 * cautious :
 */
void DestructKey(
    struct rb_root* pstKeyRoot
    )
{
    if (pstKeyRoot && pstKeyRoot->rb_node)
    {
        DestructNode(pstKeyRoot->rb_node);
    }
    return;
}

/* 
 * desc : find key node in rb_tree 
 * in   : 
 *          iType -- key type, only support INT and STRING 
 *          pkv   -- keyval
 * out  : 
 *         return 1 and  ppout point to found-Key_S if found 
 *         return 0 and  ppout point to last serached Key_S if not found 
 */
int  SerachKey(
    struct rb_root* pstRoot, 
    int     iType, 
    void*   pkv, 
    void**  ppOut
    )
{
    struct rb_node *pstNode = pstRoot->rb_node;
    Key_S *pstKey           = NULL;
    Key_S *pstPNode         = NULL;
    
    assert(iType == INT || iType == STRING);

    while (pstNode)
    {
        pstKey = container_of(pstNode, Key_S, stNode);
        pstPNode = pstKey;

        if (CMPVALBYTYPE(iType, pstKey, pkv) > 0)
        {
            pstNode = pstNode->rb_left;
        }
        else if (CMPVALBYTYPE(iType, pstKey, pkv) < 0)
        {
            pstNode = pstNode->rb_right;
        }
        else
        {
            *ppOut = pstKey;
            return 1;
        }
    }
    /* not found, return last traveled */
    *ppOut = pstPNode;
    return 0; 
}

/* 
 * desc : insert a node into key_tree
 * in   : 
 *          pstRoot ---- key_tree
 *          iType ---- key type[INT, STRING]
 *          pkv   ---- key value
 * out  : 
 *        0  ---- suc 
 *        -1 ---- failed
 *        ppstNew -- point to new insert position 
 * cautious : 
 */
int InsertKey(
    struct rb_root* pstRoot, 
    int     iType, 
    void*   pkv, 
    Key_S** ppstNew
    )
{
    int             iRet                = 0;
    struct rb_node**    ppstNode        = NULL;
    Key_S*          pstNew              = NULL;
    Key_S*          pstKey              = NULL;

    assert(iType == INT || iType == STRING);

    iRet = SerachKey(pstRoot, iType, pkv, (void*)&pstKey);
    if (iRet)
    {
        LOGE("key has been exist. please check it.\n");
        *ppstNew = pstKey;
        return F_OK;
    }
    else
    {
        *ppstNew = pstNew = malloc(sizeof(*pstNew));
        memset(pstNew, 0, sizeof(*pstNew));
        if (INT == (tkey(pstNew) = iType))
        {
            ivkey(pstNew) = (unsigned long long)pkv;
        }
        else
        {
            /* string */
            pcvkey(pstNew)  = malloc(strlen(pkv) + 1);
            memset(pcvkey(pstNew), 0, strlen(pkv) + 1);
            memcpy(pcvkey(pstNew), pkv, strlen(pkv));
        }
        ppstNode = ((NULL == pstKey) 
                        ? &pstRoot->rb_node 
                        : ((CMPVALBYTYPE(iType, pstKey, pkv) > 0) 
                            ? &(ndkey(pstKey).rb_left) 
                            : &(ndkey(pstKey).rb_right))); /* position */
        rb_link_node(&ndkey(pstNew), &ndkey(pstKey), ppstNode);
        rb_insert_color(&ndkey(pstNew), pstRoot);
    }
    return OK;
}

/*
 * desc : delete keynode in key_tree
 * in   :
 *          pstRoot ---- key_tree
 *          pstKey  ---- to be deleted keynode    
 * out  :
 * cautious   :
 */
void DeleteKeyNode(
    struct rb_root* pstRoot, 
    Key_S*          pstKey
    )
{
    rb_erase(&ndkey(pstKey), pstRoot);
    if (STRING == tkey(pstKey))
    {
        FREE(pcvkey(pstKey));
    }
    FREE(pstKey);
    return;
}
#endif

#if DESC("op_array")
/* 
 * desc : destructed object array
 * in   :  
 *          pstObj ---- destructed array
 * out  :
 * cautious :
 */
void DestructObj(
    Object_S*   pstObj
    )
{

    int             i               = 0;
    Value_S*        pstVal          = NULL;
    for (pstVal = vobject(pstObj); i < capobject(pstObj); i++)
    {
        if (mvalues(pstVal + i) && STRING == tvalues(pstVal + i))
        {
            FREE(pvalues(pstVal + i));
        }

        mvalues(pstVal + i) = 0;
        tvalues(pstVal + i) = 0;
        memset(&vobject(pstObj)->unVal, 0, sizeof(vobject(pstObj)->unVal));
    }
    FREE(pstVal);
    vobject(pstObj) = NULL;
    nobject(pstObj) = capobject(pstObj) = cntobject(pstObj) = 0;
    return;
}

/*
 * @ desc   : adjust object array and set next available index after delete and insert operations
 * @ in     :
 *              pstObj ---- object array
 * @ out    : 
 * @ cautious : current implementation of dynamic expansion
 *            TODO: dynamic reduction while cntobject(o) <= 1/3 capobject(o) , capobject(o0 = 1/2 capobject(o)
 */ 
int AdjustObj(Object_S* pstObj)
{
    int             iOldCapacity    = capobject(pstObj);
    int             i               = 0; 
    
    assert(capobject(pstObj) != MAP_MAX_SIZE);

    if (capobject(pstObj) == ++cntobject(pstObj))
    {
        capobject(pstObj)   = MIN(capobject(pstObj) * 2, MAP_MAX_SIZE);
        vobject(pstObj) = realloc(vobject(pstObj), capobject(pstObj) * sizeof(Value_S));
        memset(vobject(pstObj) + iOldCapacity, 0, (capobject(pstObj) - iOldCapacity) * sizeof(Value_S));
    }

    /* backward search */
    for (i = nobject(pstObj); i < capobject(pstObj) && (vobject(pstObj) + i)->iMark; i++);
    if (i == capobject(pstObj))
    {
        /* forward serach */
        for (i = nobject(pstObj); i >= 0 && (vobject(pstObj) + i)->iMark; i--);
        if (i < 0)
        {
            LOGE("can not find space to add obj. please check it .\n");
            nobject(pstObj) = -1;
            return F_OK;
        }
    }
    nobject(pstObj) = i;
    return OK;
}

/*   
 * @ desc   : remove object in pstObj whose index is equal to iIndex
 * @ in     :
 *              pstObj ---- array object
 *              iIndex ---- removed index
 * @ out    : 
 * @ cautious : 
 */
void DeleteObj(
    Object_S*       pstObj,
    int             iIndex
    )
{
    if (vobject(pstObj) + iIndex)
    {
        if (STRING == tvalues(vobject(pstObj) + iIndex))
        {
            FREE(pvalues(vobject(pstObj) + iIndex));
        }
        memset(vobject(pstObj) + iIndex, 0, sizeof(Value_S));
        mvalues(vobject(pstObj) + iIndex) = 0;
        cntobject(pstObj)--;
        /* TODO: dynamic resize */
    }
    return;
}

/* 
 * desc : add an object into object and carry out inserted position 
 * in   :
 *          pstObj ---- object array
 *          enType ---- inserted object-type
 *          pVal   ---- inserted object-val
 * out  :
 *          piIndex ---- inserted position 
 *          return value ----  success ok, others failure
 */
int ObjAddEle(
    Object_S*       pstObj,
    Type_E          enType,
    void*           pVal, 
    int*            piIndex
)
{
    void*               p               = NULL;

    if ((vobject(pstObj) + nobject(pstObj))->iMark)
    {
        LOGE("can get next available index, please chech it.\n");
        //AdjustObj(pstObj);
        return F_OK;
    }

    if (INT == (tvalues(vobject(pstObj) + nobject(pstObj))=enType))
    {
        ivalues(vobject(pstObj) + nobject(pstObj)) = (unsigned long long)pVal;
    }
    else
    {
        p = pvalues(vobject(pstObj) + nobject(pstObj)) = malloc(strlen((char*)pVal) + 1);
        memset(p, 0, strlen(pVal)+1);
        memcpy(p, pVal, strlen(pVal));
    }

    mvalues(vobject(pstObj) + nobject(pstObj)) = 1;
    *piIndex = nobject(pstObj);
    AdjustObj(pstObj);

    return OK;
}
#endif

#if DESC("op_map")
/* 
 * desc : init a map
 * in   : 
 *          enType  ---- type of created map
 * out  :
 *          return value ---- created map
 * cautious :
 */
Map_S* MapInit(Type_E enType)
{
    Map_S*              pstMap              = malloc(sizeof(*pstMap));
    memset(pstMap, 0, sizeof(*pstMap));
    pstMap->stKeyRoot = RB_ROOT;
    tkeymap(pstMap) = enType;

    capmap(pstMap)  = MAP_DEFAULT_SIZE;
    nobject(&(objmap(pstMap))) = 0;
    cntobject(&(objmap(pstMap))) = 0;
    vobject(&(objmap(pstMap))) = malloc(capmap(pstMap) * sizeof(Value_S));
    
    return pstMap;
}

/*
 * desc : search map by key-type and key value
 * in   :
 *          enKeyType ---- key-type
 *          pKey      ---- key-val
 * out  :
 *          piType    ---- value-type
 *          ppVal     ---- value-val
 * cautious :
 */
int SearchMap(
    Map_S*          pstMap,
    Type_E          enKeyType,
    void*           pKey,
    int*            piType,
    void**          ppVal
    )
{
    int             iRet                = 0;
    Key_S*          pstKey              = NULL;
    assert( pstMap != NULL);

    iRet = SerachKey(&pstMap->stKeyRoot, enKeyType, pKey, (void*)&pstKey);
    if (0 == iRet) /* not found */
    {
        LOGE("No target node found.\n");
        return F_OK;
    }
    *piType = tvalues(vobject(&(pstMap->stObject)) + idxkey(pstKey));
    *ppVal = (vobject(&(pstMap->stObject)) + idxkey(pstKey))->unVal.pv;
    return OK;
}

/*
 * desc : add KEY[key_type, key_val]-VALUE[val_type, val_val] into map
 * in   :
 *          enKeyType ---- key_type
 *          pKey      ---- key_val
 *          enValueType ---- val_type
 *          pVal        ---- val_val
 * cautious:
 */
int Add2Map(
    Map_S*          pstMap, 
    Type_E          enKeyType,
    void*           pKey,
    Type_E          enValueType,
    void*           pVal
    )
{
    int             iRet                = 0;
    int             iIndex              = 0;
    Key_S*          pstNew              = NULL;

    assert(pstMap->enType == enKeyType);
    
    iRet = InsertKey(&pstMap->stKeyRoot, enKeyType, pKey, &pstNew);
    if (F_OK == iRet)
    {
        LOGE("duplicate key.\n");
        return iRet;
    }

    iRet = ObjAddEle(&pstMap->stObject, enValueType, pVal, &iIndex);
    if (F_OK == iRet)
    {
        LOGE("ObjAddEle error.\n");
        return iRet;
    }
    idxkey(pstNew) = iIndex;
    return iRet;
}

/*
 * desc :delete map_elem whose key is [enValueType, pKey]
 * in   :
 *          enKeyType ---- key_type
 *          pKey      ---- key_val
 * cautious :
 */
int DelFromMap(
    Map_S*           pstMap,
    Type_E          enKeyType,
    void*           pKey
    )
{
    int             iRet                = 0;
    Key_S*          pstKey              = NULL;
    assert(pstMap != NULL);

    iRet = SerachKey(&pstMap->stKeyRoot, enKeyType, pKey, (void*)&pstKey);
    if (0 == iRet) /* not found */
    {
        LOGE("not found del node. please conform it .\n");
        return F_OK;
    }
    
    DeleteObj(&pstMap->stObject, idxkey(pstKey));
    DeleteKeyNode(&pstMap->stKeyRoot, pstKey);

    return OK;
}

/* 
 * desc : destructed map
 * in   :  
 *          pstMap ---- destructed map
 *          enKeyType ---- destructed map type
 * out  :
 * cautious :
 */
void DestructMap(
    Map_S*      pstMap
    )
{
    DestructObj(&pstMap->stObject);
    DestructKey(&pstMap->stKeyRoot);
    FREE(pstMap);
}
#endif
