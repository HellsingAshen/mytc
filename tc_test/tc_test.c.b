#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <sys/types.h>
#define global
global int g_iTag = 0;

int Tc_Factorial(int iVal)
{
    if (1 == iVal || 0 == iVal )
    {
        return 1;
    }
    else
    {
        return iVal * Tc_Factorial(iVal - 1);
    }
}

int Tc_Recursive(int iDep)
{

    printf(" my   ");
    if (!iDep)
    {
        printf("happy ending .\n");

    }else
    {
        Tc_Recursive(--iDep);
    }
    printf(" end.  ");
    
    return 0;
}
typedef struct tagPerson_S
{
    int     iAge;
    char    acName[20];
}Person_S;
#define DESC(str) 1

/*
 * @ desc: main
 * @ input:
 * @ output:    
 * @ cautious:	
 */

int main(void)
{
    int iDeep = 4;

/**
    (void)Tc_Recursive(iDeep);
**/
    printf("factorial(%d))= [%d].\n", iDeep, Tc_Factorial(iDeep));
#if 0
    int         i       = 0;
    Person_S* pstPs     = malloc(sizeof(Person_S) * 20);
    Person_S  stP1      = {1, "shen"};  
    Person_S* pstP      = NULL;

    pstPs[1] = stP1;
    pstPs[10].iAge = 10;
    memcpy(pstPs[10].acName, "ten", 3);

    *(pstPs +  11) = stP1;
    
    for (; i < 20; i++)
    {
        printf("i = [%d] age = [%d] acName = [%s].\n", i, pstPs[i].iAge, pstPs[i].acName);
    }

    
#endif









#if DESC("test void* len ") - 1
    printf(" void* len = [%d].\n", sizeof(void*));
    printf(" char* len = [%d].\n", sizeof(char*));

#endif

#if DESC("test void* len ") - 1
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


