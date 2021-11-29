#include <stdio.h>
#include <string.h>
#include <time.h>
#include "nfa_parse.h"
#include "nfa_Intepretor.h"
#include "read_file.h"
#include "utils.h"
#include "my_map.h"
// void wait(int seconds)
// {
//     clock_t endwait;
//     endwait = clock() + seconds * CLOCKS_PER_SEC;
//     while (clock() < endwait)
//     {
//     }
// }
char *regParse(char *str)
{
    char *JsonStr = initParse(str, initReadChar);
    return JsonStr;
}

int matchStr(char *str)
{
    initMatchNfa(str);
    return 0;
}

int main()
{
    // int a[] = {16, 1, 5, 33, 67, 2, 1, 8, 5, 65, 0, 23};
    // MapRoot root = new_map(Map_Number);

    // for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); i++)
    // {
    //     setm_number_node(root, a[i], "value");
    // }
    // // char *s = get_number_node(root, 7);
    // // printf("打印 %s \n", s);

    // // remove_number_map(root, 7);
    // // remove_number_map(root, 11);
    // // traversal_map(root);
    // // s = get_number_node(root, 7);
    // // printf("打印 %s 迭代器:\n", s);
    // My_Iterator *itor = new_Map_iterator((RbRoot *)root);
    // RbNodeP n = NULL;
    // printf("迭代器:\n");
    // while (n = (RbNodeP)get_itor_next(itor))
    // {
    //     printf("打印 %d \n", n->key.n);
    // }
    printf("加载webassembly模块 \n");
    return 0;
}
