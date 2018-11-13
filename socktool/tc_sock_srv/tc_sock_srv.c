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
    if (-1 == listen(iSockId, 3)){
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
#if 1
        int iSndCnt = 0;
        if (!fork())
        {
            memset(acSndRspBuf, 0, sizeof(acSndRspBuf));
            printf("accept socket ok. iConnectFd = [%d] son pro test.\n", iConnectFd);
            if ((iSndCnt = send (iConnectFd, "rec your msg.", strlen("rec your msg."), 0)) < 0)
            {
                printf("Snd Rsp error.\n");
            }
            close(iConnectFd);
            exit(0);
        }
#endif
        continue;

    }

    printf("rec end. exit.\n");
    close(iSockId);
    return 0;
}
