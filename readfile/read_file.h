#ifndef _FILE_READ_
#define _FILE_READ_
typedef void (*fun_t)(char);

int initReadFile(char *content, fun_t cb);
int initReadChar(char *content, fun_t cb);
extern int row;
extern int col;

#endif