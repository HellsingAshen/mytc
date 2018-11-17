#include "common.h"
/*
 * @ desc: string to int 
 * @ input : 
 *          pcIn
 *          iInStrLen
 * @ output: 
 *          plOut
 */ 	    
int Str2Long(
	char    *pcIn, 
    int     iInStrLen,
    long    *plOut)
{
    int             i           = 0;
    long            lOut        = 0;
    if (!pcIn || (0 > iInStrLen) || (8 < iInStrLen))
    {
        return ERR_CODE_INVALIDPARA;
    }
    
    while (i < iInStrLen)
    {
        lOut    += (*(pcIn + i) << ((iInStrLen - i - 1) * 8));
        i++;
    }

    *plOut  = lOut;
    
    return 0;
}

/*
 * @desc : long to string
 * @input: 
 *          lInNum
 *          iIn
 * @output: 
 *          pcOut
 * @cautious:
 */          
int Long2Str(
    long    lInNum,
    int     iIn,
    char*   pcOut
    )
{
    int             iRet            = 0;
    int             i               = 0;

    memset(pcOut, 0x00, iIn);
    
    while (i < iIn)
    {
        
        *(pcOut + i) = (lInNum >> ((iIn - i - 1)  * 8)) & 0xff;
        i++;
    }

    return  iRet;

}
    


void Test()
{
    printf("-----------------------------------------------\n");
    return;
}
