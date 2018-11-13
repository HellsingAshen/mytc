#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_BUF (1024)
typedef struct tagMsg_S{
	char acBuf[MAX_BUF];
	int  iMsgType;

}Msg_S;
int GetMsgId();
/*
 *@des：再学习消息队列
 *@caution: 
 */
int main(int argc, char* argv)
{
	int iRun = 1;
	char acBuf[MAX_BUF] = {0};
	Msg_S stMsg;

	printf("hello cli.\n");
	int iId = GetMsgId();
	if (iId <= 0) {
		printf("Create msg queue failed.\n");
		exit(0);
	}
	
	while (iRun){
		printf("please enter your msg:\n");
		fgets(acBuf, MAX_BUF, stdin);
		stMsg.iMsgType = 1;
		strcpy(stMsg.acBuf, acBuf);
		
		if (msgsnd(iId, (void*)&stMsg, MAX_BUF, 0) == -1){
			printf("msgsnd error.\n");
			exit(0);
		}

		if (!strncmp(acBuf, "end", 3)){
			iRun = 0;
			printf("msgsnd cli exit.\n");
		}

	}
	
	return 0;
}
/*
 * 创建消息队列的id
 */
int GetMsgId()
{
    int iId = msgget((key_t)1234, IPC_CREAT|0666);
	if (iId < 0) return -1;
	return iId;
}
