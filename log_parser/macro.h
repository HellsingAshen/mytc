#define ERR        (-1)
#define OK        (0)
#define ST_TYPE_FTP_APP_CONFIG      (1)
#define ST_TYPE_FTP_APP_NODE_CFG    (2)
#define MAX_NODE_CONFIG             (500)
#define MAX_SHMSIZE_APPCFG          (102400)
#define MAX_PATH_LEN                (500)

#define CHAR_ARR_LEN_MAX            (1024)

#define MAX_PATTON_LEN              (256)

#define SP                          (' ')

#define MAX_BUFF_LEN_128            (128)


#define BREAK_IF_ERR(ret) \
    do { \
        if (0 != ret) {break;} \
    } while (0);

#define GOTO_IF_COND(COND, GOTO) \
    do { \
       if (COND) {goto GOTO;} \
    } while (0);
#define RETURN_IF_ERR(r) \
    do { \
        if(r)   {return r;} \
    } while (0);

#define RETURN_IF_STDERR(r) \
    do { \
        if(r)   {return r;} \
    } while (0);

#define USAGE \
    "USAGE:\n\t\t-d dir \n" \
    "        \t-f file \n" \

#define MALLOC(s) malloc(s)
    
#define FREE(p) \
    do { \
        free(p); \
        p = NULL; \
    } while (0);

#define STRCMPB(p, s)  strncmp(p, s, strlen(s))
