#ifndef __COMMON_H
#define __COMMON_H

#define		ERR_CODE_INVALIDPARA        (-1)


int Str2Long(
    char    *pcIn,
    int     iInStrLen,
    long    *plOut
    );

int Long2Str(
    long    lInNum,
    int     iIn,
    char*   pcOut
    );



#endif
