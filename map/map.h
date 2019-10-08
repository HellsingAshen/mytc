#include <stdlib.h>
#include <stdio.h>
#include "rbtree.h"
#include <string.h>

#include "macro.h"

typedef enum 
{
    INT     = 1,
    STRING  = 2,
    TYPE_BOUNDARY
} Type_E;

typedef union tagValue_U
{
    int    i;
    void*  pv;
}Value_U;

typedef struct tagValue_S
{
    Type_E          enType;
    Value_U         unVal;
    int             iMark;          /* tag isused */
}Value_S;
#define tvalues(v)      ((v)->enType)
#define ivalues(v)      ((v)->unVal.i)
#define pvalues(v)      ((v)->unVal.pv)
#define mvalues(v)      ((v)->iMark)

typedef struct tagObject_S
{
    int             iNext;          /* next available index */
    int             iCapacity;
    int             iCount;
    Value_S*        pstValues;
}Object_S;

#define vobject(o)      ((o)->pstValues)
#define nobject(o)      ((o)->iNext)
#define capobject(o)    ((o)->iCapacity)
#define cntobject(o)    ((o)->iCount)

typedef struct tagMap_S
{
    Type_E          enType;
    struct rb_root  stKeyRoot;
    
    Object_S        stObject;
} Map_S;
#define capmap(m)       (capobject(&((m)->stObject)))
#define tkeymap(m)      ((m)->enType)
#define objmap(m)       ((m)->stObject)

typedef struct tagKey_S
{
    struct  rb_node stNode;
    int     iIndex;
    Type_E  enType;
    union tagKeyVal
    {
        void*   p;
        char*   pc;
        int     i;
    } unKeyVal; 
}Key_S;

#define ndkey(k)        ((k)->stNode)
#define idxkey(k)       ((k)->iIndex)
#define tkey(k)         ((k)->enType)
#define pvkey(k)        ((k)->unKeyVal.p)
#define pcvkey(k)       ((k)->unKeyVal.pc)
#define ivkey(k)        ((k)->unKeyVal.i)


/* api declaration */
Map_S* MapInit(Type_E enKeyType);

int SearchMap(
    Map_S*          pstMap,
    Type_E          enKeyType,
    void*           pKey,
    int*            piType,
    void**          ppVal
    );

int Add2Map(
    Map_S*          pstMap,
    Type_E          enKeyType,
    void*           pKey,
    Type_E          enValueType,
    void*           pVal
    );
#define ADD2IMAP(m, kv, vt, vv)     Add2Map(m, INT, kv, vt, vv)

int DelFromMap(
    Map_S*           pstMap,
    Type_E          enKeyType,
    void*           pKey
    );

void DestructMap(
    Map_S* pstMap
    );
