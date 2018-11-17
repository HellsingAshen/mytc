static char sqla_program_id[292] = 
{
 172,0,65,69,65,85,65,73,70,66,84,56,80,73,75,105,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,8,0,69,70,84,80,32,32,
 32,32,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,8,0,68,66,50,84,67,32,32,32,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0
};

#include "sqladef.h"

static struct sqla_runtime_info sqla_rtinfo = 
{{'S','Q','L','A','R','T','I','N'}, sizeof(wchar_t), 0, {' ',' ',' ',' '}};


static const short sqlIsLiteral   = SQL_IS_LITERAL;
static const short sqlIsInputHvar = SQL_IS_INPUT_HVAR;


#line 1 "db2tc.sqc"
/*--------------------------------------------------------------------
EXAMPLE of an embedded SQL C Program for DB2.
Connect to database test for this.
This APP takes one argument on the command line, a sailor's SID.  It
then finds the sailor SID's age out of the table INST105.SAILOR (in
database test) and reports it.  A dumb and not very interesting
APP, but it shows how things are done.
P. Godfrey NOV 2002
--------------------------------------------------------------------*/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlenv.h>
#include <sqlcodes.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
 
#define EXIT   0
#define NOEXIT 1
#define ERR    (-1)
#define OK     (0)
#define DESC(STR) (1)
#define MAX_NODE_CONFIG             (500)
#define MAX_SHMSIZE_APPCFG          (102400)
#define APPCFGRCD_MAX_COUNT         (317)
#define SP                          (0x20)
#define Tab                         (0x09)
#define NL                          (0x0a)
#define CR                          (0x0d)
#define MAX_NODE_CONFIG             (500)

int TrimAllSpace(char *s)
{
    int i, j;
    char    s1[4096];

    i = j = 0;
    while (s[i]) {
        if (s[i] != SP && s[i] != Tab && s[i] != NL && s[i] != CR)
            s1[j++] = s[i];
        i++; 
    }
    s1[j] = 0;
    strcpy(s, s1);
}

#if DESC("shm")
int GetShMemId(
        char* pcFile,
        int   iSize
        )
{
    if (!pcFile || iSize < 0) return ERR;

    key_t tKey= ftok(pcFile, 1);
    int iId = shmget(tKey, iSize, 0666);
    /* 
    printf("tKey = %d. id = [%d]\n", tKey, iId);
    */

    if (iId < 0) return ERR;

    return iId;
}

#endif
typedef struct  APP_CFG
{
    char pT_APP_ID[20];             /* APP_ID */
    char APP_DN[8];                 /* APP_CODE + NODE_CODE */
    char pT_APP_PATH[256];          /* HOME_PATH */
    char pT_APP_IP[33];             /* APP_IP*/
    char pT_APP_PORT[6];            /* APP_PORT*/

}CFG;

typedef struct  APP_NODE_CFG
{
    char AppNodeSrc[20];
    char AppNodeDes[20];
}AppNodeCfg;
 
/*--------------------------------------------------------------------
Include DB2's SQL error reporting facility.
--------------------------------------------------------------------*/
 

/*
EXEC SQL INCLUDE SQLCA ;
*/

/* SQL Communication Area - SQLCA - structures and constants */
#include "sqlca.h"
struct sqlca sqlca;


#line 90 "db2tc.sqc"

 
/*--------------------------------------------------------------------
Declare the SQL interface variables.
--------------------------------------------------------------------*/
 

/*
EXEC SQL BEGIN DECLARE SECTION ;
*/

#line 96 "db2tc.sqc"

    char   acPort[128+1];
    char   acUser[128 + 1];
    char   acPasswd[128 + 1];
    char   acDbName[128 + 1];

/*
EXEC SQL END DECLARE SECTION ;
*/

#line 101 "db2tc.sqc"

 
/*--------------------------------------------------------------------
Declare variables to be used in the following C program.
--------------------------------------------------------------------*/
 
char msg[1025];
int rc;
int errcount;
 
/*--------------------------------------------------------------------
This macro prints the message in the SQLCA if the return code is 0
and the SQLCODE is not 0.
--------------------------------------------------------------------*/
 
