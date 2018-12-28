#ifndef __RB_TREE_OP_
#define __RB_TREE_OP_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include "rbtree.h"

#include "parser.h"

LineEntry_S*  SerachNode(struct rb_root* pstRoot, const char* pcKey);

int InsertNode(struct rb_root* pstRoot, LineEntry_S* pstEntryNew);

void DeleteNode(struct rb_root* pstRoot, const char* pcKey);

void PrtTreeAsce(struct rb_root* pstRoot);

int FuzzySerachNode(
    struct rb_root* pstRoot,
    LineEntry_S*    pstEntry,
    LineEntry_S**   ppstLineEntry
    );

int RefreshNode(LineEntry_S* pstNew, LineEntry_S* pstOld);
#endif
