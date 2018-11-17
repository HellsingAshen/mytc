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
FILE*           fp              = NULL;

void* Th_Prt()
{
    int             i = 0;
    int             iRet = 0;
    char            acBuf[1024] = {"abc"};
    if ( write(fp,"abc", 3) < 0 )
    {
        printf("write error.\n");
    }
    //fprintf(fp, "%s", acBuf);
    //fflush(fp);

    printf("hello son end. tid  = [%x] num = [%d]\n", pthread_self(), g_iNum);
    //pthread_exit((void*)piRet);
    return (void*)0;

}

void* Th1_Prt()
{
    int             i = 0;
    int             iRet = 0;
    char            acBuf[1024] = {"def"};
    if ( write(fp,"abc", 3) < 0 )
    {
        printf("write error.\n");
    }
    //fflush(fp);
#if 0
    if ( fwrite(acBuf, 1, 4, fp ) < 0 )
    {
        printf("[B] fwrite error.\n");
    }
#endif

    printf("hello son end. tid  = [%x] num = [%d]\n", pthread_self(), g_iNum);
    //pthread_exit((void*)piRet);

    return (void*)0;
}

void* Th2_Prt()
{

    int             i = 0;
    int             iRet = 0;
    char            acBuf[1024] = {"ghl"};
    //fprintf(fp, "%s", acBuf);
    if ( write(fp,"abc", 3) < 0 )
    {
        printf("write error.\n");
    }
    //fflush(fp);
#if 0
    if ( fwrite(acBuf, 1, 4, fp ) < 0 )
    {
        printf("[C] fwrite error.\n");
    }
#endif

    printf("hello son end. tid  = [%x] num = [%d]\n", pthread_self(), g_iNum);
    //pthread_exit((void*)piRet);
    return (void*)0;
}

/*
 *@des:
 *@caution: 
 */
int main(int argc, char** argv)
{
    int             iRet            = 0;
    int             *pvRet          = NULL;
    LOGD("in main .");
    pthread_t       tTid            = 0;
    pthread_t       tTid1           = 0;
    pthread_t       tTid2           = 0;
    char            acBuf1[1024]    = {"main"};


    if (NULL !=  (fp = (fopen("./123", "w"))))
    {
        printf("fopen suc.\n");
    }
    if ( fwrite(acBuf1, 1, 4, fp ) < 0 )
    {
        printf("[C] fwrite error.\n");
    }
    fflush(fp);

#if 0
    /* pthread_mutex */
    iRet    = pthread_mutex_init(&g_tMutex, NULL);
    RETURN_IF_ERR(iRet);
    /* pthread_cond_t */
    iRet    = pthread_cond_init(&g_tCond, NULL);
    RETURN_IF_ERR(iRet);

    /* pthread rwlock */
    iRet    = pthread_rwlock_init(&g_rLock, NULL);
    RETURN_IF_ERR(iRet);
    iRet    = pthread_rwlock_init(&g_wLock, NULL);
    RETURN_IF_ERR(iRet);
#endif

    iRet = pth_crt(&tTid, NULL, Th_Prt, NULL);
    RETURN_IF_ERR(iRet);

    iRet = pth_crt(&tTid1, NULL, Th1_Prt, NULL);
    RETURN_IF_ERR(iRet);

#if 1
    iRet = pth_crt(&tTid2, NULL, Th2_Prt, NULL);
    RETURN_IF_ERR(iRet);
#endif

    /* detach tid */
    iRet = pthread_detach(tTid);
    RETURN_IF_ERR(iRet);
    iRet = pthread_detach(tTid1);
    RETURN_IF_ERR(iRet);
    iRet = pthread_detach(tTid2);
    RETURN_IF_ERR(iRet);

    //free((long)pvRet);
    sleep (10);
    printf(" at end  num = [%d]\n", g_iNum);
    
#if 0
    iRet    = pthread_cond_destroy(&g_tCond);
    RETURN_IF_ERR(iRet);

    iRet    = pthread_mutex_destroy(&g_tMutex);
    RETURN_IF_ERR(iRet);

    iRet    = pthread_rwlock_destroy(&g_rLock);
    RETURN_IF_ERR(iRet);

    iRet    = pthread_rwlock_destroy(&g_wLock);
    RETURN_IF_ERR(iRet);
#endif
    fclose(fp);

	return 0;
}
