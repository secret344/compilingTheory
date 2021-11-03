#include "stack.h"
#ifndef _LEXICAL_
#define _LEXICAL_

typedef struct WholeState
{
    enum PSW state;
} WholeState;

extern Stack *OPTR;
extern Stack *STNS;
extern WholeState *wholeStatus;
extern NfaPair *curNfa;
extern NfaPair *nfapaif;
extern int row;
extern int col;
extern int initParse(char *path);
#endif