#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#define        OK         (0)

int GetLineOffset(char* pcFile, int iNum)
{
    int                 iCount          = 0;
    int                 iLen            = 0;
    FILE*               fp              = NULL;
    int                 iChar           = 0;

    assert(pcFile != NULL);
    if (iNum <= 0) return 0;
    
    fp = fopen(pcFile, "r");

    if (!fp) return -1;

    while (EOF != (iChar =  fgetc(fp)))
    {
        if ('\n' == iChar) iCount++;
        if (iCount == iNum) break;
    }

    iLen = ftell(fp);

    fclose(fp);

    return iLen;
}

int GetFileLine(char* pcFile)
{
    int                 iCount          = 0;
    FILE*               fp              = NULL;
    int                 iChar           = 0;

    assert(pcFile != NULL);
    
    fp = fopen(pcFile, "r");

    if (!fp) return -1;

    while (EOF != (iChar =  fgetc(fp)))
    {
        if ('\n' == iChar) iCount++;
    }

    fclose(fp);

    return iCount;
}

/* 
 * @ desc: merge two files to a new file  by special lines
 * @ in:
        pcSrcFile1      : file which to be merged into pcOutFile
        iSFStartLine1   : file start pos
        iSFEndLine1     : file end pos
        pcSrcFile2      : file which to be merged into pcOutFile
        iSFStartLine2   : file start pos
        iSFEndLine2     : file end pos
        pcOutFile       : file which is output file.
 * @ out: 
 * @ cautious:
 */

int MergeFile(
    char* pcSrcFile1, 
    int iSFStartLine1, 
    int iSFEndLine1, 
    char* pcSrcFile2, 
    int iSFStartLine2, 
    int iSFEndLine2, 
    char* pcOutFile
    )
{
    int                 iOffSet0        = 0;
    int                 iOffSet1        = 0;
    int                 iOffSet2        = 0;
    int                 iOffSet3        = 0;
    FILE*               fp1             = NULL;
    FILE*               fp2             = NULL;
    FILE*               fp3             = NULL;

    assert ((pcSrcFile1) && (pcSrcFile2) && (pcOutFile));

    iOffSet0 = GetLineOffset(pcSrcFile1, iSFStartLine1);
    iOffSet1 = GetLineOffset(pcSrcFile1, iSFEndLine1);
    iOffSet2 = GetLineOffset(pcSrcFile2, iSFStartLine2);
    iOffSet3 = GetLineOffset(pcSrcFile2, iSFEndLine2);

    fp1 = fopen(pcSrcFile1, "r");
    fp2 = fopen(pcSrcFile2, "r");
    fp3 = fopen(pcOutFile, "w");
    
    if (!fp1 || !fp2 || !fp3) return -1;
    /* source file 1 process */
    fseek(fp1, iOffSet0, SEEK_SET);
    while (ftell(fp1) < iOffSet1)
    {
        fputc(fgetc(fp1), fp3);
    }

    /* source file 2 process */
    fseek(fp2, iOffSet2, SEEK_SET);
    while (ftell(fp2) < iOffSet3)
    {
        fputc(fgetc(fp2), fp3);
    }
    
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);

    return 0;
}

int main ()
{
    char*               pcFile          = "./abc";
    int                 iRet            = 0;

    char*               pcFile1         = "./abcd";
    int                 iRet1           = 0;

    iRet = GetFileLine(pcFile);

    iRet1 = GetFileLine(pcFile1);

    MergeFile(pcFile, 0, iRet, pcFile1, 1, iRet1, "./out");
    return OK;
}
