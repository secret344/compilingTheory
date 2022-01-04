#ifndef _PDA_PARSE_CPMPILER_
#define _PDA_PARSE_CPMPILER_
#include "lex_stack.h"
#include "Lexer.h"
typedef enum
{
    Gra_STMT,
    Gra_EXPR,
    Gra_EXPR_PRIME,
    Gra_TERM,
    Gra_TERM_PRIME,
    Gra_FACTOR,
    Gra_NUM_OR_ID,
    Gra_PLUS,
    Gra_SEMI,
    Gra_MULTIPLE,
    Gra_LEFT_PARENT,
    Gra_RIGHT_PARENT,
} Grammar;

void PDA_compiler_init();
#endif