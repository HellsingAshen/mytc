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



pthread_mutex_t count_mutex;
long long count;
void increment_count()
{
    pthread_mutex_lock(&count_mutex);
    count = count + 1;
    pthread_mutex_unlock(&count_mutex);
    return;
}


long long get_count()
{
    long long c;
    pthread_mutex_lock(&count_mutex);
    c = count;
    pthread_mutex_unlock(&count_mutex);
    return (c);
}

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
    int             iRand       = 0;
    pthread_setspecific(tKey, (char*)acTh0);

    pRet = (char*)pthread_getspecific(tKey);
    /* 
    printf("hello son end. tid  = [%x] num = [%d] getSpecValue = [%s]\n", (unsigned int)pthread_self(), g_iNum, pRet);
    */
    
    /* test thread_mutex */
    int i = 0;
    while (i < 10)
    {
        increment_count();
        get_count();
        i++;
        iRand   = random() % 10;
        printf("Thread 0 do,sleep %d  count = [%d].\n", iRand, count);
        sleep (1);
    }   

    
    return (void*)0;

}

void* Th1_Prt()
{
    int             i       = 0;
    int             iRet    = 0;
    char            acTh1[1024] = { "shen"};
    char*           pRet    = NULL;
    int             iRand   = 0;
    /* init */
    iRet    = pthread_once(&tOnce, PthKeyCrt);

    iRet    = pthread_setspecific(tKey, (char*)acTh1);
    if (iRet)
    {
        printf("set err.\n");
        return NULL;
    }


    pRet = (char*)pthread_getspecific(tKey);
    /*
    printf("hello son end. tid  = [%x] num = [%d] getSpecValue = [%s]\n", (unsigned int)pthread_self(), g_iNum, pRet);
    */

    //printf("hello son1 end. tid  = [%x] num = [%d]\n", pthread_self(), g_iNum);
    while (i < 10)
    {
        increment_count();
        get_count();
        i++;
        iRand   = random() % 10;
        sleep (1);
        printf("Thread 1 do,sleep %d  count = [%d].\n", iRand, count);
    }   

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
    int*            pvRet            = 0;
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

    /*
       iRet = pth_crt(&tTid2, NULL, Th2_Prt, NULL);
       RETURN_IF_ERR(iRet);
       */

    iRet = pthread_join(tTid, &pvRet);
    RETURN_IF_ERR(iRet);


    return 0;
}
