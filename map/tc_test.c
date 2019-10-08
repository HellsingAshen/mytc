#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>

#include "map.h"

int main()
{
    int                 iRet                = 0;
    void*               pVal                = NULL;
    printf("hello c.\n");
    Map_S*              pstIntKey           = NULL;
    Map_S*              pstStrKey           = NULL;
    int                 iType               = NULL;
    int                 i                   = 0;
    int                 iValType            = -1;


#if DESC("string-key")
    pstStrKey = MapInit(STRING);
    assert(pstStrKey != NULL);

    /* add key-string test */
    iRet = Add2Map(pstStrKey, STRING, "six", INT, (void*)6);
    assert(0 == iRet);

    iRet = Add2Map(pstStrKey, STRING, "seven", STRING, "7th");
    assert(0 == iRet);

    iRet = Add2Map(pstStrKey, STRING, "eigth", INT, (void*)8);
    assert(0 == iRet);

    iRet = Add2Map(pstStrKey, STRING, "nine", STRING, "9th");
    assert(0 == iRet);

    /* serach key-string test */
    iRet = SearchMap(pstStrKey, STRING, "six", &iType, &pVal);
    assert(OK == iRet && INT == iType && pVal == (void*)6);

    iRet = SearchMap(pstStrKey, STRING, "eigth", &iType, &pVal);
    assert(OK == iRet && INT == iType && pVal == (void*)8);

    iRet = SearchMap(pstStrKey, STRING, "seven", &iType, &pVal);
    assert(OK == iRet && STRING == iType && 0 == strcmp(pVal, "7th"));

    iRet = SearchMap(pstStrKey, STRING, "nine", &iType, &pVal);
    assert(OK == iRet && STRING == iType && 0 == strcmp(pVal, "9th"));

    /* delete key-string test */
    iRet = DelFromMap(pstStrKey, STRING, "six");
    assert(OK == iRet);

    iRet = DelFromMap(pstStrKey, STRING, "seven");
    assert(OK == iRet);

    iRet = DelFromMap(pstStrKey, STRING, "six1");
    assert(F_OK == iRet);

    iRet = SearchMap(pstStrKey, STRING, "six", &iType, &pVal);
    assert(F_OK == iRet);

    /* destruct key-string test */
    DestructMap(pstStrKey);
    assert(NULL == pstStrKey->stKeyRoot.rb_node->rb_left 
        &&  NULL == pstStrKey->stKeyRoot.rb_node->rb_right);
#endif

#if DESC("int-key") 

    pstIntKey = MapInit(INT);
    assert(pstIntKey != NULL);

    /* add test */
    for (; i < 3; i++)
    {
        iRet = Add2Map(pstIntKey, INT, (void*)(unsigned long long)i, INT, (void*)(unsigned long long)(i * 100));
        assert(0 == iRet);
    }

    iRet = ADD2IMAP(pstIntKey, (void*)3, STRING, "three");
    assert(0 == iRet);

    iRet = ADD2IMAP(pstIntKey, (void*)4, STRING, "four");
    assert(0 == iRet);

    iRet = ADD2IMAP(pstIntKey, (void*)5, STRING, "five");
    assert(0 == iRet);


    /* serach  test*/
    iRet = SearchMap(pstIntKey, INT, (void*)1, &iValType, &pVal);
    assert((INT == iValType) && ((void*)100 == pVal));

    iRet = SearchMap(pstIntKey, INT, (void*)3, &iValType, &pVal);
    assert((STRING == iValType) && (!strcmp(pVal, "three")));

    /* del test */
    iRet = DelFromMap(pstIntKey, INT, (void*)1);
    assert(OK == iRet);

    iRet = DelFromMap(pstIntKey, INT, (void*)11);
    assert(F_OK == iRet);

    iRet = SearchMap(pstIntKey, INT, (void*)1, &iValType, &pVal);
    assert(F_OK == iRet);

    DestructMap(pstIntKey);

#endif

    return 0;
}


