
#define     RETURN_IF_FAILED(iRet) \
    do \
    { \
        if (iRet) return iRet; \
    } while (0);


#define     RETURN_IF_NULL(p, iRet) \
    if (!p) return iRet;

#define     FREE(p) \
    do \
    { \
        if (p) free(p); p = NULL; \
    } while (0);


#define     BREAK_IF_FAILED(iRet) \
    if (iRet) {break;}