#define PRINT_MESSAGE()                                              \
  {                                                                  \
      if (rc == 0 && sqlca.sqlcode != 0)                             \
      {                                                              \
        sqlaintp(msg, 1024, 0, &sqlca);                              \
        printf("%s\n",msg);                                          \
      }                                                              \
  }
 
/*--------------------------------------------------------------------
This macro prints out all feilds in the SQLCA.
--------------------------------------------------------------------*/
 
#define DUMP_SQLCA()                                                 \
  {                                                                  \
    printf("**********  DUMP OF SQLCA  **********************\n");   \
    printf("SQLCAID: %s\n", sqlca.sqlcaid);                          \
    printf("SQLCABC: %d\n", sqlca.sqlcabc);                          \
    printf("SQLCODE: %d\n", sqlca.sqlcode);                          \
    printf("SQLERRML: %d\n", sqlca.sqlerrml);                        \
    printf("SQLERRD[0]: %d\n", sqlca.sqlerrd[0]);                    \
    printf("SQLERRD[1]: %d\n", sqlca.sqlerrd[1]);                    \
    printf("SQLERRD[2]: %d\n", sqlca.sqlerrd[2]);                    \
    printf("SQLERRD[3]: %d\n", sqlca.sqlerrd[3]);                    \
    printf("SQLERRD[4]: %d\n", sqlca.sqlerrd[4]);                    \
    printf("SQLERRD[5]: %d\n", sqlca.sqlerrd[5]);                    \
    printf("SQLWARN: %s\n", sqlca.sqlwarn);                          \
    printf("SQLSTATE: %s\n", sqlca.sqlstate);                        \
    printf("**********  END OF SQLCA DUMP  *******************\n");  \
  }
 
/*--------------------------------------------------------------------
This macro prints the message in the SQLCA if one exists.  If the
return code is not 0 or the SQLCODE is not expected, an error occurred
and must be recorded.
--------------------------------------------------------------------*/
 
#define CHECK_SQL(code,text_string,eExit)                            \
  {                                                                  \
    PRINT_MESSAGE();                                                 \
    if (rc != 0 || sqlca.sqlcode != code) {                          \
      printf("%s\n",text_string);                                    \
      printf("Expected code = %d\n",code);                           \
      if (rc == 0) {                                                 \
          DUMP_SQLCA();                                              \
      }                                                              \
      else printf("RC: %d\n",rc);                                    \
      errcount += 1;                                                 \
      if (eExit == EXIT) goto errorexit;                             \
    }                                                                \
  }
 
/*--------------------------------------------------------------------
The PROGRAM.
--------------------------------------------------------------------*/
/* def by table ftp_app_config */
typedef struct tagAppConfig_S
{
    char    acAppId     [20 + 1];
    char    acAppCode   [16 + 1];
    char    acAppName   [32 + 1];
    char    acNodeCode  [16 + 1];
    char    acNodeName  [32 + 1];
    char    acHomePath  [100 + 1];
    char    acAppIp     [64 + 1];
    int     iAppPort;
    char    acAppSystem [2 + 1];
    char    acAppState  [1 + 1];
} AppConfig_S;


