#ifndef _LEXER_PDA_CPMPILER_
#define _LEXER_PDA_CPMPILER_
#include "read_str.h"
#include "my_str.h"

typedef struct Read_Str_Instance *LexerStr;

typedef enum
{
    LEXER_EOI = 0,
    LEXER_SEMI = 1,
    LEXER_PLUS = 2,
    LEXER_TIMES = 3,
    LEXER_LP = 4,
    LEXER_RP = 5,
    LEXER_NUM_OR_ID = 6,
    LEXER_WHITE_SPACE = 7,
    LEXER_UNKNOWN_SYMBOL = 8,
} LexerNum;

LexerStr newLexerStr(char *str);
char *LexerToken(LexerNum type);
BOOL LexerMatch(LexerNum type);
LexerNum LexerAdvance(LexerStr rs);
#endif