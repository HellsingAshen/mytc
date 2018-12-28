#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "logf.h"
#include "macro.h"
#include "parser.h"

int main(int argc, char** argv)
{
    int             iRet                    = 0;
    int             i                       = 0;
    char            acPath[MAX_PATH_LEN]    = {0};

    if (argc < 2){
        printf("%s", USAGE);
        exit(0);
    }

    for (; i < argc; i++){
        if (!strcmp(*(argv + i), "-d")){
            memcpy(acPath, *(argv + i + 1), strlen(*(argv + i + 1)));
            printf("get in para: [ParserPath] = [%s]\n", acPath);
        }
    }
    
    /** parser file in dir **/   
    iRet    = ParseDir(acPath);
    RETURN_IF_ERR(iRet);

    do
    {
        LOGD("test.");
        LOGHEXD("hex test.", strlen("hex test."));
    } while (0);

    return 0;
}
