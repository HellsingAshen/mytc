#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/shm.h>
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
	int iShId = GetShMemId();
	if (iShId <= 0) {
		printf("Get share memory id failed.\n");
		exit(0);
	}
	
	pid_t pPid = fork();
	/* parent write data*/
	if (pPid > 0){
		/* 映射进程的地址*/
		pcTest = shmat(iShId, 0, 0);
		if (pcTest){
			strcpy(pcTest, "hello");
			printf("parent>>>>>>write ok.\n");
		}
		shmdt(iShId);
	}
	else{
		sleep(3);
		pcSon = shmat(iShId, 0, 0);
		if(pcSon){
			printf("son ---[%s].\n", pcSon);
		}
		shmdt(iShId);
	}
	while(1);
	return 0;
}
/*
 * 获取共享内存的id
 */
int GetShMemId()
{

	key_t tKey= ftok("/home/shen/tc/tc_shmat/shm.ini", 1);
    //int iId = shmget(IPC_PRIVATE, 1024, IPC_CREAT|0666);
    int iId = shmget(tKey, 1024, IPC_CREAT|0666);
	printf("Key = %d.\n", iId);
	if (iId < 0) return -1;
	return iId;
}
