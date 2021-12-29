#ifndef _ATTRIBUTED_PARSER_
#define _ATTRIBUTED_PARSER_
#include "Lexer.h"
#include "lex_stack.h"

typedef enum
{
    STMT,
    EXPR,
    EXPR_PRIME,
    TERM,
    TERM_PRIME,
    FACTOR,
    NUM_OR_ID,
    PLUS,
    SEMI,
    MULTIPLE,
    LEFT_PARENT,
    RIGHT_PARENT,
} AttrGrammar;

#endif