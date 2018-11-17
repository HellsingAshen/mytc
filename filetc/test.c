#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define        OK         (0)

#define        SIZE        (100)
/* char g_acStr[] = {"一二三四五六七八九十百千万1234567890"};*/
char g_acStr[] = {"1234567890"};
int DoTest()
{
    FILE                *fp     = NULL;
    int                 iRet    = 0;
    char                acArr[10] = {0}; 
    int                 iLen    = 0;

    if (NULL != (fp = fopen("/home/eftp/tool/filetc/abc", "a+")))
    {
       
        do
        {
            iLen    = rand()%10;
            printf("iLen = [%d].\n", iLen);
            memset(acArr, 0, sizeof(acArr));
            memcpy(acArr, &g_acStr[0], iLen);
            
            if (fwrite(acArr, 1, iLen, fp) < 0)
            {
                printf("fwrite failed .\n");

            }
            if (fwrite("\n", 1, 1, fp) < 0)
            {
                printf("fwrite failed .\n");

            }
            printf ("do write next str[%s] .\n", acArr);
            fflush(fp);

            sleep(10);
        } while (1);

        fclose(fp);
        return 0;
        

    }
    printf("fopen failed.\n");

    return iRet;

}


int main ()
{
	int iRet = 0;

    (void)DoTest();

    return OK;
}
