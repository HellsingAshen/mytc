#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdarg.h>
#include <time.h>
#include <sys/time.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/times.h>
#include <sys/stat.h>
#include <string.h>
#include <memory.h>
#include "logf.h"
#include <ctype.h>
#include <sys/timeb.h>

FILE    *fp;
/* 调整日志参数获取方式 */
/* static   time_t  cTime    =0;*/
static   int     g_iLogMode = LOG_MODE_DEBUG;

int ConvertEnv(char *str);
int ReplaceEnvVar(char *str);
int OpenLogFile (char *sLogFilePath, char *sLogName, int nLogSwitchMode, int nLogSize, char *sDateTime );

/* @ desc   : log
 * @ input  : 
 * @ output : 
 * @ cautious:
 *
 */
int Log(char *sLogName, int iLogMode, char* pcLogedFile, int iLogedLine, char *sFmt, ...)
{
    int     nReturnCode;
    int     iParamLogSwitchMode = LOG_SWITCH_MODE_SIZE;

    char    sLogTime[128];
    char    sDateTime[16];
    char    acActLogName[100];
    char    tmpsLogName[30];
    char    sMilliTM[4];

    va_list ap;
    time_t  lTime;
    char    sParamLogFilePath[LOG_PATH_LEN_MAX] = {"."};
    int     iParamLogSize = LOG_SIZE_DEFAULT; 
    struct tm   *tTmLocal;
    struct stat stFilePathStat;
    struct timeb tTimeB;

    /* step 1: get current log mode */
    if(getenv("LOG_MODE"))
    {
        g_iLogMode  = atoi(getenv("LOG_MODE"));
    }

    if ((g_iLogMode == LOG_MODE_OFF) || (iLogMode < g_iLogMode))
    {
        /* while log-mode is off or iLogMode is less than env_log_mode , log nothing */
        return OK;
    }

    /** TODO: switch by other mode **/
    if (getenv ("LOG_SWITCH_MODE"))
    {
        iParamLogSwitchMode = atoi(getenv("LOG_SWITCH_MODE"));
    }

    if (getenv ("LOG_SIZE"))
    {
        iParamLogSize = atoi(getenv ("LOG_SIZE"));
    }
    
    if (getenv ("LOG_FILE_PATH"))
    {
        memset (sParamLogFilePath, 0, sizeof (sParamLogFilePath));
        strcpy (sParamLogFilePath, (char *)getenv ("LOG_FILE_PATH"));
    }


    /* get current time */
    memset (sLogTime, 0x00, sizeof(sLogTime));
    memset (sDateTime, 0x00, sizeof(sDateTime));
    lTime = time (NULL);
    tTmLocal = localtime (&lTime);

    /* 日志打印时间，精确到秒 */
    strftime (sLogTime, sizeof(sLogTime), "%Y%m%d %H:%M:%S", tTmLocal);
    strftime (sDateTime, sizeof(sDateTime), "%Y%m%d%H%M%S", tTmLocal);
    /* 日志打印毫秒 */
    memset(&tTimeB, 0, sizeof(tTimeB));
    ftime(&tTimeB);
    memset(sMilliTM, 0x00, sizeof(sMilliTM));
    snprintf(sMilliTM, sizeof(sMilliTM), "%03d", tTimeB.millitm);
    
    /* 日志文件路径，按日期 */
    strcat(sParamLogFilePath, "/");
    strncat(sParamLogFilePath, sDateTime, 8);

    /* 检查当日文件路径是否存在 */
    memset(&stFilePathStat, 0x00, sizeof(stFilePathStat));
    stat(sParamLogFilePath, &stFilePathStat);
    if (!S_ISDIR(stFilePathStat.st_mode))
    {
        /* 若不存在当日文件路径，新建文件夹 */
        nReturnCode = mkdir( sParamLogFilePath, S_IRWXU|S_IRWXG|S_IRWXO );
        if(nReturnCode != 0)
        {
            return nReturnCode;
        }
    }

    /* 日志文件名 */
    memset(tmpsLogName, 0x00, sizeof(tmpsLogName));
    strcpy(tmpsLogName, sLogName);
    tmpsLogName[strlen(tmpsLogName)]='\0';
    memset(acActLogName, 0x00, sizeof(acActLogName));
    sprintf(acActLogName, "%s_%8.8s_1.log", tmpsLogName, sDateTime);
    
    /* 打开日志文件 */
    nReturnCode = OpenLogFile (sParamLogFilePath, acActLogName, iParamLogSwitchMode, iParamLogSize, sDateTime);
    if (nReturnCode)
    {
        return (nReturnCode);
    }
    /* 依据日志模式打印日志头内容 */
    if(iLogMode == LOG_MODE_ERR)
    {
        fprintf(fp, "[ERROR][%06ld][%12s:%05d][%s %.3s]->", (long)getpid(), pcLogedFile, iLogedLine, sLogTime, sMilliTM); 
    }else if(iLogMode == LOG_MODE_INFO) 
    {
        fprintf(fp, "[INFO][%06ld][%12s:%05d][%s %.3s]->", (long)getpid(), pcLogedFile, iLogedLine, sLogTime, sMilliTM); 
    }else if(iLogMode == LOG_MODE_DEBUG)  
    {
        fprintf(fp, "[DEBUG][%06ld][%12s:%05d][%s %.3s]->", (long)getpid(), pcLogedFile, iLogedLine, sLogTime, sMilliTM); 
    }else if(iLogMode == LOG_MODE_WARNING)  
    {
        fprintf(fp, "[WARN][%06ld][%12s:%05d][%s %.3s]->", (long)getpid(), pcLogedFile, iLogedLine, sLogTime, sMilliTM); 
    }
    /* 打印日志 */
    va_start(ap, sFmt);
    vfprintf(fp, sFmt, ap);
    va_end(ap);

    fprintf(fp, "\n");
    fflush(fp);

    /* close file */
    fclose (fp);

    return (0); 
}

 /*
  * FUNC:   int LogDbgString (char *sLogName, int iLogMode, 
  *                             char *psBuf, int nBufLen);         
  * INPUT:  sLogName: 日志名, 不带路径                                       
  *         iLogMode: 日志级别,                                              
  *                   HT_LOG_MODE_ERROR,HT_LOG_MODE_NORMAL,HT_LOG_MODE_DEBUG 
  *         psBuf: 需输出的buffer                                            
  *         nBufLen: buffer的长度                                            
  * OUTPUT: 无                                                               
  * RETURN: 0: 成功, 其它: 失败                                              
  * DESC:   根据LOG_MODE, 将该级别之下的日志记录到日志文件中,                
  *         输出内容是buffer的16进制值                                       
  */
