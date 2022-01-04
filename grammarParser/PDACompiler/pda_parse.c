#include "pda_parse.h"
static void pdaParse();
static void parseError();

static Stack *pdaStack = NULL;
static LexerStr lexer = NULL;

void PDA_compiler_init()
{
    lexer = newLexerStr("1123+2asd;");
    pdaStack = new_stack();
    sIntPush(pdaStack, Gra_STMT);
    pdaParse();
    printf("PdaParser accept input string");
}

void pdaParse()
{
    // stmt -> ε | expr;stmt
    // expr -> term expr’
    // expr’ -> + term expr’ |  ε
    // term -> factor term’
    // term’ -> * factor term’ |ε
    // factor -> number_or_id | (expr)
    LexerAdvance(lexer);
    while (stacksize(pdaStack) > 0)
    {
        Grammar action = speek(pdaStack);
        switch (action)
        {
            // stmt -> ε | expr;stmt
        case Gra_STMT:
            if (LexerMatch(LEXER_EOI))
                spop(pdaStack);
            else
            {
                spop(pdaStack);
                sIntPush(pdaStack, Gra_STMT);
                sIntPush(pdaStack, Gra_SEMI);
                sIntPush(pdaStack, Gra_EXPR);
            }
            break;
            // expr -> term expr’
        case Gra_EXPR:
            spop(pdaStack);
            sIntPush(pdaStack, Gra_EXPR_PRIME);
            sIntPush(pdaStack, Gra_TERM);
            break;
            // term -> factor term’
        case Gra_TERM:
            spop(pdaStack);
            sIntPush(pdaStack, Gra_TERM_PRIME);
            sIntPush(pdaStack, Gra_FACTOR);
            break;
            // expr’ -> + term expr’ |  ε
        case Gra_EXPR_PRIME:
            spop(pdaStack);
            if (LexerMatch(LEXER_PLUS))
            {
                sIntPush(pdaStack, Gra_EXPR_PRIME);
                sIntPush(pdaStack, Gra_TERM);
                sIntPush(pdaStack, Gra_PLUS);
            }
            break;
            // term’ -> * factor term’ |ε
        case Gra_TERM_PRIME:
            spop(pdaStack);
            if (LexerMatch(LEXER_TIMES))
            {
                sIntPush(pdaStack, Gra_TERM_PRIME);
                sIntPush(pdaStack, Gra_FACTOR);
                sIntPush(pdaStack, Gra_MULTIPLE);
            }
            break;
            // factor -> number_or_id | (expr)
        case Gra_FACTOR:
            spop(pdaStack);
            if (LexerMatch(LEXER_NUM_OR_ID))
            {
                sIntPush(pdaStack, Gra_NUM_OR_ID);
            }
            else if (LexerMatch(LEXER_LP))
            {
                sIntPush(pdaStack, Gra_RIGHT_PARENT);
                sIntPush(pdaStack, Gra_EXPR);
                sIntPush(pdaStack, Gra_LEFT_PARENT);
            }
            else
                parseError();
            break;
        case Gra_PLUS:
            spop(pdaStack);
            if (LexerMatch(LEXER_PLUS) == FALSE)
                parseError();
            LexerAdvance(lexer);
            break;
        case Gra_NUM_OR_ID:
            spop(pdaStack);
            if (LexerMatch(LEXER_NUM_OR_ID) == FALSE)
                parseError();
            LexerAdvance(lexer);
            break;
        case Gra_MULTIPLE:
            spop(pdaStack);
            if (LexerMatch(LEXER_TIMES) == FALSE)
                parseError();
            LexerAdvance(lexer);
            break;
        case Gra_LEFT_PARENT:
            spop(pdaStack);
            if (LexerMatch(LEXER_LP) == FALSE)
                parseError();
            LexerAdvance(lexer);
            break;
        case Gra_RIGHT_PARENT:
            spop(pdaStack);
            if (LexerMatch(LEXER_RP) == FALSE)
                parseError();
            LexerAdvance(lexer);
            break;
        case Gra_SEMI:
            spop(pdaStack);
            if (LexerMatch(LEXER_SEMI) == FALSE)
                parseError();
            LexerAdvance(lexer);
            break;
        default:
            break;
        }
    }
}

void parseError()
{
    printf("PDA parse error");
    exit(1);
}