#ifndef _MY_SYMBOL_
#define _MY_SYMBOL_
#include "symbol_define.h"
#include "bool.h"
#include "lex_stack.h"

typedef struct MySymbol
{
    SymbolDefine value;
    BOOL isNullable;
    Stack *firstSet;
    Stack *followSet;
    Stack *productions;
} MySymbol;
MySymbol *newSymbol(SymbolDefine value, BOOL nullable, Stack *productions);
#endif