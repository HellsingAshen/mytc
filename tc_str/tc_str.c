#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <sys/types.h>
#include <errno.h> 
#include <fcntl.h>  
#define global
global int g_iTag = 0;
//int WriteFile(void)
int main(void)
{
	int i = 0;
	char acCon[3] = "st";
	//char acBuf[9] = {0};
	char acSpr[10] = {0};
	char acStr[10] = {0};
	char acBuf[500] = {"12345"};
	char* pc = "NULL";
	FILE* fp	= NULL;
	int iCount	 = 0;
	
	if (fp = fopen("./ts.log", "a+"))
	{
		printf("start write.\n");
		//fprintf(fp, "hello.\n");
		//iCount =  fwrite(acBuf, 1, strlen(acBuf), fp);
		iCount =  fwrite(acBuf, 1, strlen(pc), fp);
		printf("iCount = [%d] \n", iCount);
		fclose(fp);
		fp = NULL;
	}
	if (fp)	fclose(fp);
#if 0
	//pc = acEmpty;
    printf("Hello World!\n");
    //printf("pc = [%s] isNull = [%d] strlen-pc= [%d]\n", pc, pc!=NULL, pc);
	/*error test when pc = null*/ //sprintf(acEmpty, "%s", pc);
	sprintf(acSpr, "%s", acCon);
	strcpy(acStr,  acCon);
	printf("[%s][%s]\n", acSpr, acStr);
#endif
	
	
	
    return 0;
}


