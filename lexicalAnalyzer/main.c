#include <stdio.h>
#include "lexical.h"

int main()
{
    Trie *root = create_trie();
    char *str[] = {"hello", "world", "xxs", "hell"};
    insert_trie(root, str, (sizeof str / sizeof str[0]));
    BOOL b = search_word(root, "world");
    BOOL c = search_word(root, "hello");
    BOOL d = search_word(root, "hell");
    traversal_trie(root);
    printf("%d%d%d\n", b, c, d);

    delect_trie(root, "hell");
    delect_trie(root, "world");
    traversal_trie(root);
    return 0;
}