#include "stack.h"

#ifndef _LEXICAL_
#define _LEXICAL_
// 程序状态字
enum PSW
{
    PSWdef = 0, // 默认状态 0

    PSWset = 1,      // 碰到字符集正则[xx] 1
    PSWsetESC = 2,   // 碰到字符集正则转义 2
    PSWsetStart = 3, // 字符集遇见- 3

    PSWoptr = 4,       // 操作符状态 4
    PSWsinglechar = 5, // 单字符匹配 5
    PSWESC = 6,
};

typedef struct WholeState
{
    enum PSW state;
} WholeState;

typedef struct NfaNode
{
    char *inputset;         // 字符集
    BOOL visited;           // 是否被访问过 打印
    int stateNum;           // 节点编号
    int anchor;             // 开头含有^ 结尾含有$ 或都有 0 1 2 3
    int edge;               // 记录转换边对应的值  空为 -1 字符集为 -2  没有出去的边为 -3
    struct NfaNode *next;   // 跳转的下一个状态，可为空
    struct NfaNode *next2;  // 跳转的另一个状态，可为空
} NfaNode;

typedef struct NfaPair
{
    struct NfaNode *startNode;
    struct NfaNode *endNode;
} NfaPair;

extern Stack *OPTR;
extern Stack *STNS;
extern WholeState *wholeStatus;
extern NfaPair *rootNfa;
extern NfaPair *nfapaif;
extern int row;
extern int col;
extern int initParse(char *path);
#endif