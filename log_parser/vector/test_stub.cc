#include <stdlib.h>
#include <stdio.h>
#include "vectorc.h"
#include "pub.h"
#include <assert.h>

void EleDestruct(void* p)
{
    if (p) FREE(p);
    return;

}
void PrtVct(Vector_S* pstVct)
{
    assert(NULL != pstVct);
    int                     i                   = 0;
    for (; i< pstVct->uiCapacity && pstVct->ppData[i]; i++)
    {
        printf("vct[%d] = [%d]\n, ", i, *(int*)(pstVct->ppData[i]));
    }
    printf("***********total count = [%d] cap = [%d]***********\n", pstVct->uiCount, pstVct->uiCapacity);

    return;
}

int main (int argc, char** argv)
{

    Vector_S*               pstVctor            = NULL;
    int*                    piNum               = NULL;
    void*                   piNumPush           = NULL;
    int                     iNum                = 1111;
    int                     iNumPush            = 2222;

    int                     aiArr[10]           = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    int                     i;
    void*                   pData               = NULL;

    int                     iCount              = 0;
    piNum       = &iNum;
    piNumPush   = &iNumPush; 
    
    //Vct_Construct(&pstVctor, EleDestruct);
    /* test construct */
    Vct_Construct(&pstVctor, NULL);

    /* test push */
    for (i = 0; i < 10; i++)
    { 
        Vct_Pushback(pstVctor, &aiArr[i]);
    }    
    PrtVct(pstVctor);
    

#if 0
    for (i = 0; i < 10; i++)
    { 
        Vct_Pushback(pstVctor, &aiArr[i]);
    }    

    Vct_Push(pstVctor, piNumPush);
    PrtVct(pstVctor);

    for (i = 0; i < 10; i++)
    { 
        Vct_Pushback(pstVctor, &aiArr[i]);
    }    

    for (i = 0; i < 10; i++)
    { 
        Vct_Pushback(pstVctor, &aiArr[i]);
    }    
    PrtVct(pstVctor);
#endif


    /* test pop */
    iCount = pstVctor->uiCount;
    for (i = 0; i < iCount; i++)
    {
        pData   = Vct_Popback(pstVctor);
        if (!pData)
        {
            printf("pData = NULL. i = [%d]\n", i);
        }
        else
        {
            printf("pData[%d] = [%d].\n", pstVctor->uiCount, *(int*)pData);
        }

    }

    printf("-------------------------------------------------\n");
    PrtVct(pstVctor);

    /* test push */
    

printf("---------------------------------\n");

    /* test destruct */
    Vct_Destruct(&pstVctor);
   
    return 0;
}
