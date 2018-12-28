#include "publicf.h"
#include "macro.h"

#define LOG_PATH_LEN_MAX    (128)
#if 0
/**
 *  * @ desc   : replace env var
 *  * @ in     : path string 
 *  * @ out    :
 *  * @ cautious:
 *  **/
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


/**
 * @ desc : get  nth element after seprating string 
 *  example: 
 *       [2018-12-20 04:59:15    74042 ____clisfer.sqc:1165 accept ok]
 *       sep = ' '
 *        1th         2th         3th      4th              5th    6th
 * @ in   :
 * @ out  :
 * @ cautious:
 **/         
int GetNthEleBySep(char* pcBuf, int iIndex, char cSep, char* pcOut)
{
    int                 iRet            = 0;
    int                 i               = 0;
    char*               pc              = NULL;
    char                acSep[16 + 1]   = {0};
    char*               pcDupStr        = NULL;

    pcDupStr    = strdup(pcBuf);
    acSep[0]    = cSep;
    
    pc  = strtok(pcDupStr, acSep);
    while (pc && (i < iIndex - 1))
    {
        pc = strtok(NULL, acSep);
        i++;
    }

    if (pc)
    {
        memcpy(pcOut, pc, strlen(pc));
    }
    
    free(pcDupStr);
    return iRet;
}



/**
 * @ desc : get  nth element start pos
 *    example: 
 *      [2018-12-20 04:59:15    74042 ____clisfer.sqc:1165 accept ok]
 *      sep = ' '
 *       1th        2th         3th   4th                  5th  
 * @ in   :
 * @ out  :
 * @ cautious
 **/
int GetNthPosBySep(char* pcBuf, int iIndex, char cSep, char** ppcOut)
{
    char*               pc              = NULL;
    char*               pcNext          = NULL;

    int                 i               = 0;

    pc  = pcBuf;
    while ((i < iIndex - 1) && (pc != NULL) && (*pc != '\0') && (*pc != '\n'))
    {
        if (*pc == cSep)
        {
            i++;
            pcNext = pc + 1;
            while (*pcNext == cSep)
            {
                pcNext++;
            }

            pc = pcNext;
        }
        else
        {
            pc++;
        }
    }

    if (iIndex -1 != i)
    {
        *ppcOut = NULL;
    }

    *ppcOut = pc;
    return 0;
}




/*
 * @ desc: trim left space and right space 
 * @ in  :
 * @ out :
 * @ cautious:
 *
 */
void TrimLR(char* pcBuf)
{
    char*           pcEnd           = NULL;
    char*           pcStart         = NULL;

    pcStart = pcBuf;
    pcEnd   = pcBuf + strlen(pcBuf) - 1;
    /** right **/
    while (*pcEnd == 0x20  ||
                *pcEnd == 0x09 ||
                *pcEnd == 0x0a ||
                *pcEnd == 0x0d)
    {
       pcEnd--;
    }

    pcEnd++;
    *pcEnd = '\0';

    /** left **/
    while (*pcStart == 0x20  ||
                *pcStart == 0x09 ||
                *pcStart == 0x0a ||
                *pcStart == 0x0d)
    {
        pcStart++;
    }

    strcpy(pcBuf, pcStart);

    return;
}
