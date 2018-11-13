#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <sys/types.h>
#include <errno.h> 
#include <fcntl.h>  
#include <signal.h>  
#include <sys/wait.h>

#define MAX_NUM_PID  1000
#define MAX_RUN_TIME  1000
#define Prt    printf
#define OK 		0
#define ERR 	-1	

int g_iTag = 0;
int g_iChildRunTime = 0;
int ChildMainPro()
{
	sleep(10);
	return OK;
}
int SigChldProc(int iSigNo)
{
	pid_t tPid = 0;
	while ((tPid = waitpid(-1, NULL, WNOHANG)) > -1);
	return OK;
}

int main(void)
{
	int 		i  			= 0;
	int			pid 	 	= 0;	

	if ((pid = fork()) < -1)
	{
		Prt("fork error.\n");
		return ERR;
	}
	else if (0 != pid)
	{
		return OK;	

	}

	/* fork test*/
	signal(SIGCHLD, SigChldProc);
	while (1)
	{
		while (i < MAX_NUM_PID)
		{
			pid = fork();
			if (pid < 0)
			{
				Prt("fork error.\n");
				return ERR;
			}
			else if (0 == pid)
			{
				ChildMainPro();
				exit(0);
			}
			else
			{
			}
			i++;
		}
	}
	
	
	
	
    return 0;
}


