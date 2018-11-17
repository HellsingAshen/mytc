#include <sys/stat.h> 
#include "common.h"


#define		DESC(str)       	(1)
#define		FILE_PATH_LEN		(128)
#define		FILE_NAME_LEN		(128)
#define     E_LOG_PATH          ("LOG_PATH")
#define     LOG_SIZE_DEFAULT    (10 * 1024 * 1024)
#define     E_LOG_SIZE          ("LOG_SIZE")

#define     E_LOG_LEVEL         ("LOG_LEVEL")

#define     DATE_LEN_MAX        (9)
#define     DATETIME_LEN_MAX        (8 + 6 + 3 + 1)

#define     LOG_SWITCH_SIZE    (0)
#define     LOG_SWITCH_DATE    (1)
#if  DESC(" error code ")
typedef enum tagErrorCode_E
{
    
    ERR_CODE_INVALID_PARA = -1,
    ERR_CODE_OPENFILE_FAILED,

}ErrorCode_E;

#endif
#if  DESC("date type format")
typedef enum tagDateType_E
{
    DATE_TYPE_YYMMDD = 0,
    DATE_TYPE_YYYYMMDDHHMMSSBBB,
    DATE_TYPE_YYYYMMDDHHMMSS,
    DATE_TYPE_YYYYMMDD_HHMMSS_BBB,

    DATE_TYPE_BULT

} DateType_E;
#endif
#if  DESC(" log level  ")
typedef enum tagLogLevel_E
{
    LOG_LEVEL_DEBUG = 0,
    LOG_LEVEL_INFO  = 1,
    LOG_LEVEL_WARNING = 2,
    LOG_LEVEL_ERR   = 3,
    LOG_LEVEL_OFF   = 4

} LogLevel_E;
#endif
#if  DESC(" error code ")
#define     OK       (0)
#define     ERR      (-1)
#endif

/* @ desc   : get sys time
 * @ input  : 
 *              int    iWantedFormat
 * @ output :
 *              char*   pcDateTime
 * @ cautious:
  * %a���ڼ��ļ�д��ʽ
    %A���ڼ���ȫ��
    %b�·ݵļ�д��ʽ
    %B�·ݵ�ȫ��
    %c���ں�ʱ��
    %d�·��е�����,0-31
    %HСʱ,00-23
    %I12����Сʱ�ӵ�,01-12
    %j����е�����,001-366
    %m����е��·�,01-12
    %M��,00-59
    %p���������
    %S��,00-60
    %u���ڼ�,1-7
    %w���ڼ�,0-6
    %x���ظ�ʽ������
    %X���ظ�ʽ��ʱ��
    %y����е������λ��,00-99
    %Y��
    %Z����ʱ������
    ------------------------
    struct tm *pstTmLocal;
    time_t      lTime;
    lTime = time(NULL);
    pstTmLocal = localtime(lTime);

    strftime(p, sizeof(p), "%s", pstTmLocal);

    -- ticks 
    struct tms stTms;
    long    lTms = 0;
    lTms = times(&tTms);
    ---timeb
    struct timeb stTimeb;
    ftime(&stTimeb);
    sprintf(p, "%03d", stTimeb.millitm);

 * 
 */
struct tm*  GetLocalTime()
{
    struct tm *pstTmLocal;
    time_t      lTime;
    lTime = time(NULL);
    pstTmLocal = localtime(lTime);
    return pstTmLocal;
}

void GetDateTime(
        int     iWantedFormat, 
        char*   pcDateTime
        )
{
    struct tm       *pstTmCur        = NULL;
    char            acDateTimeb[DATETIME_LEN_MAX] = {0};
    struct timeb    stTimeb         = {0};
    char            acTmb[4]        = {0}; 

    ftime(&stTimeb);
    memset(acTmb, 0x00, sizeof(acTmb));
    sprintf(acTmb, "%03d", stTimeb.millitm);
    pstTmCur    = GetLocalTime();

    switch iWantedFormat
    {
        case DATE_TYPE_YYMMDD:
        {
            sprintf(pcDateTime, "%4d%4d%4d", 
                    pstTmCur->tm_year + 1900, 
                    pstTmCur->tm_mon + 1, 
                    pstTmCur->tm_mday);
            break;
        }

        case DATE_TYPE_YYYYMMDDHHMMSSBBB:
        {
#if 0
            sprintf(pcDateTime, "%4d%4d%4d", 
                    pstTmCur->tm_year + 1900, 
                    pstTmCur->tm_mon + 1, 
                    pstTmCur->tm_mday);
#endif
            break;
        }
        case DATE_TYPE_YYYYMMDDHHMMSS:
        {
            strftime(pcDateTime, DATETIME_LEN_MAX - 3, 
                    "%Y%m%d%H%M%S", pstTmCur);
            break;
        }
        case DATE_TYPE_YYYYMMDD_HHMMSS_BBB:
        {
            strftime(acDateTimeb, DATETIME_LEN_MAX - 3, 
                    "%Y%m%d %H%M%S ", pstTmCur);
            strcat(acDateTimeb, acTmb);
            strcpy(pcDateTime, acDateTimeb);
        }
        default:
        {
            break;
        
        }
    }
    return;
}
/* @ desc   : open log 
 * @ input  : 
 *              char* pcLogPath  
 *              char* pcLogName
 *              iLogSwitchMode -- date: ***.YYYYMMDD
 *                             -- size ****.YYYYMMDDMMDDHHMMSS
 * @ output :  
 *              suc or failed
 * @ cautious: 
 */
