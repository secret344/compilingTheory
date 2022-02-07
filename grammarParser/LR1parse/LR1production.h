#ifndef _LR1_PRODUCTION_
#define _LR1_PRODUCTION_
#include "bool.h"
#include "lex_stack.h"
#include "symbol_define.h"
#include "my_ArrayList.h"

typedef struct LR1Production
{
    int dotPos;
    BOOL printDot;
    SymbolDefine left;
    My_ArrayList *right;
    My_ArrayList *lookAhead;
} LR1Production;
LR1Production *LR1productionCreate(int left, int dot, My_ArrayList *right);
LR1Production *LR1productionDotForward(LR1Production *production);
LR1Production *LR1productionCloneSelf(LR1Production *production);
BOOL LR1productionEquals(LR1Production *production, LR1Production *refProduction);
int LR1productionGetDotSymbol(LR1Production *production);
void LR1productionPrint(LR1Production *production);
#endif