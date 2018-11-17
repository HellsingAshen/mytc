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
    char                acArr[1024] = {0}; 
    int                 iLen    = 0;

    if (NULL != (fp = fopen("/home/eftp/tool/filetc/abc", "r")))
    {
       
        do
        {
            while (!feof(fp))
            {
                memset(acArr, 0, sizeof(acArr));
                iLen = fread(acArr, 1, 1023, fp);
                {
                    printf("acArr = [%s].\n", acArr);
                }
            }
            sleep(5);
            printf("file get end. do next\n");
        } while (1);

    }
    printf("fopen failed.\n");

    fclose(fp);

    return iRet;

}


int main ()
{
	int iRet = 0;

    (void)DoTest();

    return OK;
}
