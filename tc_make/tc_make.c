#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <sys/types.h>
#define global
global int g_iTag = 0;
int main(void)
{
	int i = 1;
	char acStr[3] = "st";
	char acBuf[9] = {0};
	char acEmpty[10] = {0};
	char* pc = NULL;
	
	pc = acEmpty;
    printf("Hello World!\n");
    printf("pc = [%s] isNull = [%d]\n", pc, pc!=NULL);
    return 0;
}


