#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> 
#include <fcntl.h> 
#include <sys/types.h>

#define INTCMP(i1, i2)              (((unsigned long long )i1 > (unsigned long long)i2) ?  1 : (((unsigned long long)i1 < (unsigned long long)i2 ) ? -1 : 0))
#define CMPVALBYTYPE(t, n, v2)      ((INT == t) ? (INTCMP((unsigned int)ivkey(n), (unsigned int)v2)) : (strcmp(pcvkey(n), (char*)v2)))

int f(int* p)
{
    return 0;
}

static int* f1()
{
    static int j = 2;
    return &j;
}

int  main()
{
    *(f1()) = 3;
    

#if 0
    int fp = open("./aaaa", O_WRONLY | O_APPEND); 

    int  ifd = 10;
    char* pc  = "shenjinxing";

    dup2(fp, ifd);
    //ifd = dup(fp);
    
    //close(fp);
    write(ifd, pc, strlen(pc));
    close(ifd);
#endif

    return 0;
}

#if 0
int main1()
{
    typedef union tagType_U
    {
        int i;
        double d;
    }Type_U;
    
    Type_U unUn = {1};
    printf("union           len = [%d]\n", sizeof(Type_U));
    printf("unionval        len = [%d]\n", sizeof(unUn));
    
    printf("short           len = [%d]\n", sizeof(short));
    printf("int             len = [%d]\n", sizeof(int));
    printf("unsigned int    len = [%d]\n", sizeof(unsigned int));
    printf("long            len = [%d]\n", sizeof(long));
    printf("long long       len = [%d]\n", sizeof(long long ));
    printf("void            len = [%d]\n", sizeof(void));
    printf("void*           len = [%d]\n", sizeof(void*));
    printf("float           len = [%d]\n", sizeof(float));
    printf("double          len = [%d]\n", sizeof(double));
#if 0
    char* p = "123";
    char* p2 = p;
    int iRet = 0;

    iRet = INTCMP(p2, 2);
    //iRet = INTCMP((unsigned long long)p2, (unsigned long long)2);
    //iRet = INTCMP((unsigned long long)p2, 2);
    
    printf("%d ", iRet);
    
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
#endif
