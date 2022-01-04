#include "parse_table_builder.h"

static void parseError();
static Stack *symbolArray = NULL;
static MapRoot symbolMap = NULL;

void parseError()
{
    printf("PDA parse error");
    exit(1);
}

static void runFirstSets()
{
}

void initProductions()
{
    symbolArray = new_stack();
    symbolMap = newMap(Map_Number);
    // stmt -> expr SEMI
    // expr -> term expr’ | ε
    // expr’ -> PLUS term expr’ |ε
    // term -> factor term’
    // term’ -> TIMES factor term’ |ε
    // factor -> LEFT_PAREN expr RIGHT_PAREN | NUMBER
    //
    // stmt -> expr SEMI
    Stack *productions = new_stack();
    sPointPush(productions, (int[3]){EXPR, SEMI, GRAMMAR_END});
    MySymbol *stmt = newSymbol(STMT, FALSE, productions);
    MapPutNumNode(symbolMap, STMT, stmt);
    sPointPush(symbolArray, stmt);
    // expr -> term expr’ | ε
    productions = new_stack();
    sPointPush(productions, (int[3]){TERM, EXPR_PRIME, GRAMMAR_END});
    MySymbol *expr = newSymbol(EXPR, TRUE, productions);
    MapPutNumNode(symbolMap, EXPR, expr);
    sPointPush(symbolArray, expr);
    // expr’ -> PLUS term expr’ |ε
    productions = new_stack();
    sPointPush(productions, (int[4]){PLUS, TERM, EXPR_PRIME, GRAMMAR_END});
    MySymbol *expr_prime = newSymbol(EXPR_PRIME, TRUE, productions);
    MapPutNumNode(symbolMap, EXPR_PRIME, expr_prime);
    sPointPush(symbolArray, expr_prime);
    // term -> factor term’
    productions = new_stack();
    sPointPush(productions, (int[3]){FACTOR, TERM_PRIME, GRAMMAR_END});
    MySymbol *term = newSymbol(TERM, FALSE, productions);
    MapPutNumNode(symbolMap, TERM, term);
    sPointPush(symbolArray, term);
    // term’ -> TIMES factor term’ |ε
    productions = new_stack();
    sPointPush(productions, (int[4]){TIMES, FACTOR, TERM_PRIME, GRAMMAR_END});
    MySymbol *term_prime = newSymbol(TERM_PRIME, TRUE, productions);
    MapPutNumNode(symbolMap, TERM_PRIME, term_prime);
    sPointPush(symbolArray, term_prime);
    // factor -> LEFT_PAREN expr RIGHT_PAREN | NUMBER
    productions = new_stack();
    sPointPush(productions, (int[4]){LP, EXPR, RP, GRAMMAR_END});
    sPointPush(productions, (int[2]){NUM_OR_ID, GRAMMAR_END});
    MySymbol *factor = newSymbol(FACTOR, FALSE, productions);
    MapPutNumNode(symbolMap, FACTOR, factor);
    sPointPush(symbolArray, factor);
    // 终结符
    // ;
    MySymbol *semi = newSymbol(SEMI, FALSE, NULL);
    MapPutNumNode(symbolMap, SEMI, semi);
    sPointPush(symbolArray, semi);
    // +
    MySymbol *plus = newSymbol(PLUS, FALSE, NULL);
    MapPutNumNode(symbolMap, PLUS, plus);
    sPointPush(symbolArray, plus);
    // *
    MySymbol *times = newSymbol(TIMES, FALSE, NULL);
    MapPutNumNode(symbolMap, TIMES, times);
    sPointPush(symbolArray, times);
    // lp (
    MySymbol *lp = newSymbol(LP, FALSE, NULL);
    MapPutNumNode(symbolMap, LP, lp);
    sPointPush(symbolArray, lp);
    // rp )
    MySymbol *rp = newSymbol(RP, FALSE, NULL);
    MapPutNumNode(symbolMap, RP, rp);
    sPointPush(symbolArray, rp);
    // num_or_id 数字或者id
    MySymbol *num_or_id = newSymbol(NUM_OR_ID, FALSE, NULL);
    MapPutNumNode(symbolMap, NUM_OR_ID, num_or_id);
    sPointPush(symbolArray, num_or_id);
    //
    runFirstSets();
}
