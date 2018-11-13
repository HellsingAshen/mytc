#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "common.h"
#include "logf.h"
#include <errno.h>
#include "public_macro.h"

#define MAX_BUF_LEN     (1024 * 10)
#define BUF_LEN         (6)
#define PORT            (8000)
#define USEAGE "Useage:[-client] -port [port]  -ip [ip] -data [sendData] -lencode [hex/oct] -number [clientnum]" 
#define MAX_CHILD_NUM   (1023)

typedef enum tagLenCodeType_E
{
    LenCodeType_NoLen = 0x00,
    LenCodeType_Hex = 0x01,    /* Len by Hex */
    LenCodeType_Oct = 0x02,    /* Len by Oct */

} LenCodeType_E;

int DoConnect(
    char    *pcIp,
    int     iPort
)
{
    int iRet            = 0;
    int iSockId         = -1;
    int iConnectFd      = -1;
    int iRecCount       = 0;
    char acSendLen[5]   = { 0 };
    char acConvSendLen[9] = { 0 };

    char acBuf[MAX_BUF_LEN + 1]     = { 0 };
    char acRecBuf[MAX_BUF_LEN + 1]  = { 0 };
    char acSendBuf[MAX_BUF_LEN + 1] = { 0 };

    struct sockaddr_in stSock = { 0 };
    struct sockaddr_in stSrvSock = { 0 };

    stSock.sin_family = AF_INET;
    stSock.sin_addr.s_addr = htonl (INADDR_ANY);    /* get local addr for client */
    stSock.sin_port = htons (0);    /* usg sys dispatch */
    
    RETURN_IF_FAILED(pcIp == NULL);
    RETURN_IF_FAILED(iPort < 0);

    /* create */
    if (-1 == (iSockId = socket (AF_INET, SOCK_STREAM, 0)))
    {
        printf ("Create socket error. exit.\n");
        RETURN_IF_FAILED(-1);
    }

    printf ("Create socket OK. .\n");

    /* bind */
    if (bind (iSockId, (struct sockaddr *) &stSock, sizeof (stSock)) < 0)
    {
        printf ("Client Bind Port Failed!\n");
        RETURN_IF_FAILED(-1);
    }
    printf ("bind socket OK.\n");

    /* server */
    stSrvSock.sin_family = AF_INET;
    if (inet_pton (AF_INET, pcIp, &stSrvSock.sin_addr) < 0)
    {
        printf ("convert error.\n");
        RETURN_IF_FAILED(-1);
    }

    stSrvSock.sin_port = htons (iPort);

    /* connect */
    if (inet_pton (AF_INET, pcIp, &stSrvSock.sin_addr) < 0)
    {
        printf ("convert error.\n");
        RETURN_IF_FAILED(-1);
    }

    while (1)
    {
        if (connect
                (iSockId, (struct sockaddr *) &stSrvSock,
                 sizeof (struct sockaddr)) < 0)
        {
            printf ("Connect failed.  Trying to connect now.\n");
            printf ("Connect failed. errno = [%d] errstr = [%s] Trying to connect now.\n", errno, strerror(errno));
            sleep (1);
            continue;
        }
        else
        {
            break;
        }
    }
    printf ("Connect Suc .\n");
    sleep (20);
        
    return iSockId;

}

int DoAsServer(int iPort, char* pcBuf)
{
    int             iRet            = 0;
    int             iSockId         = 0;
    struct sockaddr_in stSock       = {0};
    int             iSockLen        = 0;
    int             iConnectFd      = 0; 
    char            acBuf[MAX_BUF_LEN + 1] = {0};

    
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

    /** set sockopt **/

    /* bind */
    if (-1 == bind(iSockId, (struct sockaddr *)&stSock, sizeof(struct sockaddr))){
        printf("Bind socket error. exit.\n");
        close(iSockId);
        exit(0);
    }

    /* listen */
    if (-1 == listen(iSockId, 5))
    {
        printf("Bind socket error. exit.\n");
        close(iSockId);
        exit(0);
    }

    iSockLen    = sizeof(stSock);
    printf("Server start running .\n");
    /* accept */
    while (1)
    {
        if (-1 == (iConnectFd = accept(iSockId, (struct sockaddr*)&stSock, &iSockLen)))
        {
            printf("accept socket error. continue.\n");
            close(iConnectFd);
            continue;
        }

        if (0 > (iRecCount = recv(iConnectFd, acRecBuf, MAX_BUF_LEN, 0))){
            printf("srv rec error.\n");
            close(iSockId);
            exit(0);
        }
        printf("rec end.rec = [%s] exit.\n", acRecBuf);


        if (!fork())
        {
            if (send(iConnectFd, pcBuf, strlen(pcBuf), 0) < 0)
            {
                printf("send error.\n");
                close(iConnectFd);
                exit(0);
            }
            printf("accept socket ok. iConnectFd = [%d] son pro test.\n", iConnectFd);
            close(iConnectFd);
            exit(0);
        }
        sleep(3);

        close(iSockId);
    }


    return 0;
}