int RefreshShmAppCfgRcd(AppConfig_S stAppCfg) 
{
    int             iRet            = 0;
    int             iShmAppCfgId    = 0;
    CFG*            pstAppCfg       = NULL;
    char            acAppDn[8]      = {0};
    int             iNodeCfgCount   = 0;
    void*           pShm            = 0;
    int             iIsRefreshRcd   = 0;
    char            acPromptStr[1024] = {0};


    iShmAppCfgId    = GetShMemId(getenv("SHMFILE"), MAX_SHMSIZE_APPCFG);
    /*
    printf("in stub,get TBL[FTP_APP_CONFIG] shmId = [%d].\n", iShmAppCfgId);
    */

    pShm         = shmat(iShmAppCfgId, 0, 0);
    pstAppCfg    =  (CFG*)pShm;
    if (!pstAppCfg)
    {
        printf("shmat error at [%d] line.\n", __LINE__ );
        iRet = ERR;
        goto error;
    }

    /* serach */
    while (pstAppCfg && *(char*)pstAppCfg != '\0')
    {
        iIsRefreshRcd   = 0;
        TrimAllSpace(stAppCfg.acAppCode);
        TrimAllSpace(stAppCfg.acNodeCode);
        memset(acAppDn, 0, sizeof(acAppDn));
        sprintf(acAppDn, "%s|%s|", stAppCfg.acAppCode, stAppCfg.acNodeCode);
        memset(acPromptStr, 0, sizeof(acPromptStr));

        if (!strcmp(stAppCfg.acAppId, pstAppCfg->pT_APP_ID) 
            &&!strcmp(acAppDn, pstAppCfg->APP_DN))
        {
            printf("get it .and start to reload record. cur pro AppDn = [%s]\n", acAppDn);
 
            if (strcmp(stAppCfg.acHomePath, pstAppCfg->pT_APP_PATH))
            {
                iIsRefreshRcd = 1;
                strcat(acPromptStr, pstAppCfg->pT_APP_PATH);
                strcat(acPromptStr, " -->");
                strcat(acPromptStr, stAppCfg.acHomePath);

                memset(pstAppCfg->pT_APP_PATH, 0, sizeof(pstAppCfg->pT_APP_PATH));
                memcpy(pstAppCfg->pT_APP_PATH, stAppCfg.acHomePath, strlen(stAppCfg.acHomePath));
            }

            if (strcmp(stAppCfg.acAppIp, pstAppCfg->pT_APP_IP))
            {
                iIsRefreshRcd = 2;
                strcat(acPromptStr, " ");
                strcat(acPromptStr, pstAppCfg->pT_APP_IP);
                strcat(acPromptStr, " -->");
                strcat(acPromptStr, stAppCfg.acAppIp);

                memset(pstAppCfg->pT_APP_IP, 0, sizeof(pstAppCfg->pT_APP_IP));
                memcpy(pstAppCfg->pT_APP_IP, stAppCfg.acAppIp, strlen(stAppCfg.acAppIp));

            }
           
            if (0 != stAppCfg.iAppPort - atoi(pstAppCfg->pT_APP_PORT))
            {
                iIsRefreshRcd = 4;
                strcat(acPromptStr, " ");
                strcat(acPromptStr, pstAppCfg->pT_APP_PORT);
                strcat(acPromptStr, " -->");

                memset(pstAppCfg->pT_APP_PORT, 0, sizeof(pstAppCfg->pT_APP_PORT));
                sprintf(pstAppCfg->pT_APP_PORT, "%d", stAppCfg.iAppPort);

                strcat(acPromptStr, pstAppCfg->pT_APP_PORT);
            
            }

            break;
        }
        iNodeCfgCount++;
        pstAppCfg++;
    }

    /* insert into shm new rcd */
    if (*(char*)pstAppCfg == '\0')
    {
        iIsRefreshRcd = 8;
        if (iNodeCfgCount >= APPCFGRCD_MAX_COUNT)
        {
            printf("shm ftp_app_config full. do not add any more!!");
            goto error;
        }

        memset(pstAppCfg, 0, sizeof(*pstAppCfg)); 
        memcpy(pstAppCfg->pT_APP_ID, stAppCfg.acAppId, sizeof(pstAppCfg->pT_APP_ID));
        memcpy(pstAppCfg->pT_APP_PATH, stAppCfg.acHomePath, sizeof(pstAppCfg->pT_APP_PATH));
        memcpy(pstAppCfg->pT_APP_IP, stAppCfg.acAppIp, sizeof(pstAppCfg->pT_APP_IP));
        
        TrimAllSpace(stAppCfg.acAppCode);
        TrimAllSpace(stAppCfg.acNodeCode);
        sprintf(pstAppCfg->APP_DN, "%s|%s|", stAppCfg.acAppCode, stAppCfg.acNodeCode);
        
        sprintf(pstAppCfg->pT_APP_PORT, "%d",stAppCfg.iAppPort);
        
    }

    if (iIsRefreshRcd)
    {
        printf("Load db Rcd in Shm, AppId = [%s]. NodeId = [%s] Chang [%s]\n", stAppCfg.acAppCode, stAppCfg.acNodeCode, acPromptStr);
    }

error: 
    if( shmdt(pShm) == -1)
    {
          return ERR;
    }

    return iRet;
}


/*
 * desc: update shm by table ftp_app_config
 * input : 
 * output: 
 *        ERR if failed and OK if suc
 */
