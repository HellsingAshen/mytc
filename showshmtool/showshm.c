#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "showshmtype.h"
#include "logf.h"

#define ERR        (-1)
#define OK        (0)
#define ST_TYPE_FTP_APP_CONFIG    	(1)
#define ST_TYPE_FTP_APP_NODE_CFG    (2)
#define MAX_NODE_CONFIG             (500)
#define MAX_SHMSIZE_APPCFG 			(102400)

#define CHAR_ARR_LEN_MAX 1024
#define BREAK_IF_ERR(ret) \
	if (0 != ret) {printf("Get errorcode = [%d].\n", ret); break;}

int GetShMemId();
/*
 * input          : int iShmId   绑定共享内存的id
 * output         : 
 * caution         :
 * description    :
 *
 */
void ShowNodeCfgInMem(AppNodeCfg* pstNodeCfg)
{
	int                iNodeCfgCount    = 0;    
	if (!pstNodeCfg) return;
	printf(">>>>>>>>>>>>>>>>>>>show ftp_app_node_cfg>>>>>>>>>>>>>>>>>>>>>>\n");
	printf("%s%s\n", "[NodeSrc]", "[NodeDes]");
	while (pstNodeCfg && *(char*)pstNodeCfg != '\0')
	{
		printf("[%s][%s]\n", pstNodeCfg->AppNodeSrc, pstNodeCfg->AppNodeDes);
		iNodeCfgCount++;
		pstNodeCfg++;
	}
	printf("FROM TBL[FTP_APP_NODE_CFG] LOAD RECORD NUM = [%d] .\n", iNodeCfgCount);
	printf("<<<<<<<<<<<<<<<<<<<show ftp_app_node_cfg<<<<<<<<<<<<<<<<<<<<<<\n");
	
	return;
}

/*
 * input          : todo
 * output         : 
 * caution        :
 * description    :
 *
 */
void ShowAppCfgInMem(CFG* pstAppCfg)
{
	int                iAppCfgCount    = 0;    
	if (!pstAppCfg) return;
	printf(">>>>>>>>>>>>>>>>>>>show ftp_app_config >>>>>>>>>>>>>>>>>>>>>>\n");
	printf("[%8s][%33s][%6s][%256s][%20s]\n", 
		 "APP|ND", "APP_IP", "PORT","APP_PATH", "APP_ID");
	while (pstAppCfg && *(char*)pstAppCfg != '\0')
	{
		printf("[%8s][%33s][%6s][%256s][%20s]\n", 
			pstAppCfg->APP_DN,pstAppCfg->pT_APP_IP,pstAppCfg->pT_APP_PORT,pstAppCfg->pT_APP_PATH,pstAppCfg->pT_APP_ID);
		iAppCfgCount++;
		pstAppCfg++;
	}
	printf("FROM TBL[FTP_APP_CONFIG] LOAD RECORD NUM = [%d] .\n", iAppCfgCount);
	printf("<<<<<<<<<<<<<<<<<<<show ftp_app_config<<<<<<<<<<<<<<<<<<<<<<\n");
	
	return;

}
/*
 * input          : int iShmId   绑定共享内存的id
 * output         : 
 * caution        :
 * description    :
 *
 */
int ShowShmById(
		int iShmId, 
		int iStructType)
{
	void*            pShm			= NULL;
	CFG*      				pstAppCfg      = NULL;
	AppNodeCfg*             pstNodeCfg     = NULL;

	if (iShmId < 0) return ERR;

	pShm    = shmat(iShmId, 0, 0);
	if (!pShm)
	{
		printf("shmat error at [%d] line.\n", __LINE__ );
		return ERR;
	}
printf("iShmId = [%d].  \n", iShmId);

	switch(iStructType)
	{
		case ST_TYPE_FTP_APP_NODE_CFG:
		{
				pstNodeCfg = (AppNodeCfg*)pShm;
				ShowNodeCfgInMem(pstNodeCfg);
				break;
		}
		case ST_TYPE_FTP_APP_CONFIG:
		{
				pstAppCfg	= (CFG*)pShm;
				ShowAppCfgInMem(pstAppCfg);
				break;
		}
		default:
		{
				printf("invaild struct type.\n");
				break;
		}
	}

	return OK;

}
/*
 * 鑾峰彇鍏变韩鍐呭瓨鐨刬d
 */
int GetShMemId(
		char* pcFile, 
		int   iSize
		)
{
	if (!pcFile || iSize < 0) return ERR;

	key_t tKey= ftok(pcFile, 1);
	int iId = shmget(tKey, iSize, 0666);
	printf("tKey = %d. id = [%d]\n", tKey, iId);

	if (iId < 0) return ERR;

	return iId;
}

/*
 *@des:
 *@caution: 
 */
int main(int argc, char** argv)
{
	int                iShmNodeCfgId     = 0;
	int                iShmAppCfgId      = 0;
	int                iRet              = OK;

	do
	{
		LOGD("test.");
		LOGHEXD("hex test.", strlen("hex test."));
		iShmNodeCfgId    = GetShMemId(getenv("SHMFILE_NODE"), sizeof(AppNodeCfg) * MAX_NODE_CONFIG);
		printf("in stub,get TBL[FTP_APP_NODE_CFG] shmId = [%d].\n", iShmNodeCfgId);
		iRet = ShowShmById(iShmNodeCfgId, ST_TYPE_FTP_APP_NODE_CFG);
		BREAK_IF_ERR(iRet);

		iShmAppCfgId    = GetShMemId(getenv("SHMFILE"), MAX_SHMSIZE_APPCFG);
		printf("in stub,get TBL[FTP_APP_CONFIG] shmId = [%d].\n", iShmAppCfgId);
		iRet = ShowShmById(iShmAppCfgId, ST_TYPE_FTP_APP_CONFIG);
		BREAK_IF_ERR(iRet);
	} while (0);

	(void)shmdt((const void*)&iShmNodeCfgId);

	return 0;
}
