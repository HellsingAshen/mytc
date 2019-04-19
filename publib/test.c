#include "common.h"
int main()
{
    int             iRet                = -1;
    iRet = GetLocalByteOrder();
    printf("iRet = [%d].\n", iRet);
    return 0;
}
