#include "dfa_parse.h"

static NfaPair *nfaMachine = NULL;
static Stack *dfaList = NULL;

void initDfaParse(NfaPair *nfaPair)
{
    nfaMachine = nfaPair;
    dfaList = new_stack();
}

void convertNfaToDfa()
{
    int nextNum = STATE_FAILURE;
    Stack *dfaset = new_stack();
    Stack *input = new_stack();

    sPointPush(input, nfaMachine->startNode);
    Stack *nfaStartClosure = e_closure(input);
    // 开始创建首个dfa节点
    Dfa *start = getDfaFromNfaSet(nfaStartClosure);
    sPointPush(dfaset, start);

    while (stacksize(dfaset))
    {
        Dfa *currentDfa = spop(dfaset);
        sPointPush(dfaList, currentDfa);

        for (size_t i = 0; i < ASCII_COUNT; i++)
        {
            Stack *move = e_move(currentDfa->nfaStates, i);
            if (stacksize(move))
            {
                Stack *closure = e_closure(move);
                // 判断dfaList是否已经存在相应dfa节点
                // TODO
            }
            else
            {
            }
        }
    }
}