#ifndef _PUBLICF_H_
#define _PUBLICF_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int ReplaceEnvVar(char *str);

int GetNthEleBySep(char* pcBuf, int iIndex, char cSep, char* pcOut);

int GetNthPosBySep(char* pcBuf, int iIndex, char cSep, char** ppcOut);

void TrimLR(char* pcBuf);

#endif
