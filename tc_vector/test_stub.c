#include <stdlib.h>
#include <stdio.h>
#include "vectorc.h"
#include "pub.h"

void EleDestruct(void* p)
{
    if (p)
    {
        FREE(p);
        p   = NULL;
    }

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
    
    Vct_SetIndex(pstVctor, 100, (void*)piNum);
    pstVctor->uiCount++;

    Vct_Push(pstVctor, piNumPush);
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

    /* test destruct */
    Vct_Destruct(&pstVctor);
   
    return 0;
}