int UpdateShmByTbl_FTP_APP_CONFIG()
{
    printf("in func UpdateShmByTbl_FTP_APP_CONFIG\n");
    
/*
EXEC SQL BEGIN DECLARE SECTION ;
*/

#line 319 "db2tc.sqc"

        char    acAppId     [20 + 1];
        char    acAppCode   [16 + 1];
        char    acAppName   [32 + 1];
        char    acNodeCode  [16 + 1];
        char    acNodeName  [32 + 1];
        char    acHomePath  [100 + 1];
        char    acAppIp     [64 + 1];
        sqlint32     iAppPort;
        char    acAppSystem [2 + 1];
        char    acAppState  [1 + 1];
    
/*
EXEC SQL END DECLARE SECTION ;
*/

#line 330 "db2tc.sqc"

    int             iRet            = ERR;
    AppConfig_S     stAppCfg        = {0};

    
/*
EXEC SQL DECLARE curAppCfg CURSOR FOR 
        SELECT 
             APP_ID, APP_CODE, APP_NAME, NODE_CODE, NODE_NAME, HOME_PATH, APP_IP, APP_PORT, APP_SYSTEM, APP_STATE 
        FROM FTP_APP_CONFIG;
*/

#line 337 "db2tc.sqc"



    CHECK_SQL(0, "The SELECT query failed.", EXIT);

    
/*
EXEC SQL OPEN curAppCfg;
*/

{
#line 342 "db2tc.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 342 "db2tc.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 342 "db2tc.sqc"
  sqlastop(0L);
}

#line 342 "db2tc.sqc"


    while (1) 
    {
        memset(acAppId    , 0, sizeof(acAppId     ));
        memset(acAppCode  , 0, sizeof(acAppCode   ));
        memset(acAppName  , 0, sizeof(acAppName   ));
        memset(acNodeCode , 0, sizeof(acNodeCode  ));
        memset(acNodeName , 0, sizeof(acNodeName  ));
        memset(acHomePath , 0, sizeof(acHomePath  ));
        memset(acAppIp    , 0, sizeof(acAppIp     ));
        iAppPort  = 0;
        memset(acAppSystem, 0, sizeof(acAppSystem ));
        memset(acAppState , 0, sizeof(acAppState  ));

        memset(&stAppCfg, 0, sizeof(stAppCfg));

        
/*
EXEC SQL FETCH curAppCfg INTO 
            :acAppId, 
            :acAppCode, 
            :acAppName, 
            :acNodeCode, 
            :acNodeName, 
            :acHomePath, 
            :acAppIp, 
            :iAppPort, 
            :acAppSystem, 
            :acAppState;
*/

{
#line 369 "db2tc.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 369 "db2tc.sqc"
  sqlaaloc(3,10,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[10];
#line 369 "db2tc.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 21;
#line 369 "db2tc.sqc"
      sql_setdlist[0].sqldata = (void*)acAppId;
#line 369 "db2tc.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 369 "db2tc.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 369 "db2tc.sqc"
      sql_setdlist[1].sqldata = (void*)acAppCode;
#line 369 "db2tc.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 369 "db2tc.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 33;
#line 369 "db2tc.sqc"
      sql_setdlist[2].sqldata = (void*)acAppName;
#line 369 "db2tc.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 369 "db2tc.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 17;
#line 369 "db2tc.sqc"
      sql_setdlist[3].sqldata = (void*)acNodeCode;
#line 369 "db2tc.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 369 "db2tc.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 33;
#line 369 "db2tc.sqc"
      sql_setdlist[4].sqldata = (void*)acNodeName;
#line 369 "db2tc.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 369 "db2tc.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 101;
#line 369 "db2tc.sqc"
      sql_setdlist[5].sqldata = (void*)acHomePath;
#line 369 "db2tc.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 369 "db2tc.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 65;
#line 369 "db2tc.sqc"
      sql_setdlist[6].sqldata = (void*)acAppIp;
#line 369 "db2tc.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 369 "db2tc.sqc"
      sql_setdlist[7].sqltype = 496; sql_setdlist[7].sqllen = 4;
#line 369 "db2tc.sqc"
      sql_setdlist[7].sqldata = (void*)&iAppPort;
#line 369 "db2tc.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 369 "db2tc.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 3;
#line 369 "db2tc.sqc"
      sql_setdlist[8].sqldata = (void*)acAppSystem;
#line 369 "db2tc.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 369 "db2tc.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 2;
#line 369 "db2tc.sqc"
      sql_setdlist[9].sqldata = (void*)acAppState;
#line 369 "db2tc.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 369 "db2tc.sqc"
      sqlasetdata(3,0,10,sql_setdlist,0L,0L);
    }
#line 369 "db2tc.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 369 "db2tc.sqc"
  sqlastop(0L);
}

#line 369 "db2tc.sqc"


        if (SQLCODE != 0) break;

        /* get shm record */
        memcpy(stAppCfg.acAppId    , acAppId    , sizeof(acAppId     ));
        memcpy(stAppCfg.acAppCode  , acAppCode  , sizeof(acAppCode   ));
        memcpy(stAppCfg.acAppName  , acAppName  , sizeof(acAppName   ));
        memcpy(stAppCfg.acNodeCode , acNodeCode , sizeof(acNodeCode  ));
        memcpy(stAppCfg.acNodeName , acNodeName , sizeof(acNodeName  ));
        memcpy(stAppCfg.acHomePath , acHomePath , sizeof(acHomePath  ));
        memcpy(stAppCfg.acAppIp    , acAppIp    , sizeof(acAppIp     ));
        memcpy(stAppCfg.acAppSystem, acAppSystem, sizeof(acAppSystem ));
        memcpy(stAppCfg.acAppState , acAppState , sizeof(acAppState  ));
        stAppCfg.iAppPort = iAppPort;

        iRet =  RefreshShmAppCfgRcd(stAppCfg); 
        if (iRet) goto errorexit;
        
        
    }

errorexit:
    if (100 != SQLCODE) printf("fetch error .\n");
    
/*
EXEC SQL CLOSE curAppCfg;
*/

{
#line 393 "db2tc.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 393 "db2tc.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 393 "db2tc.sqc"
  sqlastop(0L);
}

#line 393 "db2tc.sqc"

    return OK;
}
/*
 * @desc : refresh shm; if rcd is not in , add it in shm 
 */
