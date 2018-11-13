#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <sys/types.h>
#include <errno.h> 
#include <fcntl.h>  
#define Prt printf

void Hex2Str( char *sSrc,  char *sDest, int nSrcLen )
{
    int  i;
    char szTmp[3];

    for( i = 0; i < nSrcLen; i++ )
    {
        sprintf( szTmp, "%02X", (unsigned char) sSrc[i] );
        memcpy( &sDest[i * 2], szTmp, 2 );
    }
    return ;
}

void Str2Hex( char *sSrc, char *sDest, int nSrcLen)
{
    int i, nHighBits, nLowBits;

    for( i = 0; i < nSrcLen; i += 2 )
    {
        nHighBits = sSrc[i];
        nLowBits  = sSrc[i + 1];

        if( nHighBits > 0x39 )
            nHighBits -= 0x37;
        else
            nHighBits -= 0x30;

        if( i == nSrcLen - 1 )
            nLowBits = 0;
        else if( nLowBits > 0x39 )
            nLowBits -= 0x37;
        else
            nLowBits -= 0x30;

        sDest[i / 2] = (nHighBits << 4) | (nLowBits & 0x0f);
    }
    return ;
}


int main(void)
{
    int iRet    = 0;
    char            acSrc[512]              = {0};
    char            acDes[1024]             = {0};

    Hex2Str("123", acDes, 3);
    Prt("acDes = [%s]", acDes);

    memset(acDes, 0x00, sizeof(acDes));
    Hex2Str("abc", acDes, strlen("123"));
    Prt("acDes = [%s]", acDes);

    

    
    
	
    return 0;
}


