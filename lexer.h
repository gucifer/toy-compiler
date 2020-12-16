//Arpan Parikh 2016A7TS0082
//Pranav Panchumarthi 2017A7PS0153
//Asrita V. Mandalam 2017A7PS1179
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include "keywords.h"
#ifndef LEXER
#define LEXER
typedef struct {
    int no;
    int lineno;
    int n;                  /* value for constants */
    char *text;             /* text for idents */
    float f;
} token;


token tklist[1000];
token* erlist[100];
int numerr = 0;
char* table[54][62];
extern int tkcount;
extern int line;
extern int tk_count;
extern int er_count;
int tkcount=0;
int line=0;
int tk_count=0;
int er_count=0;
int count = 0;
int last1 = 0;
// int line = 0;
// int tkcount = 0;
// token tklist[];
// int tk_count=0;	
// err erlist[];
// int er_count = 0;
#endif