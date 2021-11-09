#ifndef _FILE_READ_
#define _FILE_READ_
typedef void (*fun_t)(char);

extern int initReadFile(char *path, fun_t cb);
extern int row;
extern int col;

#endif