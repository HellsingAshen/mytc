#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>

#include "map.h"

int main()
{
    int                 iRet                = 0;
    int                 i                   = 0;
    int                 iValType            = -1;
    void*               pVal                = NULL;
    printf("hello c.\n");
    Map_S*              pstIntKey           = NULL;

    pstIntKey = MapInit(INT);
    assert(pstIntKey != NULL);

    /* add test */
    for (; i < 3; i++)
    {
        iRet = Add2Map(pstIntKey, INT, i, INT, i * 100);
        assert(0 == iRet);
    }

    iRet = ADD2IMAP(pstIntKey, 3, STRING, "three");
    assert(0 == iRet);

    iRet = ADD2IMAP(pstIntKey, 4, STRING, "four");
    assert(0 == iRet);

    iRet = ADD2IMAP(pstIntKey, 5, STRING, "five");
    assert(0 == iRet);

#if 0
    /* serach  test*/
    iRet = SearchMap(pstIntKey, INT, 1, &iValType, &pVal);
    printf("vt = [%d] vv = [%d].\n", iValType, pVal);
    assert((INT == iValType) && (100 == pVal));

    iRet = SearchMap(pstIntKey, INT, 3, &iValType, &pVal);
    printf("vt = [%d] vv = [%s].\n", iValType, pVal);
    assert((STRING == iValType) && (!strcmp(pVal, "three")));
#endif

#if 0
    /* del test */
    iRet = DelFromMap(pstIntKey, INT, 1);

    iRet = DelFromMap(pstIntKey, INT, 3);
#endif

     

    return 0;
}


