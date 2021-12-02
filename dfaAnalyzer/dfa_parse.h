#ifndef _DFA_PARSE_
#define _DFA_PARSE_
#include "nfa_Intepretor.h"
#include "dfa_utils.h"
#include "dfa_minimize.h"

typedef struct Dfa_Transfrom_Table
{
    int stateNum;
    int targetNum;
    int c;
} Dfa_Transfrom_Table;

void initDfaParse(NfaPair *nfa);

#endif