int RefreshShmNodecfgRcd(AppNodeCfg stNodeCfg)
{
    int             iRet            = 0;
    int             iShmNodeCfgId   = 0;
    AppNodeCfg*     pstAppNodeCfg   = NULL;
    char            acAppDn[8]      = {0};
    int             iNodeCfgCount   = 0;
    void*           pShm            = 0;
    char            acPromptStr[1024] = {0};

    iShmNodeCfgId    = GetShMemId(getenv("SHMFILE_NODE"), sizeof(AppNodeCfg) * MAX_NODE_CONFIG);

    pShm             = shmat(iShmNodeCfgId, 0, 0);
    pstAppNodeCfg    =  (AppNodeCfg*)pShm;
    if (!pstAppNodeCfg)
    {
        printf("shmat error at [%d] line.\n", __LINE__ );
        iRet = ERR;
        goto error;
    }

    /* serach */
    while (pstAppNodeCfg && *(char*)pstAppNodeCfg != '\0')
    {

        if (!strcmp(stNodeCfg.AppNodeSrc, pstAppNodeCfg->AppNodeSrc) 
                && !strcmp(stNodeCfg.AppNodeDes, pstAppNodeCfg->AppNodeDes))
        {
            printf("get rcd  in shm [%s] -->[%s] . do not need load it to shm .\n", stNodeCfg.AppNodeSrc, stNodeCfg.AppNodeDes);
            break;
        }
        iNodeCfgCount++;
        pstAppNodeCfg++;
    }

    /* insert into shm new rcd */
    if (*(char*)pstAppNodeCfg == '\0')
    {
        if (iNodeCfgCount >= MAX_NODE_CONFIG)
        {
            printf("shm ftp_app_node_cfg full. do not add any more!!");
            goto error;
        }

        /* memory has been already malloced  */
        memset(pstAppNodeCfg, 0, sizeof(*pstAppNodeCfg)); 
        memcpy(pstAppNodeCfg->AppNodeSrc, stNodeCfg.AppNodeSrc, sizeof(stNodeCfg.AppNodeSrc));
        memcpy(pstAppNodeCfg->AppNodeDes, stNodeCfg.AppNodeDes, sizeof(stNodeCfg.AppNodeDes));
        printf("Load tbl [ftp_app_config_cfg] Rcd in Shm, NewRcd is [%s] --> [%s]\n", stNodeCfg.AppNodeSrc, stNodeCfg.AppNodeDes);
        
    }
error:
    if( shmdt(pShm) == -1)
    {
       return ERR;
    }

    

    return iRet;
}


