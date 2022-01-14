#ifndef _LR_PRODUCTION_
#define _LR_PRODUCTION_
#include "bool.h"
#include "lex_stack.h"
#include "symbol_define.h"

struct LRProduction
{
    int dotPos;
    BOOL printDot;
    SymbolDefine left;
    Stack *right;
} LRProduction;

#endif