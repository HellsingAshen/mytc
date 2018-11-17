#include "common.h"

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

