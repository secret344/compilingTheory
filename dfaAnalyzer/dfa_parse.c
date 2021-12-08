#include "dfa_parse.h"
static void convertNfaToDfa();
static void creatDfaStateTransformTable(int count, Stack *dfa_transfrom_table);
static void destoryNull(void *x){};
static void destoryDfaList();
void viewDfaList();

static NfaPair *nfaMachine = NULL;
SetRoot dfaList = NULL;
int **dfaStateTransformTable;

void initDfaParse(NfaPair *nfaPair)
{
    // 生成dfa状态转移表结束 清理dfa节点
    if (dfaList != NULL)
        destoryDfaList();
    // 清理dfa复杂状态转移表
    if (dfaStateTransformTable != NULL)
        destoryDfaStateTransformTable(dfaStateTransformTable);

    dfaList = NULL;
    dfaStateTransformTable = NULL;
    resetStateNum();

    nfaMachine = nfaPair;
    dfaList = new_Set(Set_Struct);
    convertNfaToDfa();
    // viewDfaList();
    MinimizeDFA();
}

void convertNfaToDfa()
{
    int nextNum = STATE_FAILURE;
    int dfacount = 0; // 记录dfa节点数量

    Stack *dfa_transfrom_table = new_stack(); // dfa状态转移表
    Stack *dfaset = new_stack();              // dfa集合栈
    Stack *input = new_stack();

    sPointPush(input, nfaMachine->startNode);
    Stack *nfaStartClosure = e_closure(input);

    // 开始创建首个dfa节点
    Dfa *start = getDfaFromNfaSet(nfaStartClosure);
    sdestory(nfaStartClosure, NULL);

    sPointPush(dfaset, start);
    addp_set(dfaList, start);
    while (stacksize(dfaset))
    {
        dfacount++;
        Dfa *currentDfa = spop(dfaset);
        for (int i = 0; i < ASCII_COUNT; i++)
        {
            Stack *currentState = new_stack();
            set_To_Stack(currentState, currentDfa->nfaStates);
            // 数据格式不同 转为相同格式
            Stack *move = e_move(currentState, (char)i);
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
                sdestory(closure, destoryNull);
            }
            else
            {
                nextNum = STATE_FAILURE;
                sdestory(move, NULL);
            }

            Dfa_Transfrom_Table *t = my_malloc(sizeof(Dfa_Transfrom_Table));
            t->stateNum = currentDfa->stateNum;
            t->targetNum = nextNum;
            t->c = i;
            sPointPush(dfa_transfrom_table, t);
        }
    }

    sdestory(dfaset, destoryNull);
    // 生成dfa状态转移表
    creatDfaStateTransformTable(dfacount, dfa_transfrom_table);
    sdestory(dfa_transfrom_table, NULL);
}

void creatDfaStateTransformTable(int count, Stack *dfa_transfrom_table)
{
    if (count <= 0)
        return;
    // 动态创建二维数组
    int **a = (int **)my_calloc(ASCII_COUNT, sizeof(int *));
    for (size_t i = 0; i < ASCII_COUNT; i++)
        a[i] = (int *)my_calloc(count, sizeof(int));

    while (stacksize(dfa_transfrom_table))
    {
        Dfa_Transfrom_Table *d = spop(dfa_transfrom_table);
        a[d->c][d->stateNum] = d->targetNum;
        my_free(d);
    }
    // printDfaStateTransformTable(a, count);
    dfaStateTransformTable = a;
}

void destoryDfaList()
{
    My_Iterator *itor = new_Point_Set_iterator(dfaList);
    while (has_Set_iterator_next(itor))
    {
        Dfa *dfa = getp_Set_iterator_next(itor);
        set_destory(dfa->nfaStates, NULL);
        my_free(dfa);
    }
    my_iterator_free(itor);
    set_destory(dfaList, NULL);
}

static void realSize(RbNodeP root, int lr, int pn)
{
    if (root == NULL)
    {
        return;
    }

    int num = root->key.n;
    Dfa *value = root->value;
    RbNodeP p = root->parent;
    if (p != NULL)
    {
        int nump = p->key.n;
        Dfa *pv = p->value;
        printf(" 父亲 %d  方向%d \n", pv->stateNum, lr);
    }

    // printf(" 父亲 %d  方向%d \n", pn, lr);
    printf(" 我自己 %d %d  %d \n\n", root, value->stateNum, root->isRed);
    if (root->left != NULL)
    {
        realSize(root->left, 1, num);
    }
    if (root->right != NULL)
    {
        realSize(root->right, 2, num);
    }
}

void viewDfaList()
{
    My_Iterator *itor = new_Point_Set_iterator(dfaList);
    realSize(dfaList->node, 0, 0);
    while (has_Set_iterator_next(itor))
    {
        Dfa *dfa = getp_Set_iterator_next(itor);
        printf("打印 %d %d \n", dfa->stateNum, dfa->accepted);
    }
    my_iterator_free(itor);
}
