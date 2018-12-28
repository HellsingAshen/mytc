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
    CT_TXCS,            /* ----------ͨѶ������ȡ-------FROM[10.14.128.50][099][01]---[1000][5] */
    CT_JYZR,            /* ����׼���ж�ʧ�� or "----------����׼���жϽ���---To[%s][%s] */ 
    CT_INFO,            /* InfoBuf[021|01|]OutBuf[023|01|] or InfoBuf[023|01|] */
    CT_SHMA,            /* shmatʧ�� */  /* ignore */

    CT_UPRQ,                  /* ----------���մ�������(�ϴ�)--------FROM[%s]--TO[%s][%s]---[%s][%d] */
    CT_DWRQ     = CT_UPRQ,    /* ----------���մ�������(����)--------FROM[%s]---TO[%s][%s]---[%s][%d]*/
    CT_BATQ     = CT_UPRQ,    /* ----------���մ�������(��������)--------FROM[%s]--TO[%s][%s]---[%s][%d] */
    CT_TMPQ     = CT_UPRQ,    /* ----------���մ�������(��ȡģ��)--------FROM[%s]--[%s][%d] */

    CT_HQPZ,            /* "��ȡ�����ļ���Ϣʧ��" */
    CT_XYXT,            /* ��Դϵͳ���ͱ�����Ӧ����[%d]! */ /* end flag */
    CT_LJYY,            /*  "����Ӧ��ϵͳʧ��[%s][%s]" */
    CT_DYTC,            /* "����TcpRecvq����ʧ��[%d]! */
    CT_WJCS,            /* "�ļ�����ʧ��. ReasonCode = [%4.4s]" "ReasonMsg = [%s].*/
    
    
    CT_RETS,            /* "�ϴ��ɹ�" */
    CT_RETF,            /* "�ļ�����ʧ��"*/
    CT_RETB,            /*  "���ļ��ļ�����ʧ��. ReasonCode = [%s], ReasonMsg = [%s].\n" */

    CT_JSCS,            /*  "���մ�������[C]ʧ��." */
    CT_TCPS,            /*  TcpSendq [S] error[%d]!  or TcpSendq error[%d]!*/
    CT_YCYY,            /*  Զ��Ӧ��ϵͳʧ��[%s][%s] */
    CT_YCLJ,            /*  Զ������ ***    */

    CT_GZWJ,            /*  �����ļ�[%s]������ */

    /* end flag */   
    CT_CSFH,            /* ���䷵���ļ�[0000][���׳ɹ�] */
    CT_RPAG,

    /* from agent */
    CT_RFAG,            /*  req from agent[%s] */
    
    CT_IGNR,            /* ֪ͨ����ϵͳ��ϣ�����ϵͳ��ʼ�ļ�����*/

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
