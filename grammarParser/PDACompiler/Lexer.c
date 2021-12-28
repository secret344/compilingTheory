#include "Lexer.h"
static int lookAhead = -1;
static char *yytext = NULL;
static char current = -1;

static BOOL isAlnum(char c)
{
    if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
    {
        return TRUE;
    }
    return FALSE;
}

LexerStr newLexerStr(char *str)
{
    return newReadStr(str);
}

LexerNum LexerAdvance(LexerStr rs)
{
    LexerNum result;
    BOOL isAdvance = TRUE;
    if (current == -1)
        current = rs->advance(rs);
    switch (current)
    {
    case ';':
        result = LEXER_SEMI;
        break;
    case '+':
        result = LEXER_PLUS;
        break;
    case '*':
        result = LEXER_TIMES;
        break;
    case '(':
        result = LEXER_LP;
        break;
    case ')':
        result = LEXER_RP;
        break;
    case '\n':
    case '\t':
    case ' ':
        result = LEXER_WHITE_SPACE;
        break;
    case EOF:
        result = LEXER_EOI;
        break;
    default:
        if (isAlnum(current) == FALSE)
            result = LEXER_UNKNOWN_SYMBOL;
        else
        {
            if (yytext != NULL)
                my_free(yytext);
            yytext = NULL;
            while (current != EOF && isAlnum(current))
            {
                if (yytext == NULL)
                {
                    yytext = my_malloc(2);
                    yytext[0] = current;
                    yytext[1] = '\0';
                }
                else
                {
                    char *str = concatStrAndChar(yytext, current);
                    my_free(yytext);
                    yytext = str;
                }
                current = rs->advance(rs);
            }
            result = LEXER_NUM_OR_ID;
            isAdvance = FALSE;
        }
    }
    lookAhead = result;
    if (isAdvance == TRUE)
        current = rs->advance(rs);
    printf("yytext %s %d \n", yytext, result);
    return result;
}

BOOL LexerMatch(LexerNum type)
{
    return type == lookAhead;
}

char *LexerToken(LexerNum type)
{
    switch (lookAhead)
    {
    case LEXER_EOI:
        return "EOI";
    case LEXER_PLUS:
        return "PLUS";
    case LEXER_TIMES:
        return "TIMES";
    case LEXER_NUM_OR_ID:
        return "NUM_OR_ID";
    case LEXER_SEMI:
        return "SEMI";
    case LEXER_LP:
        return "LP";
    case LEXER_RP:
        return "RP";
    default:
        return "default";
    }
}