int DoAsClient(
    char    *pcIp,
    int     iPort,
    LenCodeType_E enLenCodeType,
    char*   pcBuf
)
{
    int             iRet            = 0;
    int             iLen            = 0;
    char            acBufLen[BUF_LEN + 1]       = {0};
    char            acSndBuf[MAX_BUF_LEN + 1]   = {0};
    char            acRecBuf[MAX_BUF_LEN + 1]   = {0};
    int             iSockId         = 0;
    int             iTotalLen       = 0;
    int             iSendCount      = 0;
    int             iRecCount       = 0;
    char            acRecBuf[MAX_BUF_LEN]       = {0};
    
    /** connect **/
    iSockId = DoConnect(pcIp, iPort);
    if (iSockId <= 0)
    {
        return iRet;
    }
    
    sprintf(acBufLen, "%06d", strlen(pcBuf));

    /** set len  with diff code **/
    switch (enLenCodeType)
    {
        case LenCodeType_Hex:
        {
            Str2Hex(acBufLen, acSndBuf, BUF_LEN);    
        }

        case LenCodeType_Oct:
        {
            memcpy(acSndBuf, acBufLen, BUF_LEN);
        }

        default:
        {
            printf("nothing to do.\n");
            break;
        }

    }

    /** set data **/
    memcpy(acSndBuf + BUF_LEN, pcBuf, strlen(pcBuf));
    iTotalLen = BUF_LEN + strlen(pcBuf);

    /** send data **/
    while (iTotalLen > iSendCount)
    {
        if ((iSendCount = send(iSockId, acSndBuf, iTotalLen, 0)) < 0)
        {
            printf("send error .\n");
            close(iSockId);
            return (-1);
        }
        iTotalLen -= iSendCount;
    }

    printf("send ok.\n");

    memset(acRecBuf, 0, sizeof(acRecBuf));

    if ((iRecCount = recv(iSockId, acRecBuf, BUF_LEN, 0)) < 0)
    {
        printf("recv len error.\n");
        close(iSockId);
    }

    /** close **/
    close(iSockId);
    return 0;
}

/*
 *@des: socket client
 *@caution: 
 */
int main (int argc, char **argv)
{
    struct sockaddr_in stSock = { 0 };
    struct sockaddr_in stSrvSock = { 0 };

    int iRet            = 0;
    /* create socket fd */
    int iSockId         = -1;
    int iConnectFd      = -1;
    int iRecCount       = 0;

    char acBuf[MAX_BUF_LEN + 1]     = { 0 };
    char acRspBuf[MAX_BUF_LEN + 1]  = { "rec your msg.\n" };

    int iPort = 10000;
    char acIp[64] = { "192.168.43.69" };
    int i = 0,j = 0, k = 0;
    int iSendCount = 0;
    LenCodeType_E enLenCodeType = LenCodeType_NoLen;

    int iPid = -1;
    int iIsClient       = 0; /* flag of client */
    int iChildNum       = 1;

    /* -port -ip -buf */
    if (argc < 3)
    {
        printf ("%s\n", USEAGE);
        exit (0);
    }

    for (i = 0; i < argc; i++)
    {
        if (!strcmp (argv[i], "-ip"))
        {
            memset (acIp, 0x00, sizeof (acIp));
            strcpy (acIp, argv[i + 1]);
            printf ("get ip = [%s].\n", acIp);
            continue;
        }

        if (!strcmp (argv[i], "-client") || !strcmp(argv[i], "-CLIENT"))
        {
            iIsClient = 1;
            continue;
        }

        if (!strcmp (argv[i], "-number"))
        {
            iChildNum = atoi (argv[i + 1]);
            printf ("get iChildNum = [%d].\n", iChildNum);
            continue;
        }

        if (!strcmp (argv[i], "-port"))
        {
            iPort = atoi (argv[i + 1]);
            printf ("get port = [%d].\n", iPort);
            continue;
        }


        if (!strcmp (argv[i], "-data"))
        {
            memset (acBuf, 0x00, sizeof (acBuf));
            strcpy (acBuf, argv[i + 1]);
            iRecCount = strlen (acBuf);
            printf ("get inbuf = [%s] Len = [%d].\n", acBuf, iRecCount);
            continue;
        }

        if (!strcmp (argv[i], "-rspdata"))
        {
            memset (acRspBuf, 0x00, sizeof (acRspBuf));
            strcpy (acRspBuf, argv[i + 1]);
            continue;
        }

        if (!strcmp (argv[i], "-lencode"))
        {
            if (!strcmp (argv[i + 1], "oct") || !strcmp (argv[i + 1], "OCT"))
            {
                enLenCodeType = LenCodeType_Oct;
                printf ("len code type is oct.\n");
                continue;
            }

            if (!strcmp (argv[i + 1], "hex") || (!strcmp (argv[i + 1], "HEX")))
            {
                enLenCodeType = LenCodeType_Hex;
                printf (" len code type is hex. \n");
                continue;
            }
        }

    }
    /** do connect test **/
    for (j = 0; j < iChildNum; j++)
    {
        iPid = fork();
        if (iPid < 0 ) return -1;
        else if (0 < iPid)
        {
            /** parent **/
            sleep(0.5);
            continue;
        }
        else
        {
            /** child process is only do connect when iIsClient flag is setted **/
            if (iIsClient)
            {
                iRet = DoAsClient(acIp, iPort, enLenCodeType, acBuf);
                BREAK_IF_FAILED(iRet);

            }
            else
            {
                iRet = DoAsServer(iPort, acRspBuf);
                /* BREAK_IF_FAILED(iRet); */
                break;
            }
        }
    }

    return iRet;
}
