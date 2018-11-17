typedef struct  APP_CFG
{
	char pT_APP_ID[20]; 		/* APP_ID */
	char APP_DN[8];				/* APP_CODE + NODE_CODE */
	char pT_APP_PATH[256];		/* HOME_PATH */
	char pT_APP_IP[33];			/* APP_IP*/
	char pT_APP_PORT[6];		/* APP_PORT*/

}CFG;
typedef struct  APP_NODE_CFG
{
    char AppNodeSrc[20];
    char AppNodeDes[20];
}AppNodeCfg;
