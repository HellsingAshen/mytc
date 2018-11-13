#include "thread_pro.h"


int pth_crt(pthread_t* pTid, void* pThAttr,void* pFun, void *pArgAddr)
{
    int             iRet                = 0;
    iRet    = pthread_create(pTid, pThAttr, pFun, pArgAddr);
    LOGD("pth_crt .\n"); 
    return iRet;
}
