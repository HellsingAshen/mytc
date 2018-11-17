#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "showshmtype.h"
#define CHAR_ARR_LEN_MAX 1024
#define TC_BIE(ret) \
    if (0 != ret) { break;}

int GetShMemId();
/*
 *@des：再学习共享内存
 *@caution: 
 */
int main(int argc, char* argv)
{
    printf("hello world.\n");
    char* pcTest;
    char* pcSon;
    int iShId = GetShMemId();
    CFG* pstCfg = NULL;
    int i = 0;

    if (iShId <= 0) {
        printf("Get share memory id failed.\n");
        exit(0);
    }
    printf("in stub,get shmId = [%d].\n", iShId);
    pcTest = shmat(iShId, 0, 0);
    pstCfg = pcTest;
    while (i < 10)
    {
        printf("%s|%s|%s|%s|%s|\n", pstCfg->APP_DN, pstCfg->pT_APP_IP, pstCfg->pT_APP_PORT, pstCfg->pT_APP_PATH, pstCfg->pT_APP_ID);
        i++;
        pstCfg++;
    }
	shmdt(iShId);
    
    return 0;
}
/*
 * 获取共享内存的id
 */
int GetShMemId()
{

    key_t tKey= ftok("/home/shen/tc/tc_shmat/shm.ini", 1);
    //int iId = shmget(IPC_PRIVATE, 1024, IPC_CREAT|0666);
    int iId = shmget(tKey, 102400, IPC_CREAT|0666);
    printf("tKey = %d. id = [%d]\n",tKey,  iId);
    if (iId < 0) return -1;
    return iId;
}
