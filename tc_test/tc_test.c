#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#define global
global int g_iTag = 0;

/* @ desc : SwapC
 * @ in :
 * @ out :
 * @ cautious: not free malloc 
 */
int* SwapC(int m, int n, int aiArr[], int iNum)
{
    int* pi = malloc(sizeof(iNum));
    memset(pi, 0x00, sizeof(int) * iNum);
    *(pi + m) = aiArr[n];
    memcpy(pi + 1, &aiArr[m], (iNum - 1) * sizeof(int));
    
    return pi;
}

void PrtArr(int aiArr[], int iNum)
{
    int i = 0;
    while (i < iNum)
    {
        printf("%d ", aiArr[i]);
        i++;
    }
    return;
}

int Swap(int* i, int* j)
{
    int t;
    if (!i || !j) return -1;
    t = *i;
    *i = *j;
    *j = t;
    return 0;
}

int* DupArr(int aiArr[], int iNum)
{
    int* piArr = malloc(sizeof(int) * iNum);
    memcpy(piArr, aiArr, sizeof(int) * iNum);
    return piArr;
}

/*
 * @ desc : remove arr[i]
 * @ in :
 * @ out :
 * @ cautious: not free arr
 */
int* RemoveArrEle(int aiArr[], int iNum, int index)
{
    int             i               = 0;
    int             j               = 0;
    int* piRetArr = malloc(sizeof(int) * (iNum - 1));
    while (i < iNum)
    {
        if (i == index)
        {
            i++;
            continue;
        }
        *(piRetArr + j) = aiArr[i];
        i++;
        j++;
    }
    return piRetArr;
}


void PrtNBlank(int m)
{
    int j = 0; 
    for (j = 0; j < m; j++)
    {
        printf("  ");
    }
    return;
}


/*
 * @ desc : Fully arranged
 * @ in   : fully arranged array 
 *          iDeep  for PrtNBlack, if call iDeep set as 0
 * @ out  :
 * @ cautious :
 *
 */
void Tc_FA(int aiArr[], int iNum, int iDeep)
{
    int             *piRet          = NULL;
    int             *piRemoveArr    = NULL;
    int             i               = 0;
    if (1 == iNum) printf("%d \n", aiArr[iNum -1]);
    else if (2 == iNum) 
    {
        PrtNBlank(iDeep);
        PrtArr(aiArr, iNum);
        printf("\n");
        piRet = DupArr(aiArr, iNum);

        Swap(piRet, piRet + 1);

        PrtNBlank(iDeep);
        PrtArr(piRet, iNum);
        printf("\n");
        free(piRet); piRet = NULL;
    }
    else
    {
        for (i = 0; i < iNum; i++)
        {
            PrtNBlank(iDeep);
            printf("%d ", aiArr[i]);
            piRemoveArr = RemoveArrEle(aiArr, iNum, i);
            printf("\n");
            Tc_FA(piRemoveArr, iNum - 1, iDeep + 1);
            printf("\n");
            free(piRemoveArr); piRemoveArr = NULL;
        }
    }
    
    return;

}

long Power(int n)
{
    if (n < 0) return -1;
    long lRet = 1;
    int i = 0;
    while (i < n)
    {
        lRet *=  10; 
        i++;
    }
    return lRet;
}
void PrtFromTo(int from, int to)
{
    int             i;
    for (i = from; i <= to; i++) printf( "%d ", i);
    printf("\n");
    return;
}

/*
 * @ desc   : Use the recursive method to find the N-bit integer from 1 to the largest.
 * @ in     : N
 * @ out    : 
 *
 */
void Tc_GetNBit(
    int     n)
{
    if (n < 0) return;
    if (1 == n ) 
    {
        PrtFromTo(1, 9);
    }
    else
    {
        Tc_GetNBit(n - 1);
        PrtFromTo(Power(n-1), Power(n) -1);
    }  
    return;
}

/* @ desc   : put m apples into n plates 
 * @ in     : M  -- apples
 *            N  -- plates
 * @ out    : 
 *            methods
 * @ cautious: 
 *
 * */
int     Tc_GetPutMethods(
    int m,
    int n)
{
    int         iRet            = 0;
    if (n <= 0 || m < 0)  return -1;
    if (1 == n || 0 == m)
    {
        return 1;
    }
    else
    {
        if (n > m)
        {
            iRet    = Tc_GetPutMethods(m, m);
        }
        else
        {
            /**
             *  plate[n] = null  and  plate[n] != null
             */
            iRet    = Tc_GetPutMethods(m, n - 1) + Tc_GetPutMethods(m - n, n);
        }
    }
    return iRet;
}

void Tc_HT_Move(char s, char d)
{
    printf("Move [%c] to [%c].\n",  s, d);
    return;
}



/*
 * desc: Hanno Tower for practising recursion
 * in  :
 *       n -- tower level 
 *       s -- src 
 *       d -- dest
 *       m -- mid
 * out : 
 *        print move step 
 * cautious:
 */
void Tc_HT(
    int iLevel,
    char cSrc,
    char cDest,
    char cMid)
{
    if (1 == iLevel)
    {
        Tc_HT_Move(cSrc, cDest);
    }
    else
    {
        (void)Tc_HT(iLevel - 1, cSrc, cMid, cDest);
        (void)Tc_HT_Move(cSrc, cDest);
        (void)Tc_HT(iLevel - 1, cMid, cDest, cSrc);
    }
    return;

}

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
#define DESC(str) 1

/*
 * @ desc: string reverse printing
 * @ in  : printed char
 * @ out : 
 * cautious: 
 */
void Tc_ReversePrint(char* sSrc, int iLen)
{
    if (!sSrc || 0 == iLen) return;
    if (1 == iLen)
    {
        printf(" %c ", sSrc[iLen - 1]); 
    }
    else
    {
        printf(" %c ", sSrc[iLen - 1]); 
        iLen--;
        Tc_ReversePrint(sSrc, iLen);
    }
    return;
}


/*
 * @ desc: main
 *         for practicing recursion
 * @ input: 
 * @ output:    
 * @ cautious:	
 */

int main(void)
{
#if 0
    int             aiArr[4] = {1, 2, 3, 4};
    Tc_FA(aiArr, 4, 0);
#endif
#if 1
    int             aiArr1[3] = {1, 2, 3};
    Tc_FA(aiArr1, 3, 0);
#endif

#if 0
    Tc_GetNBit(1);
    printf("##########################\n");
    Tc_GetNBit(2);
    printf("##########################\n");
    Tc_GetNBit(3);
    printf("##########################\n");
    Tc_GetNBit(4);
    printf("##########################\n");

#endif
#if 0
    int iDeep = 4;
    (void)Tc_Recursive(iDeep);
    printf("factorial(%d))= [%d].\n", iDeep, Tc_Factorial(iDeep));
#endif
#if 0
    Tc_HT(1, 97, 99, 98);;
    printf("-------------------------\n");
    Tc_HT(2, 97, 99, 98);;
    printf("-------------------------\n");
    Tc_HT(3, 97, 99, 98);;
    printf("-------------------------\n");
    Tc_HT(4, 97, 99, 98);;
#endif

#if 0
    Tc_ReversePrint("shen", 4);
#endif
#if 0
    printf("methods = [%d].\n", Tc_GetPutMethods(7, 3));
    printf("methods = [%d].\n", Tc_GetPutMethods(2, 3));

#endif

    return 0;
}


