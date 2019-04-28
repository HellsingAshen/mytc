#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <regex.h>

jmp_buf jbf;
void  pro_signal_alarm(int iSigNo)
{
    longjmp(jbf, 1);
#if 0
    while (1)
    {
        sleep (1);
        printf("get signal [%d].\n", iSigNo);
    }
#endif
    return;
}

int main(void)
{
    signal(SIGALRM, pro_signal_alarm);
    alarm(10);

    if (setjmp(jbf) == 1) 
    {
        printf("setjmp, exit.\n");
        return 0;
    }
    while (1)
    {
        sleep (1);
        printf("in main .\n");
    
    }

    printf("after alarm.\n");
    return 0;
}


