#ifndef _PUBLIC_H
#define _PUBLIC_H

#define     MAXSIZE                         (1024)
#define     OBS_MAX_SIZE                    (20)
#define     DICTREC_MAX_SIZE                (2000)

#ifndef     NULL    
#define     NULL    (void*)0
#endif

#define     OK                              (0)

#define     ERR                             (-1)
#define     ERR_INVALID_PARA                (-2)
#define     ERR_INPARA_NULL                 (-3)
#define     ERR_MALLOC_FAILED               (-4)

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

#define     MALLOC(s) \
    malloc(s)    


#endif
