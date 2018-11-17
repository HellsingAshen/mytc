#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_BUF_LEN (1024)
#define PORT 	(8000)


/*
 *@des：再学习socket client
 *@caution: 
 */
int main(int argc, char** argv)
{

	struct sockaddr_in stSock = {0};

	/* create socket fd */
 	int iSockId = -1;
 	int iConnectFd = -1;
	int iRecCount = 0;
	char acBuf[MAX_BUF_LEN] = { 0 };
	char acRecBuf[MAX_BUF_LEN] = { 0 };
	
	if (argc < 2) {
		printf("in para err.\n");	
		exit(0);	
	}

	stSock.sin_family	= AF_INET;
	/* stSock.sin_addr.s_addr	= htonl(INADDR_ANY); */
	stSock.sin_port	= htons(PORT);

	/* create */
	if (-1 == (iSockId = socket(AF_INET, SOCK_STREAM, 0))){
    	printf("Create socket error. exit.\n");
		exit(0);
	}	
	/* connect */
	if (inet_pton(AF_INET, argv[1], &stSock.sin_addr) < 0){
		printf("convert error.\n");	
		exit(0);
	}
	
	if (connect(iSockId, (struct sockaddr*)&stSock, sizeof(struct sockaddr)) < 0){
		printf("connect error.\n");
		exit(0);
	}

	printf("prepare to send srv.\n");
	fgets(acBuf, MAX_BUF_LEN, stdin);
	if (send(iSockId, acBuf, strlen(acBuf), 0) < 0){
		printf("send error.\n");
		exit(0);
	}
	
	if (0 > (iRecCount = recv(iSockId, acRecBuf, MAX_BUF_LEN, 0))){
		printf("srv rec error.\n");
		close(iSockId);
		exit(0);
	}
	close(iSockId);
    printf("rec end.rec = [%s] exit.\n", acRecBuf);
    return 0;
}
