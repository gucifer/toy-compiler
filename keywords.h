//Arpan Parikh 2016A7TS0082
//Pranav Panchumarthi 2017A7PS0153
//Asrita V. Mandalam 2017A7PS1179
#ifndef KEYWORDS
#define KEYWORDS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// typedef enum {
// INTEGER,//0
// REAL,
// BOOLEAN,
// OF,
// ARRAY,
// START,
// END,
// DECLARE,
// MODULE,
// DRIVER,
// PROGRAM,
// RECORD,
// TAGGED,
// UNION,
// GET_VALUE,
// PRINT,
// USE,
// WITH,
// PARAMETERS,
// TRUE,
// FALSE,
// TAKES,
// INPUT,
// RETURNS,
// AND,
// OR,
// FOR,
// IN,
// SWITCH,
// CASE,
// BREAK,
// DEFAULT,
// WHILE,
// PLUS, 
// MINUS, 
// MUL, 
// DIV, 
// LT, 
// LE, 
// GE, 
// GT, 
// EQ, 
// NE, 
// DEF, 
// ENDDEF,
// DRIVERDEF, 
// DRIVERENDDEF,
// COLON, 
// RANGEOP, 
// SEMICOL, 
// COMMA, 
// ASSIGNOP, 
// SQBO, 
// SQBC, 
// BO, 
// BC, 
// COMMENTMARK, 
// ID, 
// NUM, 
// RNUM,
// $,
// E
// } keywords2; //32

int get_keyword(char val[10])
{
	if ((strcmp(val,"INTEGER")==0)||(strcmp(val,"integer")==0))
		return 62;
	else if ((strcmp(val,"REAL")==0)||(strcmp(val,"real")==0))
		return 1;
	else if ((strcmp(val,"BOOLEAN")==0)||(strcmp(val,"boolean")==0))
		return 2;
	else if ((strcmp(val,"OF")==0)||(strcmp(val,"of")==0))
		return 3;
	else if ((strcmp(val,"ARRAY")==0)||(strcmp(val,"array")==0))
		return 4;
	else if ((strcmp(val,"START")==0)||(strcmp(val,"start")==0))
		return 5;
	else if ((strcmp(val,"END")==0)||(strcmp(val,"end")==0))
		return 6;
	else if ((strcmp(val,"DECLARE")==0)||(strcmp(val,"declare")==0))
		return 7;
	else if ((strcmp(val,"MODULE")==0)||(strcmp(val,"module")==0))
		return 8;
	else if ((strcmp(val,"DRIVER")==0)||(strcmp(val,"driver")==0))
		return 9;
	else if ((strcmp(val,"PROGRAM")==0)||(strcmp(val,"program")==0))
		return 10;
	else if ((strcmp(val,"RECORD")==0)||(strcmp(val,"record")==0))
		return 11;
	else if ((strcmp(val,"TAGGED")==0)||(strcmp(val,"tagged")==0))
		return 12;
	else if ((strcmp(val,"UNION")==0)||(strcmp(val,"union")==0))
		return 13;
	else if ((strcmp(val,"GET_VALUE")==0)||(strcmp(val,"get_value")==0))
		return 14;
	else if ((strcmp(val,"PRINT")==0)||(strcmp(val,"print")==0))
		return 15;
	else if ((strcmp(val,"USE")==0)||(strcmp(val,"use")==0))
		return 16;
	else if ((strcmp(val,"WITH")==0)||(strcmp(val,"with")==0))
		return 17;
	else if ((strcmp(val,"PARAMETERS")==0)||(strcmp(val,"parameters")==0))
		return 18;
	else if ((strcmp(val,"TRUE")==0)||(strcmp(val,"true")==0))
		return 19;
	else if ((strcmp(val,"FALSE")==0)||(strcmp(val,"false")==0))
		return 20;
	else if ((strcmp(val,"TAKES")==0)||(strcmp(val,"takes")==0))
		return 21;
	else if ((strcmp(val,"INPUT")==0)||(strcmp(val,"input")==0))
		return 22;
	else if ((strcmp(val,"RETURNS")==0)||(strcmp(val,"returns")==0))
		return 23;
	else if ((strcmp(val,"AND")==0)||(strcmp(val,"and")==0))
		return 24;
	else if ((strcmp(val,"OR")==0)||(strcmp(val,"or")==0))
		return 25;
	else if ((strcmp(val,"FOR")==0)||(strcmp(val,"for")==0))
		return 26;
	else if ((strcmp(val,"IN")==0)||(strcmp(val,"in")==0))
		return 27;
	else if ((strcmp(val,"SWITCH")==0)||(strcmp(val,"switch")==0))
		return 28;
	else if ((strcmp(val,"CASE")==0)||(strcmp(val,"case")==0))
		return 29;
	else if ((strcmp(val,"BREAK")==0)||(strcmp(val,"break")==0))
		return 30;
	else if ((strcmp(val,"DEFAULT")==0)||(strcmp(val,"default")==0))
		return 31;
	else if ((strcmp(val,"WHILE")==0)||(strcmp(val,"while")==0))
		return 32;
	else if ((strcmp(val,"ID")==0)||(strcmp(val,"id")==0))
		return 57; //DONT CHANGE THIS FROM 57
	else if ((strcmp(val,"NUM")==0)||(strcmp(val,"num")==0))
		return 58;	//DONT CHANGE THIS FROM 58
	else if ((strcmp(val,"RNUM")==0)||(strcmp(val,"rnum")==0))
		return 59;	//DONT CHANGE THIS FROM 59
	else
		return -1;
}
/*
int main()
{
     int a;
	char *arr="BREAK";
    a=get_keyword(arr); 
    
    //printf("%d",a);

    return 0;
}
*/
#endif