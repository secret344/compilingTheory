#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "lexical.h"
#include "utils.h"
#include <time.h>
#include "nfa_Intepretor.h"

void wait(int seconds)
{
    clock_t endwait;
    endwait = clock() + seconds * CLK_TCK;
    while (clock() < endwait)
    {
    }
}

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
    // Trie *root = create_trie();
    // char *str[] = {"auto", "double", "int", "struct", "break", "else", "long",
    //                "switch", "case", "enum", "register", "typedef", "char",
    //                "extern", "return", "union", "const", "float", "short",
    //                "unsigned", "continue", "for", "signed", "void", "default",
    //                "goto", "sizeof", "volatile", "do", "if", "while", "static"};
    // insert_trie(root, str, (sizeof str / sizeof str[0]));
    // BOOL b = search_word(root, "signed");
    // printf("%d", b);
    // STNS = new_stack();
    // OPTR = new_stack();
    // STNS = new_stack();
    // OPTR = new_stack();
    // printf(" %p %p ", STNS, OPTR);
    // spush(STNS, "123");
    // spush(STNS, "123");
    // sdestory(STNS);
    // straversal(OPTR);
    // (ac[a-cA-Z]*[^a-cA-Z]+[a-cA-Z]?ba.a|b*)
    int f = initParse("./reg-test.txt");
    // printf("结束字符 %s", nfapaif->startNode->inputset);
    printfNfa(nfapaif);
    initpretNfa(nfapaif->startNode, "0.1xq");
    initpretNfa(nfapaif->startNode, "9.865241");
    initpretNfa(nfapaif->startNode, "123.656");
    // wait(60);
    return f;
    // if (setpaif->startNode->anchor == 1)
    // {
    //     char *temp = norepe;
    //     norepe = setComplement(temp);
    //     free(temp);
    //     temp = NULL;
    // }
}
//  a | b*
//   1 - 2
// 0       5
//   3 - 4