#ifndef _TRIE_
#define _TRIE_
#include "bool.h"
#include "memory_management.h"

#define SUB_NODE_COUNT 26 // 26字母

typedef struct Trie
{
    BOOL isEnd;                        // 字符串是否是结尾
    int loc;                           // 字符串位置(关键字表位置)
    struct Trie *next[SUB_NODE_COUNT]; // 字典树子节点
} Trie;

Trie *create_trie();
void insert_trie(Trie *root, char *str[], int len); // 插入字典树
int search_word(Trie *root, char *str);            // 查找字典树
void traversal_trie(Trie *root);                    // 遍历字典树
BOOL delete_trie(Trie *root, char *str);            // 删除字典树
#endif