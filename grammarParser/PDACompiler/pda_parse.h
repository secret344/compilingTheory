#ifndef _PDA_PARSE_CPMPILER_
#define _PDA_PARSE_CPMPILER_
#include "lex_stack.h"
#include "Lexer.h"
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
} Grammar;

void PDA_compiler_init();
#endif