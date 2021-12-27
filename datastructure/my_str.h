#ifndef _MY_STR_
#define _MY_STR_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "memory_management.h"
#include "bool.h"
#define ASCII_COUNT 128
BOOL findChar(char s, char str[]);
char *getSetLetter(char a, char b);
char *concatstr(char *target, char *source);
char *concatStrAndChar(char *target, char source);
char *noStrRepetition(char *str);
char *setComplement(char *str);
#endif