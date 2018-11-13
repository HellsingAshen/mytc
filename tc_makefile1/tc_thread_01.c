#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#define global
global int g_iTag = 0;
int main(void)
{
    pid_t pPid = 0;
    int iTag = 10;
    if ( pPid = fork() < 0)
    {
        printf("fork err.\n");

    }
    else if (pPid ==0)
    {
        g_iTag++;
        iTag++;
        printf("son .\n");
    }
    else
    {
        sleep(2);
    }
    printf("g = %d, inner = %d\n", g_iTag, iTag);



    printf("Hello World!\n");
    return 0;
}


