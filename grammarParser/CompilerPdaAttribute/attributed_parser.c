#include "attributed_parser.h"

static void pdaParse();
static void parseError();

static Stack *pdaStack = NULL;
static LexerStr lexer = NULL;

void PDA_compiler_init()
{
    lexer = newLexerStr("1123+2asd;");
    pdaStack = new_stack();
    sPointPush(pdaStack, STMT);
    pdaParse();
    printf("PdaParser accept input string");
}

void pdaParse()
{
    // ε|{$1=$2=getname();} expr {freename($0);}; stmt
    // stmt - > ε| expr ; stmt
    // expr -> term expr’
    // expr’ -> + term {op(‘+’);} expr’ |ε
    // term -> factor term’
    // term’ -> * factor{op(‘*’);} term’
    // factor -> number_or_id { rvalue (number_or_id);} | (expr)

    LexerAdvance(lexer);
    while (stacksize(pdaStack) > 0)
    {
        AttrGrammar action = speek(pdaStack);
        switch (action)
        {
            // stmt -> ε | expr;stmt
        case STMT:
            if (LexerMatch(LEXER_EOI))
                spop(pdaStack);
            else
            {
                spop(pdaStack);
                sPointPush(pdaStack, STMT);
                sPointPush(pdaStack, SEMI);
                sPointPush(pdaStack, EXPR);
            }
            break;
            // expr -> term expr’
        case EXPR:
            spop(pdaStack);
            sPointPush(pdaStack, EXPR_PRIME);
            sPointPush(pdaStack, TERM);
            break;
            // term -> factor term’
        case TERM:
            spop(pdaStack);
            sPointPush(pdaStack, TERM_PRIME);
            sPointPush(pdaStack, FACTOR);
            break;
            // expr’ -> + term expr’ |  ε
            // expr’ -> + term {op(‘+’);} expr’ |ε
        case EXPR_PRIME:
            spop(pdaStack);
            if (LexerMatch(LEXER_PLUS))
            {
                sPointPush(pdaStack, EXPR_PRIME);
                sPointPush(pdaStack, TERM);
                sPointPush(pdaStack, PLUS);
            }
            break;
            // term’ -> * factor{op(‘*’);} term’
        case TERM_PRIME:
            spop(pdaStack);
            if (LexerMatch(LEXER_TIMES))
            {
                sPointPush(pdaStack, TERM_PRIME);
                sPointPush(pdaStack, FACTOR);
                sPointPush(pdaStack, MULTIPLE);
            }
            break;
            //  factor -> number_or_id { rvalue (number_or_id);} | (expr)
        case FACTOR:
            spop(pdaStack);
            if (LexerMatch(LEXER_NUM_OR_ID))
            {
                sPointPush(pdaStack, NUM_OR_ID);
            }
            else if (LexerMatch(LEXER_LP))
            {
                sPointPush(pdaStack, RIGHT_PARENT);
                sPointPush(pdaStack, EXPR);
                sPointPush(pdaStack, LEFT_PARENT);
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