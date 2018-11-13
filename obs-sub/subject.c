#include "subject.h"
#include "public.h"

int         RegisterObserver(Observer_S* pstObs, struct tagSubobject_S* pstSub)
{
    int             iRet                = 0;
    int             i                   = 0;
    RETURN_IF_NULL(pstObs, ERR_INPARA_NULL);
    RETURN_IF_NULL(pstSub, ERR_INPARA_NULL);

    for (; i < OBS_MAX_SIZE; i++)
    {
        if (!pstSub->astObserver[i])
        {
            pstSub->astObserver[i] = pstObs; 
            return OK;
        }

    }    

    return ERR;


}

int         UnRegisterObserver(Observer_S* pstObs, struct tagSubobject_S* pstSub)
{
    int             iRet                = 0;
    int             i                   = 0;
    RETURN_IF_NULL(pstObs, ERR_INPARA_NULL);
    RETURN_IF_NULL(pstSub, ERR_INPARA_NULL);

    for (; i < OBS_MAX_SIZE; i++)
    {
        if (pstSub->astObserver[i])
        {
            if (pstSub->astObserver[i] == pstObs)
            {
                pstSub->astObserver[i] = NULL;
                return OK;
            }
        }
    }    

    return ERR;

}

int         NotifyObserver(struct tagSubobject_S* pstSub)
{
    int             iRet                = 0;
    int             i                   = 0;
    RETURN_IF_NULL(pstSub, ERR_INPARA_NULL);
    
    for (; i < OBS_MAX_SIZE; i++)
    {
        if (pstSub->astObserver[i])
        {
            pstSub->astObserver[i]->_Notify();
        }
    }

    return iRet;

}

void       SubDestruct(struct tagSubobject_S* pstSub)
{
    FREE(pstSub); 
    return;

}

Subobject_S*        SubCons()
{
    Subobject_S*             pstSub              = NULL;

    pstSub  = (Subobject_S*)malloc(sizeof(Subobject_S));
    RETURN_IF_NULL(pstSub, ERR_MALLOC_FAILED);
    
    pstSub->_RegisterObserver = RegisterObserver;
    pstSub->_UnRegisterObserver = UnRegisterObserver;
    pstSub->_NotifyObserver     = NotifyObserver;
    
    return pstSub;
}
