#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <sys/types.h>

#define INTCMP(i1, i2)              (((unsigned long long )i1 > (unsigned long long)i2) ?  1 : (((unsigned long long)i1 < (unsigned long long)i2 ) ? -1 : 0))
#define CMPVALBYTYPE(t, n, v2)      ((INT == t) ? (INTCMP((unsigned int)ivkey(n), (unsigned int)v2)) : (strcmp(pcvkey(n), (char*)v2)))

int f(int* p)
{
    return 0;
}

int main()
{
    char* p = "123";
    char* p2 = p;
    int iRet = 0;

    iRet = INTCMP(p2, 2);
    //iRet = INTCMP((unsigned long long)p2, (unsigned long long)2);
    //iRet = INTCMP((unsigned long long)p2, 2);
    
    printf("%d ", iRet);
    
#if 0
    typedef union tagValue_U
    {
        int    i;
        void*  pv;
    }Value_U;
    Value_U u = {1};
    printf("%d %d %d",  u, u.i, u.pv );
#endif

    return 0;
}


