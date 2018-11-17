#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <setjmp.h>
#include "common.h"


#define MAX_BUF_LEN (10240)
#define PORT        (8000)
#define USAGE       ("src run with listen-port[8000] and default-sendrspbuf[rec your msg.]")
#define MSG_LEN     (4)

jmp_buf env;
void pro_alarm(int is)
{
    longjmp(env, 1);
}
/*
 * @des: socket server
 * @caution: 
 */
int main(int argc, char** argv)
{
    struct sockaddr_in stSock = {0};

    /* create socket fd */
    int iSockId     = -1;
    int iConnectFd  = -1;
    int iRecCount   = 0;
    int iSockLen    = 0;
    int i           = 0;
    int iPort       = PORT;
    int iMsgLen     = 0;
    int iRspLen     = 0;
    int iRecCurLen  = 0;
    int iSndLen     = 0;

    char acRspBuf[MAX_BUF_LEN - 4 ] = {"rec your msg."};
    char acSndRspBuf[MAX_BUF_LEN]   = {0};
    char acBuf[MAX_BUF_LEN]         = { 0 };

    if (argc < 2)
    {
        printf("USAGE: [%s].\n", USAGE);
    }
    else
    {

        for (i = 0; i < argc; i++)
        {
            if (!strcmp (argv[i], "-port"))
            {
                iPort = atoi (argv[i + 1]);
                printf ("start to listen port is [%d].\n", iPort);
                continue;
            }

            if (!strcmp (argv[i], "-rsp"))
            {
                memset(acRspBuf, 0x00, sizeof(acRspBuf));
                strcpy(acRspBuf, argv[i + 1]);
                printf ("prepare to send rsp data is [%s].\n", acRspBuf);
                continue;
            }
        }
    }

    /* init sock para */
    stSock.sin_family    = AF_INET;
    stSock.sin_addr.s_addr    = htonl(INADDR_ANY);
    stSock.sin_port    = htons(iPort);

    if (-1 == (iSockId = socket(AF_INET, SOCK_STREAM, 0)))
    {
        printf("Create socket error. exit.\n");
        close(iSockId);
        exit(0);
    }    

    /* bind */
    if (-1 == bind(iSockId, (struct sockaddr *)&stSock, sizeof(struct sockaddr))){
        printf("Bind socket error. exit.\n");
        close(iSockId);
        exit(0);
    }

    /* listen */
    if (-1 == listen(iSockId, 10)){
        printf("Bind socket error. exit.\n");
        close(iSockId);
        exit(0);
    }

    iSockLen    = sizeof(stSock);
    /* accept */
    while (1)
    {
        if (-1 == (iConnectFd = accept(iSockId, (struct sockaddr*)&stSock, &iSockLen))){
            printf("accept socket error. continue.\n");
            close(iConnectFd);
            continue;
        }
        printf("accept socket ok. do recv.\n");

        /* rec len*/
        iRecCount = recv(iConnectFd, acBuf, MSG_LEN, 0);
        if (iRecCount < 0){
            printf("rec error. continue.\n");
            close(iConnectFd);
            continue;
        }
        printf("rec buf len = [%x] [%x] [%x] [%x].\n", acBuf[0], acBuf[1], acBuf[2], acBuf[3]);
		/*
        iMsgLen =  (acBuf[0]<<24) + (acBuf[1]<<16) + (acBuf[2]<<8) + (acBuf[3]);
    	*/

        printf("#####################################\n");
        Str2Long(acBuf, MSG_LEN, (long*)&iMsgLen);
        Test();

        printf("iMsgLen = [%d].\n", iMsgLen);
        if (iMsgLen <= 0)
        {
            continue;
        }  

        /* rec actual len */
        memset(acBuf, 0, sizeof(acBuf));
        iRecCurLen = 0;

        signal(SIGALRM, pro_alarm);
        alarm (60);
        if (setjmp(env) == 1)
        {
            alarm (0);
            signal(SIGALRM, pro_alarm);
            return -1;
        }

        while (iMsgLen - MSG_LEN > iRecCurLen)
        {
            iRecCount = 0;
            iRecCount = recv(iConnectFd, acBuf + iRecCurLen, MAX_BUF_LEN - MSG_LEN - iRecCurLen, MSG_WAITALL);
            if (iRecCount < 0)
            {
                printf("rec error. continue.\n");
                continue;
            }
            iRecCurLen  = iRecCurLen + iRecCount;
            printf("rec ok.iRecCount = [%d]\n", iRecCount);
        }

        printf("###Rec buf = [%s]. rec length = [%d]###.\n", acBuf, iRecCount);

        signal(SIGCHLD, SIG_IGN);
        if (!fork())
        {
            /* son process */

			(void)
			/*
            acSndRspBuf[0] = ((strlen(acRspBuf) + 4)>>24) & 0xff;
            acSndRspBuf[1] = ((strlen(acRspBuf) + 4)>>16) & 0xff ;
            acSndRspBuf[2] = ((strlen(acRspBuf) + 4)>>8)  & 0xff;
            acSndRspBuf[3] = (strlen(acRspBuf) + 4) & 0xff;
			*/
			Long2Str((long)(strlen(acRspBuf) + 4), MSG_LEN, acSndRspBuf);
            memcpy(acSndRspBuf + 4, acRspBuf, strlen(acRspBuf));

            iSndLen = strlen(acRspBuf) + 4;

            printf("sendRspBuf iSndLen = [%d]. len = [%x] [%x] [%x] [%x]. RspBuf = [%s].\n",
                    iSndLen, acSndRspBuf[0], acSndRspBuf[1], acSndRspBuf[2], acSndRspBuf[3], &acSndRspBuf[4]);

            acSndRspBuf[MAX_BUF_LEN - 1] = '\0';

            if (-1 == send(iConnectFd, acSndRspBuf, strlen(acRspBuf) + 4, 0))
            {
                printf("child pro send error. exit.\n");
                close(iConnectFd);
                exit(0);
            } 
            printf("send to client ok.\n");
            close(iConnectFd);
            exit(0);
        }

        acBuf[MAX_BUF_LEN - 1]    = '\0';

        //sleep(2);
        close(iConnectFd);

    }

    printf("rec end. exit.\n");
    close(iSockId);
    return 0;
}
