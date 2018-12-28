#ifndef __PARSER_H
#define __PARSER_H

#include "macro.h"
#include <sys/types.h>
#include "rbtree.h"

typedef enum tagErrCode_E
{
    ERR_CODE_SUCCESS,
    ERR_CODE_PARSEFAILED = 1,
    ERR_CODE_INVAILDLINE,
    ERR_CODE_UNRECOGNISELINE,
    ERR_CODE_MALLOCFAILED,

    ERR_CODE_NO_CB,                 /* no callback func */

    /* parse line content */
    ERR_CODE_NONEEDPARSE,
    ERR_CODE_MAX,
}ErrCode_E;
typedef enum tagTranType_E
{
    TRANS = 0,
}TranType_E;


typedef enum tagCtxType_E
{
    CT_INVALID	= -1,
    CT_TDET     = 1,    /* format like this [017][01][/home/jfxt/]\
                            [10.14.134.16][8864][000054][/tmp/IntegralCheckF/6641007CCQF20181130.zip] */
    CT_TXCS,            /* ----------通讯参数获取-------FROM[10.14.128.50][099][01]---[1000][5] */
    CT_JYZR,            /* 交易准入判断失败 or "----------交易准入判断结束---To[%s][%s] */ 
    CT_INFO,            /* InfoBuf[021|01|]OutBuf[023|01|] or InfoBuf[023|01|] */
    CT_SHMA,            /* shmat失败 */  /* ignore */

    CT_UPRQ,                  /* ----------接收传输请求(上传)--------FROM[%s]--TO[%s][%s]---[%s][%d] */
    CT_DWRQ     = CT_UPRQ,    /* ----------接收传输请求(下载)--------FROM[%s]---TO[%s][%s]---[%s][%d]*/
    CT_BATQ     = CT_UPRQ,    /* ----------接收传输请求(批量下载)--------FROM[%s]--TO[%s][%s]---[%s][%d] */
    CT_TMPQ     = CT_UPRQ,    /* ----------接收传输请求(获取模板)--------FROM[%s]--[%s][%d] */

    CT_HQPZ,            /* "获取配置文件信息失败" */
    CT_XYXT,            /* 向源系统发送报文响应出错[%d]! */ /* end flag */
    CT_LJYY,            /*  "连接应用系统失败[%s][%s]" */
    CT_DYTC,            /* "调用TcpRecvq函数失败[%d]! */
    CT_WJCS,            /* "文件传输失败. ReasonCode = [%4.4s]" "ReasonMsg = [%s].*/
    
    
    CT_RETS,            /* "上传成功" */
    CT_RETF,            /* "文件传输失败"*/
    CT_RETB,            /*  "多文件文件传输失败. ReasonCode = [%s], ReasonMsg = [%s].\n" */

    CT_JSCS,            /*  "接收传输请求[C]失败." */
    CT_TCPS,            /*  TcpSendq [S] error[%d]!  or TcpSendq error[%d]!*/
    CT_YCYY,            /*  远程应用系统失败[%s][%s] */
    CT_YCLJ,            /*  远程连接 ***    */

    CT_GZWJ,            /*  规则文件[%s]不存在 */

    /* end flag */   
    CT_CSFH,            /* 传输返回文件[0000][交易成功] */
    CT_RPAG,

    /* from agent */
    CT_RFAG,            /*  req from agent[%s] */
    
    CT_IGNR,            /* 通知下游系统完毕，上游系统开始文件传输*/

    /* no need to parse */
    CT_IGNO,         

    

    CT_MAX
}CtxType_E;

#define LINECONTENT_P
#ifdef LINECONTENT_P
typedef struct tagLineContent_S
{
    CtxType_E   enContentType;              /* content type             */

    char        *pcTranCode;                /* trans code               */
    char        *pcRetCode;                 /* ret code                 */
    char        *pcRetDesc;                 /* ret code description     */

    char        *pcAppSrc;                  /* app src code             */
    char        *pcAppDst;                  /* app destion code         */
    char        *pcNodeSrc;                 /* node src code            */
    char        *pcNodeDst;                 /* node destion code        */
    char        *pcDstFile;                 /* destion full path        */
    char        *pcSeqNo;                   /* SEQ_FTP_CLI_LIST         */
    char        *pcSrcIp;                   /* src   ip                 */
    char        *pcDstIp;                   /* destion  ip              */
    char        *pcDstPort;                 /* destion port             */

    char        *pcBasePath;                /* destion base path*/

	/* trans */
	char		*pcDst;						/* appDst + nodeDst */
	char		*pcSrc;						/* appSrc + nodeSrc */
    
}LineContent_S;

#else
typedef struct tagLineContent_S
{
    CtxType_E   enContentType;               /* content type             */

    char        acTranCode[4 + 1];          /* trans code               */
    char        acRetCode[4 + 1];           /* ret code                 */
    char        acRetDesc[128 + 1];         /* ret code description     */

    char        acAppSrc[3 + 1];            /* app src code             */
    char        acAppDst[3 + 1];            /* app destion code         */
    char        acNodeSrc[2 + 1];           /* node src code            */
    char        acNodeDst[2 + 1];           /* node destion code        */
    char        acDstFile[MAX_PATH_LEN];    /* destion full path        */
    char        acSeqNo[20 + 1];            /* SEQ_FTP_CLI_LIST         */
    char        acDstIp[15 + 1];            /* destion  ip              */
    char        acDstPort[5+ 1];            /* destion port             */
    
}LineContent_S;
#endif


typedef struct tagLineEntry_S
{
    char        acDate[10 + 1];             /* start date               */
    char        acTime[8 + 1];              /* start time               */
    char        acPid[5 + 1];               /* pid who logged           */
    char        acFileLine[128 + 1];        /* filename and line number */

    char        acEndDate[10 + 1];          /* end date                 */
    char        acEndTime[8 + 1];           /* end time                 */
    
    LineContent_S*  pstLnCtt;               /* point to line content struct */

    char        acKey[10 + 8 + 8 + 1];      /* key = acDate + acTime + tPid */
    struct rb_node stNode;                  /* rbtree node              */
}LineEntry_S;

int ParseDir(char* pcPath);

#endif
