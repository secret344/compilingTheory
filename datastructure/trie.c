#include "trie.h"
#include <stdio.h>
#include <string.h>

Trie *create_trie()
{
    Trie *trie = my_malloc(sizeof(Trie));
    trie->isEnd = FALSE;
    for (int i = 0; i < SUB_NODE_COUNT; i++)
    {
        trie->next[i] = NULL;
    }
    return trie;
}

void insert_trie_entity(Trie *root, char *str, int loc)
{
    while (*str != '\0')
    {
        char c = *str++;
        int id = c - 'a';

        if (root->next[id] == NULL)
        {
            root->next[id] = create_trie();
        }
        root = root->next[id];
    }
    root->isEnd = TRUE;
    root->loc = loc;
}

void insert_trie(Trie *root, char *str[], int len)
{
    for (int i = 0; i < len; i++)
    {
        insert_trie_entity(root, str[i], i);
    };
}

int search_word(Trie *root, char *str)
{
    char *new_str = my_malloc(strlen(str) + 1);
    int count = 0;
    while (*str != '\0')
    {
        char c = *str++;
        int id = c - 'a';
        if (root->next[id] == NULL)
        {
            return -1;
        }
        root = root->next[id];
        new_str[count++] = id + 'a';
    }
    if (root->isEnd)
    {
        new_str[count] = '\0';
        printf("找到的字符串 %s\n", new_str);
        return root->loc;
    }
    else
    {
        return -1;
    }
}

void traversal(Trie *root, char *str)
{
    if (root == NULL)
    {
        return;
    }
    int len = strlen(str);
    char *new_str = my_malloc(len + 1);
    strcpy(new_str, str);

    if (root->isEnd)
    {
        char *new_str_result = my_malloc(len + 2);
        strcpy(new_str_result, new_str);
        printf("traversal找到的字符串 %s\n", new_str_result);
        my_free(new_str_result);
        new_str_result = NULL;
    }

    for (int i = 0; i < SUB_NODE_COUNT; i++)
    {
        new_str[len] = i + 'a';
        traversal(root->next[i], new_str);
    }
    my_free(new_str);
    new_str = NULL;
}

void traversal_trie(Trie *root)
{
    traversal(root, "");
}

int hasChild(Trie *root)
{
    for (int i = 0; i < SUB_NODE_COUNT; i++)
    {
        if (root->next[i] != NULL)
        {
            return TRUE;
        }
    }
    return FALSE;
}

BOOL delete_trie(Trie *root, char *str)
{
    int len = strlen(str);
    int first_index = str[0] - 'a';
    if (root->next[first_index] == NULL)
    {
        return FALSE;
    }
    if (len == 1)
    {
        if (root->next[first_index]->isEnd)
        {
            if (hasChild(root->next[first_index]))
            {
                root->next[first_index]->isEnd = FALSE;
            }
            else
            {
                my_free(root->next[first_index]);
                root->next[first_index] = NULL;
            }
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    int flag = delete_trie(root->next[first_index], str + 1);
    // 深度优先
    if (!hasChild(root->next[first_index]) && !root->next[first_index]->isEnd)
    {
        my_free(root->next[first_index]);
        root->next[first_index] = NULL;
    }

    return flag;
}