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
    dfa->accepted = FALSE;

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
    int count = 0;
    int s1 = stacksize(closure);
    Dfa *result = NULL;
    My_Iterator *itor = new_Point_Set_iterator(dfaList);
    // 获取dfa集合迭代器
    while (has_Set_iterator_next(itor))
    {
        count++;
        BOOL is = TRUE;
        Dfa *dfa = getp_Set_iterator_next(itor);
        int s2 = dfa->nfaStates->size;
        if (s1 != s2)
        {
            continue;
        }
        // 判断相等
        My_Iterator *itorNfa = new_Point_Set_iterator(dfa->nfaStates);
        while (has_Set_iterator_next(itorNfa))
        {
            NfaNode *nfa = getp_Set_iterator_next(itorNfa);
            if (stackPointerInclude(closure, nfa) == FALSE)
            {
                is = FALSE;
                break;
            }
        }
        my_iterator_free(itorNfa);

        if (is == TRUE)
        {
            result = dfa;
            break;
        }
    }
    my_iterator_free(itor);
    return result;
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
/**
 * @brief 打印dfa状态转移表
 * 
 */
void printDfaStateTransformTable(int **a, int count)
{
    for (size_t i = 0; i < ASCII_COUNT; i++)
    {
        printf("%c ", i);
        for (size_t j = 0; j < count; j++)
        {
            printf(" %d ", a[i][j]);
        }
        printf("\n");
    }
}
/**
 * @brief 卸载dfa状态转移表
 * 
 * @param a 
 */
void destoryDfaStateTransformTable(int **a)
{
    for (size_t i = 0; i < ASCII_COUNT; i++)
    {
        my_free(a[i]);
    }
    my_free(a);
}

cJSON *DfaToCJson(Dfa *dfa)
{
    cJSON *current = cJSON_CreateObject();

    cJSON *stateNum = cJSON_CreateNumber(dfa->stateNum);
    cJSON *accepted = cJSON_CreateNumber(dfa->accepted);

    cJSON *nfaSet = cJSON_CreateArray();
    My_Iterator *itor = new_Point_Set_iterator(dfa->nfaStates);
    while (has_Set_iterator_next(itor))
    {
        NfaNode *nfa = getp_Set_iterator_next(itor);
        cJSON *nfaStateNum = cJSON_CreateNumber(nfa->stateNum);
        cJSON_AddItemToArray(nfaSet, nfaStateNum);
    }
    my_iterator_free(itor);

    cJSON_AddItemToObject(current, "dfaStateNum", stateNum);
    cJSON_AddItemToObject(current, "accepted", accepted);
    cJSON_AddItemToObject(current, "nfaset", nfaSet);

    return current;
}
/**
 * @brief 状态转移表 json
 * 
 * @param n 
 * @param row  行数
 * @param col  列数
 * @return cJSON* 
 */
cJSON *stateTransformTableToJson(int **a, int row, int col)
{
    cJSON *root = cJSON_CreateArray();
    for (size_t i = 0; i < row; i++)
    {
        cJSON *colJson = cJSON_CreateArray();
        for (size_t j = 0; j < col; j++)
        {
            cJSON *nJson = cJSON_CreateNumber(a[i][j]);
            cJSON_AddItemToArray(colJson, nJson);
        }
        cJSON_AddItemToArray(root, colJson);
    }
    return root;
}