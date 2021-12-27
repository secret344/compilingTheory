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

LexerNum Lexer_advance(Read_Str *rs)
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
    return result;
}

BOOL Lexer_match(LexerNum type)
{
    return type == lookAhead;
}