int LogHexString (char *sLogName, int iLogMode, char* pcLogedFile, int iLogLine, char *psBuf, int nBufLen)
{
    register int i,j=0;
    int     nReturnCode;

    char    sLine[100], sTemp[6];
    char    sLogTime[128];
    char    sDateTime[16];
    char    acLogName[100];
    char    tmpsLogName[30];
    char    sMilliTM[4];
    
    int     iParamLogSwitchMode = LOG_SWITCH_MODE_SIZE;
    char    sParamLogFilePath[LOG_PATH_LEN_MAX] = {"."};
    int     iParamLogSize = LOG_SIZE_DEFAULT; 
    
    time_t  lTime;
    struct  tm   *tTmLocal;
    struct  stat stFilePathStat;
    struct  timeb tTimeB;

    if(getenv("LOG_MODE"))
    {
        g_iLogMode  = atoi(getenv("LOG_MODE"));
    }

    if ((g_iLogMode == LOG_MODE_OFF) || (iLogMode < g_iLogMode))
    {
        return OK;
    }

    if (getenv ("LOG_SWITCH_MODE"))
    {
        iParamLogSwitchMode = atoi(getenv("LOG_SWITCH_MODE"));
    }


    if (getenv ("LOG_SIZE"))
    {
        iParamLogSize = atoi(getenv ("LOG_SIZE"));
    }
    
    if (getenv ("LOG_FILE_PATH"))
    {
        memset (sParamLogFilePath, 0, sizeof (sParamLogFilePath));
        strcpy (sParamLogFilePath, (char *)getenv ("LOG_FILE_PATH"));
    }


    /* get current time */
    memset (sLogTime, 0x00, sizeof(sLogTime));
    memset (sDateTime, 0x00, sizeof(sDateTime));
    lTime = time (NULL);
    tTmLocal = localtime (&lTime);

    strftime (sLogTime, sizeof(sLogTime), "%Y%m%d %H:%M:%S", tTmLocal);
    strftime (sDateTime, sizeof(sDateTime), "%Y%m%d%H%M%S", tTmLocal);

    memset(&tTimeB, 0, sizeof(tTimeB));
    ftime(&tTimeB);
    memset(sMilliTM, 0x00, sizeof(sMilliTM));
    snprintf(sMilliTM, sizeof(sMilliTM), "%03d", tTimeB.millitm);

    strcat(sParamLogFilePath, "/");
    strncat(sParamLogFilePath, sDateTime, 8);

    memset(&stFilePathStat, 0x00, sizeof(stFilePathStat));
    stat(sParamLogFilePath, &stFilePathStat);
    if (!S_ISDIR(stFilePathStat.st_mode))
    {
        nReturnCode = mkdir( sParamLogFilePath, S_IRWXU|S_IRWXG|S_IRWXO );
        if(nReturnCode != 0)
        {
            return nReturnCode;
        }
    }

    memset(tmpsLogName, 0x00, sizeof(tmpsLogName));
    strcpy(tmpsLogName, sLogName);
    tmpsLogName[strlen(tmpsLogName)]='\0';
    memset(acLogName, 0x00, sizeof(acLogName));
    sprintf(acLogName, "%s_%8.8s_1.log", tmpsLogName, sDateTime);

    nReturnCode = OpenLogFile (sParamLogFilePath, acLogName, iParamLogSwitchMode, iParamLogSize, sDateTime);
    if (nReturnCode)
    {
        return (nReturnCode);
    }
        
    fprintf(fp, "[%s][%06ld][%12s:%05d][%s %.3s]->[nLen: %d]\n",
	(iLogMode == LOG_MODE_ERR) ? "ERROR":
		((iLogMode == LOG_MODE_WARNING) ? ("WARN") : 
			(iLogMode == LOG_MODE_INFO) ? ("INFO") : 
				"DEBUG"),
    (long)getpid(), 
    pcLogedFile,     
    iLogLine, 
    sLogTime, 
    sMilliTM, 
    nBufLen);
    fprintf(fp, "%80.80s\n", SINGLE_LINE); 

    /* save log msg in file */
    for (i=0; i<nBufLen; i++)
    {
        /* initialize a new line */
        if (j==0)
        {
            memset ( sLine, ' ', sizeof(sLine));
            sprintf (sTemp, "%04d:", i );
            memcpy (sLine, sTemp, 5);
            sprintf (sTemp, ":%04d", i+15 );
            memcpy (sLine+72, sTemp, 5);
        }
        
        /* output psBuf value in hex */
        sprintf( sTemp, "%02X ", (unsigned  char)psBuf[i]);
        memcpy( &sLine[j*3+5+(j>7)], sTemp, 3);
        
        /* output psBuf in ascii */
        if ( isprint (psBuf[i]))
        {
            sLine[j+55+(j>7)]=psBuf[i];
        }
        else
        {
            sLine[j+55+(j>7)]='.';
        }
        j++;
        
        /* output the line to file */
        if (j==16)
        {
            sLine[77]=0;
            fprintf(fp, "%s\n", sLine);
            j=0;
        }
    }
    
    /* last line */
    if (j)
    {
        sLine[77]=0;
        fprintf(fp, "%s\n", sLine);
    }
    fprintf(fp, "%80.80s\n", SINGLE_LINE); 

    fflush(fp);

    /* close file */
    fclose (fp);

    return (0); 
}

