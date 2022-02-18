﻿#include <stdio.h>
#include <string.h>
#include <time.h>
#include "nfa_parse.h"
#include "nfa_Intepretor.h"
#include "dfa_Intepretor.h"
#include "dfa_parse.h"
#include "read_file.h"
#include "utils.h"
#include "my_map.h"
#include "read_str.h"
#include "pda_parse.h"
#include "parse_table_builder.h"
#include "LRcompiler.h"
#include "LR1compiler.h"

char *regParse(char *str)
{
    char *JsonStr = initParse(str, initReadChar);
    return JsonStr;
}

char *matchStr(char *str)
{
    // initMatchNfa(str);
    
    char *json = initMatchDfa(str);
    return json;
}

char *getDfaJson()
{
    return dfaJsonStr;
}

int main()
{
    printf("加载webassembly模块  \n");
    // LL parser

    // initProductions();
    // stmt -> expr SEMI
    // expr -> term expr’ | ε
    // expr’ -> PLUS term expr’ |ε
    // term -> factor term’
    // term’ -> TIMES factor term’ |ε
    // factor -> LEFT_PAREN expr RIGHT_PAREN | NUMBER

    // FIRST(stmt) = { SEMI , LEFT_PAREN, NUMBER }
    // FIRST(expr) = { LEFT_PAREN, NUMBER }
    // FIRST(expr’) = {PLUS}.
    // FIRST(term) = { LEFT_PAREN, NUMBER }
    // FIRST(term’) = {TIMES}.
    // FIRST(factor) = {LEFT_PAREN, NUMBER}.
    // follow
    // STMT{  }
    // EXPR{ SEMI RIGHT_PARENT  }
    // EXPR_PRIME{ SEMI RIGHT_PARENT  }
    // TERM{ PLUS SEMI RIGHT_PARENT  }
    // TERM_PRIME{ PLUS SEMI RIGHT_PARENT  }
    // FACTOR{ TIMES PLUS SEMI RIGHT_PARENT  }
    // lr分析器
    // LRinitParser();
    // lr1分析器
    LR1initParser();
    return 0;
}
