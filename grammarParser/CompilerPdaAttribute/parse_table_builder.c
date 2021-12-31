#include "parse_table_builder.h"

static void parseError();
static Stack *symbolArray = NULL;

void parseError()
{
    printf("PDA parse error");
    exit(1);
}

void initProductions()
{
    symbolArray = new_stack();
    // stmt -> expr SEMI
    // expr -> term expr’ | ε
    // expr’ -> PLUS term expr’ |ε
    // term -> factor term’
    // term’ -> TIMES factor term’ |ε
    // factor -> LEFT_PAREN expr RIGHT_PAREN | NUMBER
    Stack *productions = new_stack();
    sIntPush(productions, EXPR);
    sIntPush(productions, SEMI);
    MySymbol *stmt = newSymbol(STMT, FALSE, productions);
    sPointPush(symbolArray, stmt);
}
