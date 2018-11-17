#include "dict.h"
#include "hash.h"

int InsertDict(DictTbl_S* pstDictTbl, const char* pcValue, int iLen)
{
    int             iRet                = 0;
    uint32_t        uiHashValue         = 0;
    DictRec_S*      pstRec              = NULL;
    DictRec_S*      pstNewRec           = NULL;

    RETURN_IF_NULL(pstDictTbl, ERR);
    /** 1. get pos in DictTbl  **/
    uiHashValue     = GetHash(pcValue, iLen) & pstDictTbl->iMask;
    pstRec          = &pstDictTbl->stDictRec[uiHashValue];
    
    /** 2. rec[pos] is empty, do add it  **/
    if (!pstRec->pcValue)
    {
        pstRec->pcValue = (char*)calloc(1, (iLen + 1) * sizeof(char));
        RETURN_IF_NULL(pstRec->pcValue, ERR);
        memcpy(pstRec->pcValue, pcValue, iLen);
        pstRec->iLen    = iLen;
        pstRec->uiRefCount++;
        pstRec->pstNextDictRec  = NULL;
        return OK;
    }

    /** 3. find pcValue is alreadly in DictRec, add ref count **/
    while (pstRec)
    {
        /** get it **/
        if (!memcmp(pcValue, pstRec->pcValue, iLen) 
                &&('\0' == pstRec->pcValue[iLen]))
        {
            pstRec->uiRefCount++;
            return OK;
        }
        
        /* get last rec which is not null */
        if (!pstRec->pstNextDictRec)
        {
            break;
        }

        pstRec = pstRec->pstNextDictRec;

    }  

    /** 4. find pcValue is not in DictRec,  add it **/
    pstNewRec   = (DictRec_S*)calloc(1, sizeof(DictRec_S));
    RETURN_IF_NULL(pstNewRec, ERR);
    pstNewRec->pcValue  = (char*)calloc(1, iLen + 1);
    if (!pstNewRec->pcValue)
    {
        FREE(pstNewRec);
        return ERR;
    }
    
    pstNewRec->iLen     = iLen;
    pstNewRec->uiRefCount++;
    pstNewRec->pstNextDictRec   = NULL;
   
    pstNewRec->pstNextDictRec   = pstRec->pstNextDictRec; 
    pstRec->pstNextDictRec      = pstNewRec;

    return iRet;

}

int RevmoveDict(DictTbl_S* pstDictTbl, const char* pcValue)
{
    int             iRet                = 0;
    unsigned int    uiHashValue         = 0;
    DictRec_S*      pstRec              = NULL;
    DictRec_S*      pstTmpRec           = NULL;
    DictRec_S*      pstMidRec           = NULL;
    int             iLen                = 0;

    iLen    = strlen(pcValue);

    RETURN_IF_NULL(pstDictTbl, ERR);
    uiHashValue     = GetHash(pcValue, iLen) & pstDictTbl->iMask;
    pstRec          = &pstDictTbl->stDictRec[uiHashValue];
    RETURN_IF_NULL(pstRec, OK);
    
    while (pstRec)
    {
        if (!memcmp(pcValue, pstRec->pcValue, strlen(pcValue)) 
            && ('\0' == pstRec->pcValue[strlen(pcValue)]))
        {
            pstRec->uiRefCount--;
            if (!pstRec->uiRefCount)
            {
                /* free this rec on the chain */
                /* head */
                if (!pstTmpRec)
                {
                    pstMidRec = pstRec->pstNextDictRec;
                    memset(pstRec, 0, sizeof(*pstRec));
                    if (!pstMidRec)
                    {
                        return OK;
                    }
                    memcpy(pstRec, pstMidRec, sizeof(struct tagDictRec_S));
                    pstRec->pstNextDictRec  = pstMidRec->pstNextDictRec;
                    FREE(pstMidRec);
                    return OK;
                }
                pstTmpRec->pstNextDictRec = pstRec->pstNextDictRec;
                FREE(pstRec);
            }

        }
        pstTmpRec = pstRec;
        pstRec  = pstRec->pstNextDictRec;
    }
    
    /* not fount return ok */ 
    return iRet;
}

int GetDict(DictTbl_S* pstDictTbl, uint32_t uiHash)
{
    return OK;
}

void DispDictRec(DictRec_S* pstDictRec)
{
	if (!pstDictRec) return;
	DictRec_S* pstRec	 = pstDictRec;
	while (pstRec)
	{
		printf(" pcValue = [%s], uiLen = [%d], uiRefCount = [%d]", pstRec->pcValue, pstRec->iLen, pstRec->uiRefCount);
		pstRec = pstRec->pstNextDictRec;
	}
	return;
}
void DispDictTbl(DictTbl_S* pstDictTbl)
{
	int				i				= 0;
	if (!pstDictTbl) return;
	printf("----------------Dict Used[%d]----------------\n", pstDictTbl->uiUsed);
	while (i < DICTREC_MAX_SIZE)
	{
		printf("----------------Dict HaskPos[%d]----------------\n", i);
		DispDictRec(&(pstDictTbl->stDictRec[i]));
		i++;
	}

	
	return;
}
