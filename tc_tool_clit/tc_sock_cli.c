#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "common.h"
#include "logf.h"


#define MAX_BUF_LEN (1024 * 10)
#define PORT     (8000)
#define USEAGE "Useage:-port [port]  -ip [ip] -data [sendData] -lencode [hex/oct]."

typedef enum tagLenCodeType_E
{
	LenCodeType_NoLen = 0x00,
	LenCodeType_Hex = 0x01,	/* Len by Hex */
	LenCodeType_Oct = 0x02,	/* Len by Oct */

} LenCodeType_E;

/*
 *@des: socket client
 *@caution: 
 */
	int
main (int argc, char **argv)
{

	struct sockaddr_in stSock = { 0 };
	struct sockaddr_in stSrvSock = { 0 };

	/* create socket fd */
	int iSockId = -1;
	int iConnectFd = -1;
	int iRecCount = 0;
	char acSendLen[5] = { 0 };
	char acConvSendLen[9] = { 0 };

	char acBuf[MAX_BUF_LEN + 1] = { 0 };
	char acRecBuf[MAX_BUF_LEN + 1] = { 0 };
	char acSendBuf[MAX_BUF_LEN + 1] = { 0 };

	int iPort = 10002;
	char acIp[64] = { "192.168.43.69" };
	int i = 0;
	int iSendCount = 0;
	LenCodeType_E enLenCodeType = LenCodeType_NoLen;
	int iTotalSendLen = 0;


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

		if (!strcmp (argv[i], "-port"))
		{
			iPort = atoi (argv[i + 1]);
			printf ("get port = [%d].\n", iPort);
			continue;
		}

		if (!strcmp (argv[i], "-data"))
		{
			memset (acBuf, 0x00, sizeof (acRecBuf));
			strcpy (acBuf, argv[i + 1]);
			iRecCount = strlen (acBuf);
			printf ("get inbuf = [%s] Len = [%d].\n", acBuf, iRecCount);
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

	stSock.sin_family = AF_INET;
	stSock.sin_addr.s_addr = htonl (INADDR_ANY);	/* get local addr for client */
	stSock.sin_port = htons (0);	/* usg sys dispatch */

	/* create */
	if (-1 == (iSockId = socket (AF_INET, SOCK_STREAM, 0)))
	{
		printf ("Create socket error. exit.\n");
		exit (0);
	}

	printf ("Create socket OK. .\n");

	/* bind */
	if (bind (iSockId, (struct sockaddr *) &stSock, sizeof (stSock)) < 0)
	{
		printf ("Client Bind Port Failed!\n");
		exit (1);
	}
	printf ("bind socket OK.\n");

	/* server */
	stSrvSock.sin_family = AF_INET;
	if (inet_pton (AF_INET, acIp, &stSrvSock.sin_addr) < 0)
	{
		printf ("convert error.\n");
		exit (0);
	}
	stSrvSock.sin_port = htons (iPort);
	printf ("srv socket OK.\n");

	/* connect */
	if (inet_pton (AF_INET, acIp, &stSrvSock.sin_addr) < 0)
	{
		printf ("convert error.\n");
		exit (0);
	}

	while (1)
	{
		if (connect
				(iSockId, (struct sockaddr *) &stSrvSock,
				 sizeof (struct sockaddr)) < 0)
		{
			sleep (1);
			printf ("Connect failed.  Trying to connect now.\n");
			continue;
		}
		else
		{
			break;
		}
	}

	printf ("connect socket OK.\n");
	if (enLenCodeType)
	{
		if (enLenCodeType & LenCodeType_Hex)
		{
			/*
			   sprintf (acSendLen, "%04x", strlen (acBuf));
			   printf ("acSendLen = [%s].\n", acSendLen);
			   memset (acSendBuf, 0x00, sizeof (acSendBuf));

			   Hex2Str(acSendLen, acConvSendLen, strlen(acSendLen));
			//      strcpy(acSendBuf, acSendLen);
			//      strcpy(acSendBuf + strlen(acSendBuf), acBuf);
			strcpy(acSendBuf, acConvSendLen);
			strcpy(acSendBuf + strlen(acSendBuf), acBuf);
			*/

			memcpy (acSendBuf + 4, acBuf, strlen (acBuf));
			iTotalSendLen = 4 + strlen (acBuf);
			acSendBuf[0] = 0x00;
			acSendBuf[1] = 0x00;
			acSendBuf[2] = iTotalSendLen / 256;
			acSendBuf[3] = iTotalSendLen % 256;

		}
		else if (enLenCodeType & LenCodeType_Oct)
		{
			sprintf (acSendLen, "%04d", strlen (acBuf));
			printf ("acSendLen = [%s].\n", acSendLen);
			memset (acSendBuf, 0x00, sizeof (acSendBuf));
			strcpy (acSendBuf, acSendLen);
			strcpy (acSendBuf + strlen (acSendBuf), acBuf);
		}
	}
	else
	{
		printf ("Send buf with no length.\n");
		strcpy (acSendBuf, acBuf);
	}

	printf ("prepare to send srv Buf = [%d]\n", iTotalSendLen);
	printf ("prepare to send srv Buf = [%02x][%02x][%02x][%02x].\n",
			acSendBuf[0], acSendBuf[1], acSendBuf[2], acSendBuf[3]);
	//printf ("prepare to send srv Buf = [%s].\n", acSendBuf+4);

	iRecCount = iTotalSendLen;
sleep (10);
    close(iSockId);
printf("start sleep.\n");
sleep (10);
	while (iTotalSendLen > iSendCount)
	{
		if ((iSendCount = send (iSockId, acSendBuf, iRecCount, 0)) < 0)
		{
			printf ("send error.\n");
			close (iSockId);
			exit (0);
		}
		printf ("Send buf = [%s], sendlen=[%d].\n", acBuf, strlen (acBuf));
		iTotalSendLen -= iSendCount;
	}

	printf ("prepare to read srv  msg.\n");

#if 1
	memset (acRecBuf, 0x00, sizeof (acRecBuf));
	if (0 > (iRecCount = recv (iSockId, acRecBuf, 4, 0)))
	{
		printf ("srv rec error.\n");
		close (iSockId);
		//exit (0);

	}
	printf ("iRecCount=[%d]\n", iRecCount);
	if (iRecCount < 4)
	{
		printf ("iRecCount < 4[%d]\n", iRecCount);
		close (iSockId);
		return 0;
	}
	iTotalSendLen = acRecBuf[2] * 256 + acRecBuf[3];
	printf ("iTotalSendLen=[%d]\n", iTotalSendLen);
	memset (acBuf, 0x00, sizeof (acBuf));
	iSendCount = 0;
	memset (acRecBuf, 0x00, sizeof (acRecBuf));
	while (iTotalSendLen > iSendCount + 4)
	{
		if (0 >
				(iRecCount = recv (iSockId, acRecBuf + iSendCount, 10240, 0)))
		{
			printf ("srv rec error.\n");
			close (iSockId);
		}
		printf ("iRecCount=[%d]\n", iRecCount);
        LOGHEXD(acRecBuf + iSendCount, MAX_BUF_LEN - 1);
		iSendCount += iRecCount;
	}
	if (iSendCount != iTotalSendLen - 4)
	{
        LOGD("##################iSendCount is not equal iTotalSenLen -4>>>>>>>>>>>>>>>>>>>\n");

		printf ("\n recv error!\n");
		printf ("real redd iRecCount=[%d],need len iTotalSendLen=[%d]\n",
				iRecCount, iTotalSendLen);
		printf ("rec end.rec =[%s] \n", acRecBuf);
        LOGHEXD(acRecBuf, sizeof(acRecBuf));
        LOGD("##################iSendCount is not equal iTotalSenLen -4<<<<<<<<<<<<<<<<<\n");
	}
	else
	{
		printf ("recv ok \n");
		printf ("rec end.rec =[%s] \n", acRecBuf);
	}
	//printf ("rec end.rec =[%s] exit.\n", acRecBuf);
	//sleep(4);
#endif
	close (iSockId);
	return 0;
}
