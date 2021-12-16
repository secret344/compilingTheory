#ifndef _DFA_PARSE_
#define _DFA_PARSE_
#include "nfa_Intepretor.h"
#include "dfa_utils.h"
#include "dfa_minimize.h"
#include "nfa_parse.h"

typedef struct Dfa_Transfrom_Table
{
    int stateNum;
    int targetNum;
    int c;
} Dfa_Transfrom_Table;

extern SetRoot dfaList;
extern int **dfaStateTransformTable;
extern char *dfaJsonStr;

void dfaParse();
void destoryDfaList(SetRoot dl);
#endif
