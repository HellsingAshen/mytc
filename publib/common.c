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
    
/*
 * @desc : unsigned int to hex string 
 * @input: 
 *          n   
 * @output: 
 *          str 
 * @cautious:
 */          
static void
Uint2HexStr(char * str, uint32_t n) {
    int i;
    static char hex[16] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
    for (i=0;i<8;i++) {
        str[i] = hex[(n >> ((7-i) * 4))&0xf];
    }
    str[8] = '\0';
}

/*
 * @ desc   : judge local is big or little endian
 * @ input  : 
 * @ output : 
 * @ return :         
 *              0 --> little endian
 *              1 --> big endian
 * @ cautious:
 */          
int GetLocalByteOrder()
{
    uint32_t                uiInt               = 0x01;

    return ((0x01 == *(unsigned char*)&uiInt) ? 0 : 1);
}

void Test()
{
    printf("-----------------------------------------------\n");
    return;
}