/* only support add */
int UpdateShmByTbl_FTP_APP_NODE_CFG()
{
    printf("in func UpdateShmByTbl_FTP_APP_CONFIG\n");
    
/*
EXEC SQL BEGIN DECLARE SECTION ;
*/

#line 466 "db2tc.sqc"

        char    acAppSrc    [16 + 1];
        char    acNodeSrc   [16 + 1];
        char    acAppDst    [16 + 1];
        char    acNodeDst   [16 + 1];
    
/*
EXEC SQL END DECLARE SECTION ;
*/

#line 471 "db2tc.sqc"


    int             iRet            = ERR;
    AppNodeCfg     stNodeCfg        = {0};

    
/*
EXEC SQL DECLARE curNodeCfg CURSOR FOR 
        SELECT 
            APP_SRC, NODE_SRC,  APP_DES, NODE_DES 
        FROM ftp_app_node_cfg;
*/

#line 479 "db2tc.sqc"



    CHECK_SQL(0, "The SELECT query failed.", EXIT);

    
/*
EXEC SQL OPEN curNodeCfg;
*/

{
#line 484 "db2tc.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 484 "db2tc.sqc"
  sqlacall((unsigned short)26,2,0,0,0L);
#line 484 "db2tc.sqc"
  sqlastop(0L);
}

#line 484 "db2tc.sqc"


    while (1) 
    {
        memset(acAppSrc   , 0, sizeof(acAppSrc   ));
        memset(acNodeSrc  , 0, sizeof(acNodeSrc  ));
        memset(acAppDst   , 0, sizeof(acAppDst   ));
        memset(acNodeDst  , 0, sizeof(acNodeDst  ));
    
        memset(&stNodeCfg, 0, sizeof(stNodeCfg));

        
/*
EXEC SQL FETCH curNodeCfg INTO 
            :acAppSrc, 
            :acNodeSrc, 
            :acAppDst, 
            :acNodeDst;
*/

{
#line 499 "db2tc.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 499 "db2tc.sqc"
  sqlaaloc(3,4,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 499 "db2tc.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 499 "db2tc.sqc"
      sql_setdlist[0].sqldata = (void*)acAppSrc;
#line 499 "db2tc.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 499 "db2tc.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 499 "db2tc.sqc"
      sql_setdlist[1].sqldata = (void*)acNodeSrc;
#line 499 "db2tc.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 499 "db2tc.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 17;
#line 499 "db2tc.sqc"
      sql_setdlist[2].sqldata = (void*)acAppDst;
#line 499 "db2tc.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 499 "db2tc.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 17;
#line 499 "db2tc.sqc"
      sql_setdlist[3].sqldata = (void*)acNodeDst;
#line 499 "db2tc.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 499 "db2tc.sqc"
      sqlasetdata(3,0,4,sql_setdlist,0L,0L);
    }
#line 499 "db2tc.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 499 "db2tc.sqc"
  sqlastop(0L);
}

#line 499 "db2tc.sqc"


        if (SQLCODE != 0) break;

        /* get shm record */
        TrimAllSpace(acAppSrc);
        TrimAllSpace(acNodeSrc);
        sprintf(stNodeCfg.AppNodeSrc, "%s|%s|", (acAppSrc), (acNodeSrc));
        sprintf(stNodeCfg.AppNodeDes, "%s|%s|", (acAppDst), (acNodeDst));

        iRet =  RefreshShmNodecfgRcd(stNodeCfg); 
        if (iRet) goto errorexit;
        
    }

errorexit:
    if (100 != SQLCODE) printf("fetch error .\n");
    
/*
EXEC SQL CLOSE curAppCfg;
*/

{
#line 516 "db2tc.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 516 "db2tc.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 516 "db2tc.sqc"
  sqlastop(0L);
}

#line 516 "db2tc.sqc"

    return  iRet;

}

