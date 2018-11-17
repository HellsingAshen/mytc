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
	printf("hello tool.\n");
	char* pcTest;
	char* pcSon;
	CFG stCFG = {"003|02|", "127.0.0.1", "9999", "/home/sjx/", "0001"};
	int i = 0;
	CFG* pstCfg = NULL;
	int iShId = GetShMemId();
	if (iShId <= 0) {
		printf("Get share memory id failed.\n");
		exit(0);
	}
	printf("in shmtest,get shmId = [%d].\n", iShId);
	pcTest = shmat(iShId, 0, 0);
	if (!pcTest) return -1;
	pstCfg = pcTest;
	
	printf("start to write shmdata.\n");
	while (i < 10)
	{
		memcpy(pstCfg, &stCFG, sizeof(CFG));	
		sprintf(pstCfg->pT_APP_ID, "%019d", i);
		pstCfg++;
		i++;
	}
	printf("write shmdata done.\n");

	shmdt(iShId);
	return 0;
}
/*
 * 获取共享内存的id
 */
int GetShMemId()
{

	key_t tKey= ftok("/home/shen/tc/tc_shmat/shm.ini", 1);
    int iId = shmget(tKey, 102400, IPC_CREAT|0644);
	printf("Key = %d.\n", iId);
	if (iId < 0) return -1;
	return iId;
}
