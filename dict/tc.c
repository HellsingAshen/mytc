#include <stdlib.h>
#include <stdio.h>
#include "dict.h"
#include "public.h"

DictTbl_S  stDT;


int main()
{
    const char*             pName           = "jinxing";
    const char*             pFirstName      = "shen";
    int                     iRet            = 0;
    memset(&stDT, 0, sizeof(DictTbl_S));
    stDT.iMask = 0xff;

    iRet = InsertDict(&stDT, pName, strlen(pName));
    RETURN_IF_FAILED(iRet);
    iRet = InsertDict(&stDT, pFirstName, strlen(pFirstName));
    RETURN_IF_FAILED(iRet);
    iRet = InsertDict(&stDT, "ab", strlen("ab"));
    RETURN_IF_FAILED(iRet);
    iRet = InsertDict(&stDT, "ab", strlen("ab"));
    RETURN_IF_FAILED(iRet);
    iRet = InsertDict(&stDT, "abc", strlen("abc"));
    RETURN_IF_FAILED(iRet);
    iRet = InsertDict(&stDT, "abcd", strlen("abcd"));
    RETURN_IF_FAILED(iRet);
    iRet = InsertDict(&stDT, "abd", strlen("abd"));
    RETURN_IF_FAILED(iRet);
    iRet = InsertDict(&stDT, "abe", strlen("abe"));
    RETURN_IF_FAILED(iRet);
    
    DispDictTbl(&stDT);
    printf("after del\n");

    iRet = RevmoveDict(&stDT, "ab");
    RETURN_IF_FAILED(iRet);
    iRet = RevmoveDict(&stDT, "abc");
    RETURN_IF_FAILED(iRet);
    iRet = RevmoveDict(&stDT, "abcd");
    RETURN_IF_FAILED(iRet);

    DispDictTbl(&stDT);




    printf("Hello World.\n");
    return 0;
}
