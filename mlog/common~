#define    OK                   (0)
#define    ERR                  (-1)

#define    RETURN_IF_FAILED(r) \
    if (OK != r){return r;}
#define    BREAK_IF_FAILED(r) \
    if (OK != r){break;}
int ConfigDir(char* pcDir)
{
    struct stat stDirStat   = {0};
    int         iRet        = 0;

    iRet    = stat(pcDir, &stDirStat);
    if (iRet)
    {
        if (ENOENT != iRet))
        {
            /* printf("log file dir check error.\n"); */
            return  iRet;
        }
    }
    
    if (S_IFDIR != stDirStat.st_mode)
    {
        iRet = mkdir(pcDir, S_IRWXU | S_IRWXG); 
    }
    return iRet;
}
