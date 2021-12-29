#ifndef _SYMBOL_DEFINE_
#define _SYMBOL_DEFINE_

typedef enum
{
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

char *getSymbolStr(SymbolDefine symbol)
{
    switch (symbol)
    {
    case PLUS:
        return "PLUS";
    case TIMES:
        return "TIMES";
    case NUM_OR_ID:
        return "NUM_OR_ID";
    case SEMI:
        return "SEMI";
    case LP:
        return "LEFT_PARENT";
    case RP:
        return "RIGHT_PARENT";
    case EXPR:
        return "EXPR";
    case EXPR_PRIME:
        return "EXPR_PRIME";
    case FACTOR:
        return "FACTOR";
    case STMT:
        return "STMT";
    case TERM:
        return "TERM";
    case TERM_PRIME:
        return "TERM_PRIME";
    default:
        return "UNKNOWN SYMBOL";
    }
}
#endif