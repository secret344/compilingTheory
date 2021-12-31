#include "pda_parse.h"
static void pdaParse();
static void parseError();

static Stack *pdaStack = NULL;
static LexerStr lexer = NULL;

void PDA_compiler_init()
{
    lexer = newLexerStr("1123+2asd;");
    pdaStack = new_stack();
    sIntPush(pdaStack, STMT);
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
        case STMT:
            if (LexerMatch(LEXER_EOI))
                spop(pdaStack);
            else
            {
                spop(pdaStack);
                sIntPush(pdaStack, STMT);
                sIntPush(pdaStack, SEMI);
                sIntPush(pdaStack, EXPR);
            }
            break;
            // expr -> term expr’
        case EXPR:
            spop(pdaStack);
            sIntPush(pdaStack, EXPR_PRIME);
            sIntPush(pdaStack, TERM);
            break;
            // term -> factor term’
        case TERM:
            spop(pdaStack);
            sIntPush(pdaStack, TERM_PRIME);
            sIntPush(pdaStack, FACTOR);
            break;
            // expr’ -> + term expr’ |  ε
        case EXPR_PRIME:
            spop(pdaStack);
            if (LexerMatch(LEXER_PLUS))
            {
                sIntPush(pdaStack, EXPR_PRIME);
                sIntPush(pdaStack, TERM);
                sIntPush(pdaStack, PLUS);
            }
            break;
            // term’ -> * factor term’ |ε
        case TERM_PRIME:
            spop(pdaStack);
            if (LexerMatch(LEXER_TIMES))
            {
                sIntPush(pdaStack, TERM_PRIME);
                sIntPush(pdaStack, FACTOR);
                sIntPush(pdaStack, MULTIPLE);
            }
            break;
            // factor -> number_or_id | (expr)
        case FACTOR:
            spop(pdaStack);
            if (LexerMatch(LEXER_NUM_OR_ID))
            {
                sIntPush(pdaStack, NUM_OR_ID);
            }
            else if (LexerMatch(LEXER_LP))
            {
                sIntPush(pdaStack, RIGHT_PARENT);
                sIntPush(pdaStack, EXPR);
                sIntPush(pdaStack, LEFT_PARENT);
            }
            else
                parseError();
            break;
        case PLUS:
            spop(pdaStack);
            if (LexerMatch(LEXER_PLUS) == FALSE)
                parseError();
            LexerAdvance(lexer);
            break;
        case NUM_OR_ID:
            spop(pdaStack);
            if (LexerMatch(LEXER_NUM_OR_ID) == FALSE)
                parseError();
            LexerAdvance(lexer);
            break;
        case MULTIPLE:
            spop(pdaStack);
            if (LexerMatch(LEXER_TIMES) == FALSE)
                parseError();
            LexerAdvance(lexer);
            break;
        case LEFT_PARENT:
            spop(pdaStack);
            if (LexerMatch(LEXER_LP) == FALSE)
                parseError();
            LexerAdvance(lexer);
            break;
        case RIGHT_PARENT:
            spop(pdaStack);
            if (LexerMatch(LEXER_RP) == FALSE)
                parseError();
            LexerAdvance(lexer);
            break;
        case SEMI:
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