/*****************************************************************************/
/* FUNC:   int OpenLogFile (char *sLogFilePath, char *sLogName,              */
/*                          int nLogSwitchMode, int nLogSize,                */
/*                          char *sDate, FILE *fp)                           */
/* INPUT:  sLogFilePath: 日志路径                                            */
/*         sLogName: 日志文件名                                              */
/*         nLogSwitchMode: 日志切换模式                                      */
/*                   LOG_SWITCH_MODE_SIZE, LOG_SWITCH_MODE_DATE              */
/*         nLogSize: LOG_SWITCH_MODE_SIZE模式下文件大小                      */
/*         sDateTime: 当前时间, YYYYMMDDhhmmss                               */
/* OUTPUT: fp: 打开的日志文件的指针                                          */
/* RETURN: 0: 成功, 其它: 失败                                               */
/* DESC:   根据nLogSwitchMode, 打开日志文件                                  */
/*         LOG_SWITCH_MODE_SIZE: 当文件大小(M)达到nLogSize, 切换到新文件,    */
/*                               原文件改名为文件名中带有时间                */
/*                               xx.log.YYYYMMDDhhmmss                       */
/*         LOG_SWITCH_MODE_DATE: 日志文件名带有日期, xx.log.YYYYMMDD         */
/*****************************************************************************/
int OpenLogFile (char *sLogFilePath, char *sLogName, int nLogSwitchMode, int nLogSize, char *sDateTime )
{
    char        sExpFilePath[LOG_PATH_LEN_MAX];
    char        sFullLogName[LOG_PATH_LEN_MAX+LOG_NAME_LEN_MAX];
    char        sFullBakLogName[LOG_PATH_LEN_MAX + LOG_NAME_LEN_MAX + 1];
    int         nReturnCode;
    struct stat statbuf;
    
    memset (sFullLogName, 0x00, sizeof (sFullLogName));
    
    strcpy (sExpFilePath, sLogFilePath);
    nReturnCode = ReplaceEnvVar (sExpFilePath);
    
    /* set log file name */
    if (!sLogName || strlen(sLogName) == 0)
        sprintf (sFullLogName, "%s/%s", sExpFilePath, LOG_DEFAULT_NAME);
    else
        sprintf (sFullLogName, "%s/%s", sExpFilePath, sLogName);
    
    if (nLogSwitchMode == LOG_SWITCH_MODE_DATE)
    {
        /* append date in log file name */
        strncat (sFullLogName, sDateTime, 8);
    }
    else
    {
        /* this is LOG_SWITCH_MODE_SIZE */
        /* check file size */
        memset (&statbuf, 0x00, sizeof(statbuf));
        nReturnCode = stat (sFullLogName, &statbuf);
        if ( nReturnCode == 0 && statbuf.st_size >= LOG_SIZE_UNIT * nLogSize )
        {
            memset (sFullBakLogName, 0x00, sizeof(sFullBakLogName));
            sprintf (sFullBakLogName, "%s.%s", sFullLogName, sDateTime);
            rename (sFullLogName, sFullBakLogName);
        }
    }

    /* open log file */
    fp = fopen (sFullLogName, "a+");
    if (fp == NULL )
        return (ERR_CODE_LOG_BASE+errno);

    return 0;
}

