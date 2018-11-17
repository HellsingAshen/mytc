#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define        OK         (0)

#define        SIZE        (100)
char g_acStr[] = {"一二三四五六七八九十百千万1234567890"};
int DoTest()
{
    int iRet = 0;
    char aaacArr[SIZE][SIZE][SIZE] = {0};
    int i = 0, j = 0, k = 0;
    int iRand = 0, iOffset = 0;
    do 
    {
        for (i = 0; i < SIZE; i++)
        {
                for (j = 0; j < SIZE; j++)
                {
                        for (iOffset = 0; iOffset < SIZE; iOffset = iOffset + iRand)
                        {
                            iRand = rand()%10;
                            memcpy(&aaacArr[i][j][iOffset], &g_acStr[0], iRand);
                        }
                        printf("astr = [%s].\n", aaacArr[i][j]);
                    
                }
        }
    }while (0);
    
    return iRet;

}


int main ()
{
	int iRet = 0;
    int i = 0;
    for (i = 0; i < SIZE; i++)
    {
        //printf("i = [%d].\n", i);
    }
    int j = 1234;
    int* k;
    typeof (*k) in = 5;
    printf("%d.\n", in);
    
    
//    (void)DoTest();

    return OK;
}