int OpenFile(
        char* pcLogPath,
        char* pcLogFile,
        int iLogSwitchMode
        )
{
    int             iRet            = OK;
    char            acFullPath[FILE_PATH_LEN + FILE_NAME_LEN + DATETIME_LEN_MAX ] = {0};
    char            acBackFileName[FILE_NAME_LEN + DATETIME_LEN_MAX  + 1] = {0};
    char            acDateTime[DATETIME_LEN_MAX] = {0};
    struct stat     stFileStat   = {0};
    long            lLogSize        = LOG_SIZE_DEFAULT;
    
    if (!pcLogFile || !pcLogPath)
    {
        return ERR_CODE_INVALID_PARA;
    }

    GetDateTime(DATE_TYPE_YYYYMMDDHHMMSS, acDateTime);
    
    sprintf(acFullPath, "%s%s", 
                pcLogPath, pcLogFile);
    if (LOG_SWITCH_DATE == iLogSwitchMode) 
    {
	    strncat(acFullPath, acDateTime, strlen("YYYYMMMDD"));
    
    }
    else if (LOG_SWITCH_SIZE == iLogSwitchMode)
    {
        if (getenv(E_LOG_SIZE))
        {
            lLogSize    = atol(getenv(E_LOG_SIZE));
        }
	    iRet = stat(acFullPath, &stFileStat);
	    if (!iRet && (stFileStat.st_size > lLogSize))
	    {
            sprintf(acBackFileName, "%s.%s", pcLogFile, acDateTime);
            rename(pcLogFile, acBackFileName);
	    }
    }

    g_fpLog = fopen(acFullPath, "a+");
    if (!g_fpLog)
    {
        iRet    = ERR_CODE_OPENFILE_FAILED;
    }
    return iRet;

}


/* 
 * @ desc: log 
 * @ input:
 * @        iLogMode:  log level
 *          pcLogFile: log file name
 *          pcFmt:     log content start from this
 * @ output: 
 *          log suc or failed.
 * @ cautious:
 */
 
FILE                *g_fpLog  = NULL;
int	YDLog(
    int     iLogMode,
    char    *pcLogFile,
    char    *pcLogedFile,
    int     iLogedFileLine,    
    char    *pcFmt,
    ...
    )
{
    
    /*  step 1. ������־�����ж���¼��־
     *  step 2. ���ݻ��������ҵ���¼����־·��,·��������,�½�·��.
     *  step 3. �ҵ�д����־��ȫ·��,�ļ�������,�½��ļ����ڣ������־״̬������־
     *  step 3. ������־�����ж���¼��־
     *  step 3. �ر��ļ����
     */
    int     iRet                        =  OK;
    char    acLogPath[FILE_PATH_LEN + FILE_NAME_LEN]    = {"."};
    int     iLogSize                    = LOG_SIZE_DEFAULT;
    int     iLogLevel                   = LOG_LEVEL_DEBUG;
    char    acLogDate[DATE_LEN_MAX]     = {0};  /* file path: log_dir/date/logfile */
    /* time */
    long    lTick                       = 0;
    struct  timeb stTimeB               = {0};
    struct tm   *pstTmLocal             = NULL;
    char    acLogDateTimeb[DATETIME_LEN_MAX] = {0};

    int     iLogSwitchMode              = LOG_SWITHCH_SIZE;

    /*  step 1. ������־�����ж���¼��־ */
    if (getenv(E_LOG_LEVEL))
    {
        iLogLevel    = atoi(getenv(E_LOG_LEVEL));
    }
    
    /* С�ڵ�ǰ��ӡ�ȼ���ֱ���˳� */
    if (iLogMode < iLogLevel)
    {
        return iRet;
    }
    /* step 2. �ҵ���־���·�� */
    if (getenv(E_LOG_PATH)
    {
        memset(acLogPath, 0, sizeof(acLogPath));
        strcpy(acLogPath, (char*)getenv(E_LOG_PATH));
    }
    strcat(acLogPath, "/");

    memset(acLogDate, 0, sizeof(acLogDate));
    GetDateTime(DATE_TYPE_YYMMDD, acLogDate);

    strcat(acLogPath, acLogDate);
    strcat(acLogPath, "/");

    /* �ж��ļ��д��� */
    iRet    = ConfigDir(acLogPath, pcLogedFile);
    RETURN_IF_FAILED(iRet);

     /* 
      * step 3. ����־ 
      */
     
    GetDateTime(DATE_TYPE_YYYYMMDD_HHMMSS_BBB, acLogDateTimeb);
    if (getenv(E_LOG_SWITCH_MODE))
    {
        iLogSwitchMode    = atoi(getenv(E_LOG_SWITCH_MODE));
    }

    iRet    = OpenFile(acLogPath, pcLogFile, iLogSwitchMode);
    RETURN_IF_FAILED(iRet);

    /* 
     * step 4. write log 
     */

    fprintf(g_fpLog, "[%5s][%06ld][%12s:%05d][%s]",
            ((iLogMode == LOG_LEVEL_ERR) ? "ERROR" :
                ((LOG_LEVEL_WARNING == iLogMode) ? "WARN ":
                    (LOG_LEVEL_INFO == iLogMode) ? "INFO ": "DEBUG")), 
            (long)getpid(),
            __FILE__, __LINE__, 
            acLogDateTimeb);
    return uiRet;

}
