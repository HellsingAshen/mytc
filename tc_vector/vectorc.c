#include <stdio.h>
#include <stdlib.h>
#include "vectorc.h"
#include "alias.h"
#include "pub.h"
#define     OK      (0)
#define     ERR     (-1)
/* @ desc:	Vct_Construct
 * @ input:	
 * 			pfnElementDestrucct : destruct method
 *			
 * @ output:
 * 			ppstVector: construct vector
 * @ cautious:
 */
UINT32    Vct_Construct(
        Vector_S**          ppstVector, 
        PFUNC_OBJ_DESTRUCT  pfnElementDestruct
        )
{
    int                     iRet                = OK;
    Vector_S*               pstVector           = NULL;

    do 
    {
        pstVector   = (Vector_S*)MALLOC(sizeof(Vector_S));           
        BREAK_IF_NULL(pstVector, iRet, ERR);

        pstVector->ppData       = MALLOC(sizeof(void*) * VECTOR_CAPACITY_DEFAULT);
        BREAK_IF_NULL((void*)&(pstVector->ppData[0]), iRet, ERR);

        pstVector->uiCount      = 0;
        pstVector->uiCapacity   = VECTOR_CAPACITY_DEFAULT;
        pstVector->pfnDestruct  = pfnElementDestruct;
    }
    while (0);

    if (iRet)
    {
        FREE(pstVector->ppData);
        FREE(pstVector);
    }
    *ppstVector = pstVector;
    return iRet;
}

/* @ desc: Vct_Destruct 
 * @ input : 
 * 				vector which to be destructed.
 * @ output :
 * @ cautious:
 */
void Vct_Destruct(Vector_S** ppstVector)
{
    /*
     * ����vector ,�������ÿ����Ա������������,�ͷ�,Ȼ���ͷ���������
     */
    unsigned int    uiIndex 	= 0;
    Vector_S		*pstVector	= NULL;
    if (!ppstVector || !(*ppstVector))
    {
        return;
    }

    pstVector	= *ppstVector;
    /* destruct vct element */
    if (pstVector->pfnDestruct)
    {
        for (; uiIndex < pstVector->uiCapacity; ++uiIndex)
        {
            if (pstVector->ppData[uiIndex])
            {
                pstVector->pfnDestruct(pstVector->ppData[uiIndex]);
                pstVector->ppData[uiIndex] = NULL;
                pstVector->uiCount--;
            }
        }

        if (pstVector->uiCount)
        {
            printf("warning: Vct_Destruct count .");
        }
    }

    pstVector->uiCapacity = 0;
    FREE(pstVector->ppData);
    FREE(pstVector);
    *ppstVector	= NULL;

    return;

}

/* @ desc   : Vct_Clear 
 * @ input  : 
 *              ppstVector
 * @ output :
 * @ cautious: 
 */
void Vct_Clear(Vector_S** ppstVector)
{
    /*
     * ��� vector ,���ͷ�������Ԫ��
     */

    unsigned int    uiIndex = 0;
    Vector_S		*pstVector	= NULL;
    if (!ppstVector || !(*ppstVector))
    {
        return;
    }

    pstVector	= *ppstVector;
    for (; uiIndex < pstVector->uiCapacity; ++uiIndex)
    {
        if (pstVector->ppData[uiIndex])
        {
            pstVector->ppData[uiIndex] = NULL;
        }
    }

    pstVector->uiCount = 0;

    return;
}

/* @ desc   : Vct_SetCapacity 
 * @ input  : 
 *              pstVector
 *              uiCapacity
 * @ output :
 * @ cautious: 
 */

