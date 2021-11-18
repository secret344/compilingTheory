#include "dfa_utils.h"

static int STATE_NUM = 0;

Dfa *getDfaFromNfaSet(Stack *input)
{
    Dfa *dfa = (Dfa *)my_malloc(sizeof(Dfa));
    dfa->nfaStates = new_stack();

    while (stacksize(input))
    {
        NfaNode *nfa = spop(input);
        sPointPush(dfa->nfaStates, nfa);
        // 存在终止nfa节点，修改dfa接收状态
        if (nfa->next == NULL && nfa->next2 == NULL)
        {
            dfa->accepted = TRUE;
        }
    }
    // 序号加一
    dfa->stateNum = STATE_NUM++;
    return dfa;
}