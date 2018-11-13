#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <semaphore.h>

#include <errno.h>

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

union semun {
    int val;
    struct semid_ds* buf;
    ushort* array;
};

int g_iNum = 0;

void* Th_Sem(int* piSem)
{
    int             iRet        = 0;
    //sleep (2);
    iRet = sem_wait(piSem);
    if (iRet)
    {
        printf("[A] P err.\n");
    }
    
    printf("[A] P get.\n");
    while (1);
    printf("[A] P get.\n");
    
    return (void*)0;

}

void* Th1_Sem(int* piSem)
{
    int             iRet        = 0;
    //sleep(4);
    iRet = sem_wait(piSem);
    if (iRet)
    {
        printf("[B] P err.\n");
    }
    printf("[B] P get.\n");
    return (void*)0;
}

void* Th2_Sem(int* piSem)
{
    int             iRet        = 0;
    printf("[C] sleep b.\n");
    sleep(4);
    printf("[C] sleep e.\n");
    iRet = sem_post(piSem);
    if (iRet)
    {
        printf("[V] C err.\n");
    }
    printf("[C] sleep ret =[%d].\n", iRet);
    return (void*)0;
}

/*
 *@des:
 *@caution: 
 */
int main(int argc, char** argv)
{
    int             iRet            = 0;
    LOGD("in main .");
    pthread_t       tTid            = 0;
    pthread_t       tTid1           = 0;
    pthread_t       tTid2           = 0;
    char*           pRet    = NULL;
    char            c = 'X';
    int             iSem            = 0;

    sem_t           tSem;

    iRet    = sem_init(&tSem, 0, 1);
    RETURN_IF_ERR(iRet);


    iRet = pth_crt(&tTid, NULL, Th_Sem, &tSem);
    RETURN_IF_ERR(iRet);

    iRet = pth_crt(&tTid1, NULL, Th1_Sem, &tSem);
    RETURN_IF_ERR(iRet);

    iRet = pth_crt(&tTid2, NULL, Th2_Sem, &tSem);
    RETURN_IF_ERR(iRet);



    /* detach tid */
    iRet = pthread_detach(tTid);
    RETURN_IF_ERR(iRet);
    iRet = pthread_detach(tTid1);
    RETURN_IF_ERR(iRet);
    iRet = pthread_detach(tTid2);
    RETURN_IF_ERR(iRet);


    iRet = sem_destroy(&tSem);
    RETURN_IF_ERR(iRet);

    sleep (10);
    printf(" at end  num = [%d]\n", g_iNum);
    

	return 0;
}
