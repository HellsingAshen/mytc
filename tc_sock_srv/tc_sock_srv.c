#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


#define MAX_BUF_LEN (10240)
#define PORT 	(1111)


/*
 *@des：再学习socket server
 *@caution: 
 */
int main(int argc, char* argv)
{
	struct sockaddr_in stSock = {0};

	/* create socket fd */
 	int iSockId = -1;
 	int iConnectFd = -1;
	int iRecCount = 0;
	char acBuf[MAX_BUF_LEN] = { 0 };
    int             iSockLen    = 0;
	
	stSock.sin_family	= AF_INET;
	stSock.sin_addr.s_addr	= htonl(INADDR_ANY);
	stSock.sin_port	= htons(PORT);

	if (-1 == (iSockId = socket(AF_INET, SOCK_STREAM, 0))){
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
	while (1){
		if (-1 == (iConnectFd = accept(iSockId, (struct sockaddr*)&stSock, &iSockLen))){
    		printf("accept socket error. continue.\n");
            close(iConnectFd);
			continue;
		}
    	printf("accept socket ok. do recv.\n");

		/* rec */
		iRecCount = recv(iConnectFd, acBuf, MAX_BUF_LEN, 0);
		if (iRecCount < 0){
    		printf("rec error. continue.\n");
            close(iConnectFd);
			continue;
		}
        printf("Rec buf = [%s]. rec length = [%d].\n", acBuf,  iRecCount);

		if (!fork())
        {
			/* son process */
			if (-1 == send(iConnectFd, "recv your msg, client.\n", 23, 0)){
				printf("child pro send error. exit.\n");
				close(iConnectFd);
				exit(0);
			} 
			printf("send to client ok.\n");
			close(iConnectFd);
			exit(0);
		}
		
		acBuf[MAX_BUF_LEN]	= '\0';

		printf("rec msg  = [%s].\n", acBuf);
        sleep(2);
        close(iConnectFd);
	
	}
	
    printf("rec end. exit.\n");
	close(iSockId);
    return 0;
}
