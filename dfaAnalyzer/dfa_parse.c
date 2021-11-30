#include "dfa_parse.h"
static void convertNfaToDfa();
static NfaPair *nfaMachine = NULL;
static SetRoot dfaList = NULL;

void initDfaParse(NfaPair *nfaPair)
{
    nfaMachine = nfaPair;
    dfaList = new_Set(Set_Struct);
    convertNfaToDfa();
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
    addp_set(dfaList, start);

    while (stacksize(dfaset))
    {
        Dfa *currentDfa = spop(dfaset);

        for (size_t i = 0; i < ASCII_COUNT; i++)
        {
            Stack *currentState = new_stack();
            set_To_Stack(currentState, currentDfa->nfaStates);
            // 数据格式不同 转为相同格式
            Stack *move = e_move(currentState, i);
            if (stacksize(move))
            {
                Stack *closure = e_closure(move);
                // 判断dfaList是否已经存在相应dfa节点
                Dfa *dfa = isNfaStatesExistInDfa(closure, dfaList);
                if (dfa == NULL)
                {
                    // 不存在 新建dfa节点
                    Dfa *newDfa = getDfaFromNfaSet(closure);
                    nextNum = newDfa->stateNum;
                    addp_set(dfaList, newDfa);
                    // 加入栈 继续循环
                    sPointPush(dfaset, newDfa);
                }
                else
                {
                    // 已经存在相应dfa
                    nextNum = dfa->stateNum;
                }
            }
            else
            {
                nextNum = STATE_FAILURE;
            }
            if (nextNum != STATE_FAILURE)
            {
                printf("DFA from state: %d to state: %d on char: %zu \n", currentDfa->stateNum, nextNum, i);
            }
        }
    }
}