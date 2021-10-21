#ifndef _LEXICAL_
#define _LEXICAL_

#define BOOL int
#define TRUE 1
#define FALSE 0
#define SUB_NODE_COUNT 26 // 26字母

typedef struct trie
{
    struct trie *next[SUB_NODE_COUNT]; // 字典树子节点
    BOOL isEnd;                        // 字符串是否是结尾
    int loc;                           // 字符串位置(关键字表位置)
} Trie;

extern Trie *create_trie();
extern void insert_trie(Trie *root, char *str[], int len); // 插入字典树
extern BOOL search_word(Trie *root, char *str);            // 查找字典树
extern void traversal_trie(Trie *root);                    // 遍历字典树
extern BOOL delect_trie(Trie *root, char *str);            // 删除字典树
#endif