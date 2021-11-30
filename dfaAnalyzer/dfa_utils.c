#include "dfa_utils.h"

static int STATE_NUM = 0;

void resetStateNum()
{
    STATE_NUM = 0;
}

Dfa *getDfaFromNfaSet(Stack *input)
{
    Dfa *dfa = (Dfa *)my_malloc(sizeof(Dfa));
    dfa->nfaStates = new_Set(Set_Struct);

    while (stacksize(input))
    {
        NfaNode *nfa = spop(input);
        addp_set(dfa->nfaStates, nfa);
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

Dfa *isNfaStatesExistInDfa(Stack *closure, SetRoot dfaList)
{
    int s1 = stacksize(closure);
    My_Iterator *itor = new_Point_Set_iterator(dfaList);
    // 获取dfa集合迭代器
    while (has_Set_iterator_next(itor))
    {
        BOOL is = TRUE;
        Dfa *dfa = getp_Set_iterator_next(itor);
        int s2 = dfa->nfaStates->size;
        if (s1 != s2)
        {
            break;
        }
        // 判断相等
        My_Iterator *itorNfa = new_Point_Set_iterator(dfa->nfaStates);
        while (has_Set_iterator_next(itorNfa))
        {
            NfaNode *nfa = getp_Set_iterator_next(itorNfa);
            if (!stackPointerInclude(closure, nfa))
            {
                is = FALSE;
                break;
            }
        }
        my_iterator_free(itorNfa);
        if (is)
        {
            my_iterator_free(itor);
            return dfa;
        }
    }
    my_iterator_free(itor);
    return NULL;
}

void set_To_Stack(Stack *target, SetRoot source)
{
    My_Iterator *itor = new_Point_Set_iterator(source);
    while (has_Set_iterator_next(itor))
    {
        void *p = getp_Set_iterator_next(itor);
        sPointPush(target, p);
    }
    my_iterator_free(itor);
}