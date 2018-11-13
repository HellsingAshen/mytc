#include <stdlib.h>
#include <stdio.h>
#include "tc_common.h"

/*
 * 1. 执行linux 命令符
 * 2. 程序抓取linux命令字的执行结果显示
*/
int Tc_Popen()
{
    int         iRet            = OK;
    char        acCmdStr[256]   = {0};
    char        acRetBuf[256]   = {0};
    FILE*       *fp             = NULL;

    do 
    {
        strcpy(acCmdStr, "date");
        fp  = popen(acCmdStr, "r");
        BIN(fp);

        while (NULL != fgets(acRetBuf, sizeof(acRetBuf), fp))
        {
            acRetBuf[sizeof(acRetBuf) -1 ] = '\0';
            printf("in app, get ret = [%s].\n", acRetBuf);
        }

    } while (0);

    pclose(fp);
    return iRet;
}
/* MAIN */
int main(void)
{
    int         iRet            = OK;
    do
    {
        iRet    = Tc_Popen();
        BIE(iRet);

    } while (0);
    return 0;
}