UINT32 Vct_SetCapacity(Vector_S* pstVector, unsigned int uiCapacity)
{
    /* 
       1. ����uiCapaticy �ҵ�����Ҫ�����Ĵ�С
       2. ���·���ռ�
       3. ��ԭ����vector���ݿ������µĿռ�
       */
    UINT32  uiRet           = OK;
    void*   pData           = NULL;
    UINT32  uiReCapacity    = 0;

    /* �������ûĬ�ϵĴ󣬲���Ҫ���� */
    if (uiCapacity < VECTOR_CAPACITY_DEFAULT)
    {
        return OK;
    }
    
    uiReCapacity    = pstVector->uiCapacity;

    while (uiReCapacity < uiCapacity)
    {
        uiReCapacity = uiReCapacity<<1;
    }

    if (uiReCapacity > VECTOR_CAPACITY_MAX)
    {
        uiReCapacity  = VECTOR_CAPACITY_MAX;
    }
    else if (uiReCapacity < VECTOR_CAPACITY_DEFAULT)
    {
        uiReCapacity  = VECTOR_CAPACITY_RESIZE_MIN;
    }

    pData   = MALLOC(uiReCapacity * sizeof(void*));

    memcpy(pData, pstVector->ppData, sizeof(void*) * pstVector->uiCapacity);
    FREE(pstVector->ppData);
    pstVector->ppData = pData;
    pstVector->uiCapacity = uiReCapacity;
    pData	= NULL;

    return uiRet;
}

/* @ desc   : Vct_Pushback 
 * @ input  : 
 *              pstVector
 *              pObj        
 * @ output :   suc or failed
 * @ cautious: 
 */
UINT32 Vct_Pushback(Vector_S* pstVector,  void* pObj)
{
    UINT32              uiRet           = OK;
    UINT32              uiCurIndex      = pstVector->uiCount;

    do
    {
        /* resize */
        if (uiCurIndex == pstVector->uiCapacity)
        {
            uiRet   = Vct_SetCapacity(pstVector, pstVector->uiCapacity + 1);
            BREAK_IF_FAILED(uiRet);
        }

        uiRet   = Vct_SetIndex(pstVector, pstVector->uiCount, pObj);
        BREAK_IF_FAILED(uiRet);
        
        pstVector->uiCount++;
    }
    while (0);

    return uiRet;    
}


/* @ desc   : vector ���Ԫ�ص�vector ���׸���λ�� 
 * @ input  : 
 *              pstVector
 *              pObj        ����ӵĶ���ָ��
 * @ output :   suc or failed
 * @ cautious: 
 */

UINT32 Vct_Push(Vector_S* pstVector,  void* pObj)
{
    UINT32              uiRet       = OK;
    unsigned int        uiIndex = 0;

    if (!pObj || !pstVector) 
    {
        return ERR_CODE_INVALIDPARA;
    }

    for (; uiIndex < pstVector->uiCount; ++uiIndex)
    {
        if (!pstVector->ppData[uiIndex])
        {
            pstVector->ppData[uiIndex] = pObj;
            break;
        }
    }

    if (uiIndex == pstVector->uiCount)
    {
        uiRet = Vct_Pushback(pstVector, pObj);
    }

    return uiRet;
}

/* @ desc   : vector ��������
 * @ input  : 
 *             
 *             
 * @ output :  
 * @ cautious: 
 */

void* Vct_Popback(Vector_S* pstVector)
{
    /* �����ǵ������󣬲��Զ��������ֻ���� vector */

    void*               pObj            = NULL;
    if (!pstVector || (0 == pstVector->uiCount))
    {
        return NULL;
    }

    pObj    = pstVector->ppData[pstVector->uiCount - 1];
    while (!pObj && (pstVector->uiCount -1 >= 0))
    {
        pstVector->uiCount--;
        pObj    = pstVector->ppData[pstVector->uiCount - 1];

    }

    pstVector->ppData[pstVector->uiCount - 1] = NULL;
    pstVector->uiCount--;

    return pObj;

}
/* @ desc   : Vct_SetIndex
 * @ input  :  
 *              pstVector
 *              index
 *              pObj
 *             
 * @ output :   FAILED or SUC
 * @ cautious:  
 */
UINT32 Vct_SetIndex(Vector_S* pstVector, unsigned int uiIndex, void* pObj)
{
    /* 1.�ҵ�λ��
       2. �滻
     */
    UINT32              uiRet               = 0;
    if (!pstVector || !pObj)
    {
        return ERR_CODE_INVALIDPARA;
    }

    if (uiIndex > pstVector->uiCount - 1)
    {
        if (uiIndex > pstVector->uiCapacity - 1)
        {
            printf("Vct_SetIndex has create memory hole.\n");
            uiRet = Vct_SetCapacity(pstVector, uiIndex);
            RETURN_IF_FAILED(uiRet);
        }
        pstVector->uiCount = uiIndex + 1 - 1;
    }

    pstVector->ppData[uiIndex] = pObj;

    return OK;
}


