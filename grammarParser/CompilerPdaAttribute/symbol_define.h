#ifndef _SYMBOL_DEFINE_
#define _SYMBOL_DEFINE_

typedef enum
{
    GRAMMAR_END = -1,
    EOI,
    SEMI,
    PLUS,
    TIMES,
    LP,
    RP,
    NUM_OR_ID,
    WHITE_SPACE,
    UNKNOWN_SYMBOL,

    EXPR = 257,
    EXPR_PRIME = 259,
    FACTOR = 260,
    STMT = 256,
    TERM = 258,
    TERM_PRIME = 261,

    ACTION_0 = 512,
    ACTION_1 = 513,
    ACTION_2 = 514,
    ACTION_3 = 515,
    ACTION_4 = 516,
} SymbolDefine;

char *getSymbolStr(SymbolDefine symbol);
#endif