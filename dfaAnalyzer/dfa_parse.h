#ifndef _DFA_PARSE_
#define _DFA_PARSE_
#include "nfa_Intepretor.h"
#include "dfa_interface.h"
#include "dfa_utils.h"

typedef struct Dfa_Transfrom_Table
{
    int stateNum;
    int targetNum;
    int c;
} Dfa_Transfrom_Table;

extern void initDfaParse(NfaPair *nfa);

#endif