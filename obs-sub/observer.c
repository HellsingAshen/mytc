#include "observer.h"
#include "public.h"

void Notify()
{
    
    printf("in func Notify.\n");
    return;
}  

void NotifyImp()
{
    printf("in func NotifyImp.\n");
    return;
}   

void ObsDestruct(Observer_S* pstObs)
{
    if (!pstObs) return;
    FREE(pstObs);
    return;
}

Observer_S* ObsConstruct ()
{
    Observer_S* pstObs              = NULL;
    pstObs  = (Observer_S*)malloc(sizeof(Observer_S));
    RETURN_IF_NULL(pstObs, ERR_MALLOC_FAILED);

    pstObs->_NotifyImp = NotifyImp;
    pstObs->_Notify    = Notify;
    
    return pstObs;
}
