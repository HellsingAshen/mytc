#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include "defchar.h"



void main ()
{
	char acStr1[1024] = "  1234567890\n";

	TrimLeft(acStr1);

	printf(acStr1);


	return;
}

int get_position(char *s_str, char *t_str)
{
  int i=0,isize=0;
  
  isize=strlen(s_str);
  for(i=isize-1; i>=0; i--)
  {
    if( s_str[i] == t_str[0] )
       return i + 1;
  }

  return 0;
}

void main3 ()
{
	DIR* 	dp = NULL;
#if 0

	int 	iRet = 0;
	iRet = get_position("/abc/", "/");
	printf("iRet = [%d].\n", iRet);

	iRet = get_position("//", "/");
	printf("iRet = [%d].\n", iRet);

	iRet = get_position("abc", "/");
	printf("iRet = [%d].\n", iRet);
#endif
	

#if 1
	FILE *fp = NULL;
	dp	= opendir("/home");	
	//fp=fopen("/home/eftp/tool/sndclient", "w+");
	
	//fp=fopen("/", "w+");
	if (dp != NULL) 
	{
		printf("fopen suc.\n");
	}
	else
	{
		printf("fopen fail.\n");
	}
	if (fp)
		fclose(fp);
#endif
	return;
}
