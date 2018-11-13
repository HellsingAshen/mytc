#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define        OK         (0)

#define        SIZE        (100)
char g_acStr[] = {"1|6217788300130014273|1|100|341222198807270015|ÄÚÂí¶û|"};

int GetOneField(char * Buffer, int n, char * Fld, char Seperator)
{
    int i, len;
    char    *p, *begin;

    i = 0 ;
    p = Buffer;
    while ( *p != '\0' &&  i != n - 1) {
        if ( *p == Seperator ) 
            i++;
        p++;
    }
    if ( *p == '\0') {
        Fld[0] = '\0';
        return(0);
    }
    begin = p;
    while ( *p != '\0' &&  *p != Seperator) 
        p++;
    len = p - begin;
    if (len != 0) {
        memcpy(Fld, begin, len);
        Fld[len] = '\0';
        return(len);
    } else {
        Fld[0] = '\0';
        return(0);
    }
}

int main ()
{
	int iRet = 0;
    int i = 1;
    char acFld[128] ;

    for (; i < 7 ; i++)
    {
        memset (acFld, 0, 128);
        iRet = GetOneField(g_acStr, i, acFld, '|'); 
        /* */ 
        printf("i = [%d]  Fld = [%s], iRet = [%d]\n", i, acFld, iRet);

    }
    return OK;
}
