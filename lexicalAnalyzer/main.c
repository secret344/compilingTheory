#include <stdio.h>
#include "trie.h"
#include "lexical.h"
#include <malloc.h>
#include <string.h>
#include "stack.h"
int main()
{
    // Trie *root = create_trie();
    // char *str[] = {"hello", "world", "xxs", "hell"};
    // insert_trie(root, str, (sizeof str / sizeof str[0]));
    // BOOL b = search_word(root, "world");
    // BOOL c = search_word(root, "hello");
    // BOOL d = search_word(root, "hell");
    // traversal_trie(root);
    // printf("%d%d%d\n", b, c, d);

    // delect_trie(root, "hell");
    // delect_trie(root, "world");
    // traversal_trie(root);
    Trie *root = create_trie();
    char *str[] = {"auto", "double", "int", "struct", "break", "else", "long",
                   "switch", "case", "enum", "register", "typedef", "char",
                   "extern", "return", "union", "const", "float", "short",
                   "unsigned", "continue", "for", "signed", "void", "default",
                   "goto", "sizeof", "volatile", "do", "if", "while", "static"};
    // insert_trie(root, str, (sizeof str / sizeof str[0]));
    // BOOL b = search_word(root, "signed");
    // printf("%d", b);

    // int f = initParse("./reg-test.txt");
    // printf("结束%d", f);

    PStack stack;
    new_stack(stack);
    push(stack, "1111");
    push(stack, "7q");
    push(stack, "8d");

    StackNodeSymbol s = "def";
    pop(stack, s);
    printf("出栈: %s\n", s);
    pop(stack, s);
    printf("出栈: %s\n", s);
    pop(stack, s);
    printf("出栈: %s\n", s);

    return 0;
}