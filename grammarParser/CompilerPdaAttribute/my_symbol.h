#ifndef _MY_SYMBOL_
#define _MY_SYMBOL_
#include "symbol_define.h"
#include "bool.h"

typedef struct MySymbol
{
    SymbolDefine value;
    BOOL isNullable;
} MySymbol;

#endif