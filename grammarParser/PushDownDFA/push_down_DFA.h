#ifndef _PUSH_DOWN_DFA_
#define _PUSH_DOWN_DFA_
#include "lex_stack.h"
#include "read_str.h"
#include "utils.h"

typedef enum
{
    PUSH_1,
    POP,
    ERROR,
    ACCEPT
} StateAction;
void initPushDownDfa();
#endif