#include <stdlib.h>
#include <stdio.h>
#include "logf.h"
#include <string.h>

int main()
{
    int                 iRet    = 0;
	int					i = 0;
	LogMode_E			enE = LOG_MODE_OFF;
    printf("start test. i = [%d] enE = [%d]\n", i, enE);
    

    iRet    = Log("abc", LOG_MODE_DEBUG, __FILE__, __LINE__, "%s\n", "hello");
    if (iRet)
    {
        printf(" iRet = [%d].\n", iRet);
    }

    iRet    = LogHexString("bcd", LOG_MODE_ERR, __FILE__, __LINE__, "abc", (int)strlen("abc"));
    if (iRet)
    {
        printf(" iRet = [%d].\n", iRet);
    }

	LOGD("in func LOGD.");
	LOGHEXD("in func LOGHEXD.", strlen("in func LOGHEXD."));

	LOG("logd", LOG_MODE_ERR, "in func LOGD.");
	LOGHEX("loghex", LOG_MODE_ERR, "in func LOGHEXD.", (int)strlen("in func LOGHEXD."));
	
	return 0;
}
