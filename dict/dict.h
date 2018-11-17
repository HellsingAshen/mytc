#ifndef _DICT_H_
#define _DICT_H_
#include "public.h"
#include "pthread.h"
#include "stdint.h"

typedef struct tagDictRec_S
{
    char*               pcValue;
    int                 iLen;
    unsigned int        uiRefCount;
    struct tagDictRec_S* pstNextDictRec;

}DictRec_S;

typedef struct tagDictTbl_S
{
    DictRec_S           stDictRec[DICTREC_MAX_SIZE];
    int                 iMask;
    unsigned int        uiUsed;
    pthread_mutex_t     tLock;
}DictTbl_S;


int InsertDict(DictTbl_S* pstDictTbl, const char* pcValue, int iLen);

int RevmoveDict(DictTbl_S* pstDictTbl, const char* pcValue);

int GetDict(DictTbl_S* pstDictTbl, uint32_t uiHash);

#endif
