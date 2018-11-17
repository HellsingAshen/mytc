#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

int g_iNum = 0;


void* Th_Sub(int* piSem)
{
    int             iRet        = 0;

    return (void*)0;

}

void* Th_Pub(int* piSem)
{
    int             iRet        = 0;
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

    int             iSem            = 0;
    if (argc > 1)
    {
    }

    iRet = pth_crt(&tTid, NULL, Th_Pub, &iSem);
    RETURN_IF_ERR(iRet);

    iRet = pth_crt(&tTid1, NULL, Th_Sub, &iSem);
    RETURN_IF_ERR(iRet);

    /* detach tid */
    iRet = pthread_detach(tTid);
    RETURN_IF_ERR(iRet);
    iRet = pthread_detach(tTid1);
    RETURN_IF_ERR(iRet);

    sleep (10);
    printf(" at end  num = [%d]\n", g_iNum);
    

	return 0;
}
