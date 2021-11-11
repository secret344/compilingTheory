#ifndef _TRIE_
#define _TRIE_
#include "bool.h"

#define SUB_NODE_COUNT 26 // 26字母

typedef struct Trie
{
    BOOL isEnd;                        // 字符串是否是结尾
    int loc;                           // 字符串位置(关键字表位置)
    struct Trie *next[SUB_NODE_COUNT]; // 字典树子节点
} Trie;

extern Trie *create_trie();
extern void insert_trie(Trie *root, char *str[], int len); // 插入字典树
extern BOOL search_word(Trie *root, char *str);            // 查找字典树
extern void traversal_trie(Trie *root);                    // 遍历字典树
extern BOOL delect_trie(Trie *root, char *str);            // 删除字典树
#endif