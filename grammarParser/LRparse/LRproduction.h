#ifndef _LR_PRODUCTION_
#define _LR_PRODUCTION_
#include "bool.h"
#include "lex_stack.h"
#include "symbol_define.h"
#include "my_ArrayList.h"

typedef struct LRProduction
{
    int dotPos;
    BOOL printDot;
    SymbolDefine left;
    My_ArrayList *right;
} LRProduction;
LRProduction *productionCreate(int left, int dot, My_ArrayList *right);
LRProduction *productionDotForward(LRProduction *production);
BOOL productionEquals(LRProduction *production, LRProduction *refProduction);
int productionGetDotSymbol(LRProduction *production);
void productionPrint(LRProduction *production);
#endif