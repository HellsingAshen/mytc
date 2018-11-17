#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <sys/types.h>
#define global
global int g_iTag = 0;

#define DESC(str) 1

/*
 * @ desc: main
 * @ input:
 * @ output:    
 * @ cautious:	
 */

int main(void)
{
	
#if DESC("test void* len ") - 0
    printf(" void* len = [%d].\n", sizeof(void*));
    printf(" char* len = [%d].\n", sizeof(char*));

#endif

#if 0
	int i = 1;
	char acStr[3] = "st";
	char acBuf[9] = {0};
	char acEmpty[10] = {0};
	char* pc = NULL;
	
	pc = acEmpty;
    printf("Hello World!\n");
    printf("pc = [%s] isNull = [%d]\n", pc, pc!=NULL);
#endif
    return 0;
}


