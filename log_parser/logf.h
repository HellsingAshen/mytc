#ifndef __LOG_H_
#define __LOG_H_

#define             OK                              (0)
#define             LOG_SIZE_DEFAULT                (50 * 1024 * 1024)
#define             ERR_CODE_LOG_BASE               (10000)

typedef enum tagLogMode_E
{
    LOG_MODE_OFF	= -1,       /* log off */
    LOG_MODE_DEBUG 	= 0,        /* debug */
    LOG_MODE_INFO,              /* info  */
    LOG_MODE_WARNING,           /* warning */
    LOG_MODE_ERR,               /* error */
    LOG_MODE_BULT               /* boundary limit */
}LogMode_E;

#define LOG_PATH_LEN_MAX        128     /* 日志文件路径的长度的最大值 */
#define LOG_NAME_LEN_MAX        32      /* 日志文件名的长度的最大值 */

/* 日志切换模式, 按文件大小或按日期 */
#define LOG_SWITCH_MODE_SIZE    1
#define LOG_SWITCH_MODE_DATE    2

#define LOG_SIZE_UNIT           1000000

#define LOG_DEFAULT_NAME        "yd"
#define SINGLE_LINE             "--------------------------------------------------------------------------------\n"

/* log in default file with LOGMODE[LOD_MODE_DEBUG] */
#define LOGE(sFmt, args...) \
    Log(LOG_DEFAULT_NAME, LOG_MODE_ERR  , __FILE__, __LINE__, sFmt, ##args)

#define LOGI(sFmt, args...) \
    Log(LOG_DEFAULT_NAME, LOG_MODE_INFO , __FILE__, __LINE__, sFmt, ##args)

#define LOGD(sFmt, args...) \
	Log(LOG_DEFAULT_NAME, LOG_MODE_DEBUG, __FILE__, __LINE__, sFmt, ##args)

#define LOGHEXD(pcBUf, iBufLen) \
	LogHexString(LOG_DEFAULT_NAME, LOG_MODE_DEBUG, __FILE__, __LINE__, pcBUf, iBufLen)

/* log normal */
#define LOG(pcLogFileName, iLogMode, sFmt, args...) \
	Log(pcLogFileName, iLogMode, __FILE__, __LINE__, sFmt, ##args)
#define LOGHEX(pcLogFileName, iLogMode, pcBUf, iBufLen) \
	LogHexString(pcLogFileName, iLogMode, __FILE__, __LINE__, pcBUf, iBufLen)

/* function declare */
int Log(char *sLogName, int iLogMode, char*pcLogedFile, int iLogedLine, char *sFmt, ...);

int LogHexString (char *sLogName, int iLogMode, char* pcLogedFile, int iLogedLine, char *psBuf, int nBufLen);
#endif