/*  ftp_app_config -- only support add and modify. do not support del operation */
int main (int argc, char *argv[])
{
    
/*
EXEC SQL BEGIN DECLARE SECTION ;
*/

#line 524 "db2tc.sqc"

        char   acPort[128+1];
        char   acUser[128 + 1];
        char   acPasswd[128 + 1];
        char   acDbName[128 + 1];
    
/*
EXEC SQL END DECLARE SECTION ;
*/

#line 529 "db2tc.sqc"


    int             iRet                = ERR; 

    memset(&acPort[0], 0, sizeof(acPort));
    memset(&acPasswd[0], 0, sizeof(acPasswd));
    memset(&acUser[0], 0, sizeof(acUser));
    memset(&acDbName[0], 0, sizeof(acDbName));


#if 0
    memcpy(&acPasswd[0], "eftp", 4);
    memcpy(&acUser[0], "eftp", 4);
    memcpy(&acDbName[0], "eftp", 4);
#endif

    if (getenv("DB2_DATEBASE") != NULL)
    {
        memset(&acDbName[0], 0, sizeof(acDbName));
        strcpy(&acDbName[0], getenv("DB2_DATEBASE"));
    }

    if (getenv("DB2_USER") != NULL)
    {
        memset(&acUser[0], 0, sizeof(acUser));
        strcpy(&acUser[0], getenv("DB2_USER"));
    }

    if (getenv("DB2_PASSWORD") != NULL)
    {
        memset(&acPasswd[0], 0, sizeof(acPasswd));
        strcpy(&acPasswd[0], getenv("DB2_PASSWORD"));
    }



    /** connect to db **/
    
/*
EXEC SQL CONNECT TO :acDbName USER :acUser USING :acPasswd;
*/

{
#line 566 "db2tc.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 566 "db2tc.sqc"
  sqlaaloc(2,3,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 566 "db2tc.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 129;
#line 566 "db2tc.sqc"
      sql_setdlist[0].sqldata = (void*)acDbName;
#line 566 "db2tc.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 566 "db2tc.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 129;
#line 566 "db2tc.sqc"
      sql_setdlist[1].sqldata = (void*)acUser;
#line 566 "db2tc.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 566 "db2tc.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 129;
#line 566 "db2tc.sqc"
      sql_setdlist[2].sqldata = (void*)acPasswd;
#line 566 "db2tc.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 566 "db2tc.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 566 "db2tc.sqc"
  sqlacall((unsigned short)29,5,2,0,0L);
#line 566 "db2tc.sqc"
  sqlastop(0L);
}

#line 566 "db2tc.sqc"

    CHECK_SQL(0, "Connect failed", EXIT);
 
    
/*
EXEC SQL SELECT CFG_VALUE into :acPort
        FROM FTP_SYS_CONFIG WHERE CFG_CODE = 'SYS_PORT';
*/

{
#line 570 "db2tc.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 570 "db2tc.sqc"
  sqlaaloc(3,1,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 570 "db2tc.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 129;
#line 570 "db2tc.sqc"
      sql_setdlist[0].sqldata = (void*)acPort;
#line 570 "db2tc.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 570 "db2tc.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 570 "db2tc.sqc"
  sqlacall((unsigned short)24,3,0,3,0L);
#line 570 "db2tc.sqc"
  sqlastop(0L);
}

#line 570 "db2tc.sqc"

 
    CHECK_SQL(0, "The SELECT query failed.", EXIT);
 
    printf("Port is [%s]\n", acPort);
    printf("Executed Successfuly\n") ;


    iRet = UpdateShmByTbl_FTP_APP_CONFIG();
    if (iRet) 
    {
        printf("Update shm by table ftp_app_config failed. exit.\n") ;
        goto errorexit;
    }
    
    iRet = UpdateShmByTbl_FTP_APP_NODE_CFG();
    if (iRet) 
    {
        printf("Update shm by table ftp_app_node_cfg failed. exit.\n") ;
        goto errorexit;
    }

 
errorexit:
    
/*
EXEC SQL CONNECT RESET;
*/

{
#line 594 "db2tc.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 594 "db2tc.sqc"
  sqlacall((unsigned short)29,3,0,0,0L);
#line 594 "db2tc.sqc"
  sqlastop(0L);
}

#line 594 "db2tc.sqc"


    return 0;
}
