#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MAX_BUF (1024)
int GetMsgId();
typedef struct tagMsg_S{
        char acBuf[MAX_BUF];
        int  iMsgType;

}Msg_S;
/*
 *@des：再学习共享内存
 *@caution: 
 */
int main(int argc, char* argv)
{
	int iRun = 1;
	int iMsgType = 0;
	Msg_S stMsg ;
    int iId = GetMsgId();
    if (iId <= 0) {
        printf("Get msg queue id failed.\n");
        exit(0);
    }
	
	while (iRun){
		if (msgrcv(iId, (void*)&stMsg, MAX_BUF, iMsgType, 0) == -1){
			printf("msgrcv error. \n");
			exit(0);
		}
		printf("rec data = [%s] iMsgType = [%d].\n", stMsg.acBuf, iMsgType);
		if (!strncmp(stMsg.acBuf, "end", 3)){
			printf("rec end. exit.\n");
			iRun = 0;
		}
	}
    
    return 0;
}
/*
 * 获取消息队列的id
 */
int GetMsgId()
{
    int iId = msgget((key_t)1234, IPC_CREAT|0666);
    if (iId < 0) return -1;
    return iId;
}
