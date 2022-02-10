#include "symbol_define.h"
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
    case EOI:
        return "EOI";
    default:
        return "UNKNOWN SYMBOL";
    }
}