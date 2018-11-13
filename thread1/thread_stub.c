#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/shm.h>
*/
#include "thread_pro.h"
#include "logf.h"

#define ERR        (-1)
#define OK        (0)
#define ST_TYPE_FTP_APP_CONFIG    	(1)
#define ST_TYPE_FTP_APP_NODE_CFG    (2)
#define MAX_NODE_CONFIG             (500)
#define MAX_SHMSIZE_APPCFG 			(102400)

#define CHAR_ARR_LEN_MAX 1024
#define BREAK_IF_ERR(ret) \
	if (0 != ret) {printf("Get errorcode = [%d] line = [%d].\n", ret, __LINE__); break;}
#define RETURN_IF_ERR(ret) \
	if (0 != ret) {printf("Get errorcode = [%d] line = [%d].\n", ret, __LINE__); return ret;}

int g_iNum = 0;
pthread_mutex_t g_tMutex ;      
pthread_rwlock_t g_rLock ;      
pthread_rwlock_t g_wLock ;      

pthread_cond_t g_tCond ;

pthread_key_t   tKey;
pthread_once_t  tOnce = PTHREAD_ONCE_INIT; /* related to which is reliased once */

void KeyDestruct(void* p)
{
    return (void*)0;
}
void PthKeyCrt()
{
    int             iRet = 0;
    iRet    = pthread_key_create(&tKey, KeyDestruct);
    if (iRet) return;
    
    return;
    
    

}
void* Th_Prt()
{
    int             iRet        = 0;
    char            acTh0[1024] = { "family"};
    char*           pRet        = NULL;
    /* init */
    iRet    = pthread_once(&tOnce, PthKeyCrt);
    
    pthread_setspecific(tKey, (char*)acTh0);

    pRet = (char*)pthread_getspecific(tKey);
    printf("hello son end. tid  = [%x] num = [%d] getSpecValue = [%s]\n", (unsigned int)pthread_self(), g_iNum, pRet);
    return (void*)0;

}

void* Th1_Prt()
{
    int             i       = 0;
    int             iRet    = 0;
    char            acTh1[1024] = { "shen"};
    char*           pRet    = NULL;
    /* init */
    iRet    = pthread_once(&tOnce, PthKeyCrt);
    
    iRet    = pthread_setspecific(tKey, (char*)acTh1);
    if (iRet)
    {
        printf("set err.\n");
        return NULL;
    }
    

    pRet = (char*)pthread_getspecific(tKey);
    printf("hello son end. tid  = [%x] num = [%d] getSpecValue = [%s]\n", (unsigned int)pthread_self(), g_iNum, pRet);

//printf("hello son1 end. tid  = [%x] num = [%d]\n", pthread_self(), g_iNum);

    return (void*)0;
}

void* Th2_Prt()
{
    int             i = 0;
    int             iRet = 0;

    /* init */
    iRet    = pthread_once(&tOnce, PthKeyCrt);
    return (void*)0;
}

/*
 *@des:
 *@caution: 
 */
int main(int argc, char** argv)
{
    int             iRet            = 0;
    //int             *pvRet          = NULL;
    LOGD("in main .");
    pthread_t       tTid            = 0;
    pthread_t       tTid1           = 0;
    pthread_t       tTid2           = 0;
    char*           pRet    = NULL;

    char            acTh[1024] = { "main"};
    

    iRet = pth_crt(&tTid, NULL, Th_Prt, NULL);
    RETURN_IF_ERR(iRet);

    iRet = pth_crt(&tTid1, NULL, Th1_Prt, NULL);
    RETURN_IF_ERR(iRet);

    iRet = pth_crt(&tTid2, NULL, Th2_Prt, NULL);
    RETURN_IF_ERR(iRet);



    iRet    = pthread_setspecific(tKey, (char*)acTh);
    pRet = (char*)pthread_getspecific(tKey);

    printf("hello main end. getSpecValue = [%s]\n",  pRet);

    /* detach tid */
    iRet = pthread_detach(tTid);
    RETURN_IF_ERR(iRet);
    iRet = pthread_detach(tTid1);
    RETURN_IF_ERR(iRet);
    iRet = pthread_detach(tTid2);
    RETURN_IF_ERR(iRet);

    //pthread_join(tTid, &pvRet);
    sleep (10);
    printf(" at end  num = [%d]\n", g_iNum);
    

	return 0;
}
