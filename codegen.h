#ifndef CODEDEF
#define CODEDEF
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
int flagoptional =1;

char conv[15],tret[15];
int cnmod=0;

char label[15]="label";
int clabel=0;

char reg[15]="reg";
int creg=0;

char outreg[15]="outreg";
int coutreg=0;

char defreg[15]="default";
int cdefreg=0;

int switchstart=0;
int iterswitch=0;

FILE *functiondeffp,*datafp,*bssfp,*textfp,*fp;
#endif
