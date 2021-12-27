#include "push_down_DFA.h"
static void initTransformTable();
static void recognizeParenthese();
void historyChar(char c);
int getColumnForInputChar(char c);
void takeAction(StateAction action);

static Stack *pushDownStack = NULL;
static StateAction **dfaTransformTable = NULL;
static BOOL lastAccept = FALSE;
static Read_Str *input = NULL;
static char *receive = NULL;

static const int STATE_0 = 0;
static const int STATE_1 = 1;
// 压栈有限状态自动机 初始学习
void initPushDownDfa()
{
    lastAccept = FALSE;
    pushDownStack = new_stack();
    input = newReadStr("(()(()))");
    initTransformTable();
    sPointPush(pushDownStack, STATE_0);
    recognizeParenthese();
    printf("匹配结果 %d \n", lastAccept);
}

void recognizeParenthese()
{
    char c;
    while (TRUE)
    {
        c = input->advance(input);
        // 跳过
        if (c == '\n')
        {
            c = (char)input->advance(input);
            continue;
        }
        historyChar(c);
        int column = getColumnForInputChar(c);
        int topStackSymbol = (int)speek(pushDownStack);
        StateAction action = dfaTransformTable[topStackSymbol][column];
        takeAction(action);
        if (c == EOF)
        {
            break;
        }
    }
}

int getColumnForInputChar(char c)
{
    switch (c)
    {
    case '(':
        return 0;
    case ')':
        return 1;
    case EOF:
        return 2;
    default:
        // 默认异常退出
        exit(1);
        return -1;
    }
}

void takeAction(StateAction action)
{
    switch (action)
    {
    case PUSH_1:
        printf("take action by push state 1\n");
        sPointPush(pushDownStack, STATE_1);
        break;
    case POP:
        printf("take action by pop state from stack\n");
        spop(pushDownStack);
        break;
    case ERROR:
        printf("Error! The input string can not be accepted\n");
        exit(1);
        break;
    case ACCEPT:
        printf("DFA go into accept state\n");
        lastAccept = TRUE;
        break;
    }
}

void initTransformTable()
{
    dfaTransformTable = (int **)my_malloc((2) * sizeof(int *));
    for (int i = 0; i < 2; i++)
    {
        dfaTransformTable[i] = (int *)my_malloc((4) * sizeof(int));
        for (int j = 0; j < 4; j++)
        {
            dfaTransformTable[i][j] = 0;
        }
    }
    dfaTransformTable[0][0] = PUSH_1;
    dfaTransformTable[0][1] = ERROR;
    dfaTransformTable[0][2] = ACCEPT;
    dfaTransformTable[1][0] = PUSH_1;
    dfaTransformTable[1][1] = POP;
    dfaTransformTable[1][2] = ERROR;
}

void historyChar(char c)
{
    if (receive == NULL)
    {
        receive = my_malloc(2);
        receive[0] = c;
        receive[1] = '\0';
    }
    else
    {
        char *temp = my_malloc(2);
        temp[0] = c;
        temp[1] = '\0';
        char *p = concatstr(receive, temp);
        my_free(temp);
        my_free(receive);
        receive = p;
    }
    if (c == EOF && receive != NULL)
    {
        my_free(receive);
        receive = "EOF";
    }
    printf("receive char: %s \n", receive);
}