int  ConvertEnv(char *str)
{
char envbuf[LOG_PATH_LEN_MAX],buf[LOG_PATH_LEN_MAX];
char *ptr=NULL,*ptr1=NULL;
int   len,  choice=0; 
    
    memset(buf, 0, sizeof(buf));

    ptr=(char *)strpbrk((char *)str,"./");
    if ( ptr != NULL )
    {
        choice = 1;
        memset(envbuf, 0, sizeof(envbuf));
        memcpy(envbuf, &str[1], ptr-str-1);
    }
    else
    {
        choice = 2;
        memset(envbuf, 0, sizeof(envbuf));
        strcpy(envbuf,&str[1]);
    }

    ptr1=(char *)getenv(envbuf);
    if ( ptr1 == (char *)NULL )
    {
        return -1;
    }
    else
    {
        if ( choice == 1 )
        {
            strcat(buf, ptr1);
            strcat(buf, ptr);
        }
        else if ( choice == 2 )
            strcat(buf, ptr1);
    }

    len=strlen(buf);

    memset(str, 0, len + 1);
    strcpy(str, buf);

    return 0;
}

/*****************************************************************************/
/* FUNC:   int ReplaceEnvVar(char *str)                                      */
/* INPUT:  str: 字符串, 可能包含环境变量                                     */
/*              如: $(HOME)/src/$TERM                                        */
/* OUTPUT: str: 字符串, 环境变量已经用对应的值替换                           */
/* RETURN: 0: 成功, 其它: 失败                                               */
/* DESC:   对输入的字符串, 将其中的环境变量用对应的值替换                    */
/*         如: $(HOME)/src/$TERM, 其中的$(HOME)和$TERM会被替换               */
/*         调用时须保证str对应的buffer足够大, 不会因替换造成越界             */
/*****************************************************************************/
#ifndef _PUBLICF_H_
int ReplaceEnvVar(char *str)
{
    char *ptr=NULL;
    char buf[LOG_PATH_LEN_MAX], field[LOG_PATH_LEN_MAX];
    int  len=0,nRet,flag;
    int  count=1,i,j;

    /********************************************************************/
    /*      delete  characters ' ','(',')','\t' from string "str"       */
    /********************************************************************/
    len=strlen(str);
    memset(buf,0,sizeof(buf));

    for(i=0,j=0;i<len;i++)
    if ( str[i] != ' ' && str[i] != '\t' && str[i] != '(' && str[i] != ')' )
        buf[j++]=str[i];

    memset(str,0, len);
    strcpy(str,buf);

    /********************************************************/
    /*      distinguish if first character is '$' or not    */
    /********************************************************/
    if ( str[0] == '$' )
        flag = 1;
    else
        flag = 2;

    memset(buf, 0, sizeof(buf));
    if ( flag == 1 )
    {
        ptr=(char *)strtok((char *)str,"$");
        while ( ptr != NULL )
        {
            memset(field, 0, sizeof(field));
            sprintf(field,"%c%s",'$',ptr);
            nRet = ConvertEnv(field);
            if ( nRet != 0 )
                return -1;
    
            strcat(buf, field);

            ptr=(char *)strtok((char *)NULL,"$");
        }
    }
    else if ( flag == 2 )
    {
        ptr=(char *)strtok((char *)str,"$");
        while ( ptr != NULL )
        {
            count++;
            if ( count != 2)
            {
                memset(field, 0, sizeof(field));
                sprintf(field,"%c%s",'$',ptr);
                nRet = ConvertEnv(field);
                if ( nRet != 0 )
                    return -1;
            }
            else
            {
                memset(field, 0, sizeof(field));
                sprintf(field,"%s",ptr);
            }

            strcat(buf, field);

            ptr=(char *)strtok((char *)NULL,"$");
        }
    }

    len = strlen(buf);
    memcpy(str, buf, len+1);

    return 0;
}
#endif


/*
 * **函数名称: GetDate_YYYYMMDD                
 * **功能描述: 获取当前日期                    
 * **作    者:                                 
 * **输入参数:                                 
 * **输出参数:                                 
 * **          sCurrentDate：得到的日期        
 * **返回值:                                   
 */
void  GetDate_YYYYMMDD(char *sCurrentDate)
{
    time_t current;
    struct tm *tmCurrentTime;

    time(&current);
    tmCurrentTime = localtime(&current);
    sprintf(sCurrentDate, "%4d-%02d-%02d", tmCurrentTime->tm_year + 1900,
            tmCurrentTime->tm_mon + 1, tmCurrentTime->tm_mday);
}

/*
 * **函数名称: GetTime_HHMMSS                        
 * **功能描述: 获取时间                              
 * **作    者:                                       
 * **输入参数:                                       
 * **输出参数:                                       
 * **          buff：得到的时间                      
 * **返回值:                                         
 */
void GetTime_HHMMSS(char* buff)
{
    time_t now;
    struct tm * tTime;

    time(&now);
    tTime = localtime(&now);
    sprintf(buff, "%.2d-%.2d-%.2d", tTime->tm_hour, tTime->tm_min, tTime->tm_sec );
    return;
}


