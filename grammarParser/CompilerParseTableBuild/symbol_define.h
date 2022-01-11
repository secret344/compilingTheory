#ifndef _SYMBOL_DEFINE_
#define _SYMBOL_DEFINE_

typedef enum
{
    GRAMMAR_END = -1,
    NO_TERMINAL_MAXRANGE = 6,
    NO_TERMINAL_VALUE_BASE = 256,
    TERMINAL_MAX_RANGE = 7,
    EOI = 0,
    SEMI = 1,
    PLUS = 2,
    TIMES = 3,
    LP = 4,
    RP = 5,
    NUM_OR_ID = 6,
    WHITE_SPACE = 7,
    UNKNOWN_SYMBOL = 8,

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