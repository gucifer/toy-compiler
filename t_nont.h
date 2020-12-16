//Arpan Parikh 2016A7TS0082
//Pranav Panchumarthi 2017A7PS0153
//Asrita V. Mandalam 2017A7PS1179
#include <stdio.h>
#include <string.h>
#ifndef TNONT
#define TNONT


char *terminal_map(int t)
{
	switch(t)
	{
		case 62: return "INTEGER";
			 break;
		case 1: return "REAL";
			 break;
		case 2: return "BOOLEAN";
			 break;
		case 3: return "OF";
			 break;
		case 4: return "ARRAY";
			 break;
		case 5: return "START";
			 break;
		case 6: return "END";
			 break;
		case 7: return "DECLARE";
			 break;
		case 8: return "MODULE";
			 break;
		case 9: return "DRIVER";
			 break;
		case 10: return "PROGRAM";
			 break;
		case 11: return "RECORD";
			 break;
		case 12: return "TAGGED";
			 break;
		case 13: return "UNION";
			 break;
		case 14: return "GET_VALUE";
			 break;
		case 15: return "PRINT";
			 break;
		case 16: return "USE";
			 break;
		case 17: return "WITH";
			 break;
		case 18: return "PARAMETERS";
			 break;
		case 19: return "TRUE_";
			 break;
		case 20: return "FALSE_";
			 break;
		case 21: return "TAKES";
			 break;
		case 22: return "INPUT";
			 break;
		case 23: return "RETURNS";
			 break;
		case 24: return "AND";
			 break;
		case 25: return "OR";
			 break;
		case 26: return "FOR";
			 break;
		case 27: return "IN";
			 break;
		case 28: return "SWITCH";
			 break;
		case 29: return "CASE";
			 break;
		case 30: return "BREAK";
			 break;
		case 31: return "DEFAULT";
			 break;
		case 32: return "WHILE";
			 break;
		case 33: return "PLUS";
			 break;
		case 34: return "MINUS";
			 break;
		case 35: return "MUL";
			 break;
		case 36: return "DIV";
			 break;
		case 37: return "LT";
			 break;
		case 38: return "LE";
			 break;
		case 39: return "GE";
			 break;
		case 40: return "GT";
			 break;
		case 41: return "EQ";
			 break;
		case 42: return "NE";
			 break;
		case 43: return "DEF";
			 break;
		case 44: return "ENDDEF";
			 break;
		case 45: return "DRIVERDEF";
			 break;
		case 46: return "DRIVERENDDEF";
			 break;
		case 47: return "COLON";
			 break;
		case 48: return "RANGE";
			 break;
		case 49: return "SEMICOL";
			 break;
		case 50: return "COMMA";
			 break;
		case 51: return "ASSIGNOP";
			 break;
		case 52: return "SQBO";
			 break;
		case 53: return "SQBC";
			 break;
		case 54: return "BO";
			 break;
		case 55: return "BC";
			 break;
		case 56: return "COMMENTMARK";
			 break;
		case 57: return "ID";
			 break;
		case 58: return "NUM";
			 break;
		case 59: return "RNUM";
			 break;
		case 60: return "$";
			 break;
		case 61: return "E";
			 break;

	}

}

char *nonterminal_map(int t)
{
	switch(t)
	{
		case 0: return "program";
				 break;
		case 1: return "boolConstt";
				 break;
		case 2: return "moduleDeclarations";
				 break;
		case 3: return "moduleDeclaration";
				 break;
		case 4: return "othermodules";
				 break;
		case 5: return "module";
				 break;
		case 6: return "driverModule";
				 break;
		case 7: return "var_id_num";
				 break;
		case 8: return "input_plist";
				 break;
		case 9: return "datatype";
				 break;
		case 10: return "assignmentStmt";
				 break;
		case 11: return "type";
				 break;
		case 12: return "range";
				 break;
		case 13: return "input_plist_rec";
				 break;
		case 14: return "ret";
				 break;
		case 15: return "output_plist";
				 break;
		case 16: return "output_plist_rec";
				 break;
		case 17: return "moduleDef";
				 break;
		case 18: return "statements";
				 break;
		case 19: return "ioStmt";
				 break;
		case 20: return "moduleReuseStmt";
				 break;
		case 21: return "var";
				 break;
		case 22: return "whichId";
				 break;
		case 23: return "simpleStmt";
				 break;
		case 24: return "whichStmt";
				 break;
		case 25: return "optional";
				 break;
		case 26: return "lvalueIDStmt";
				 break;
		case 27: return "lvalueARRStmt";
				 break;
		case 28: return "index_";
				 break;
		case 29: return "idList";
				 break;
		case 30: return "idList_rec";
				 break;
		case 31: return "conditionalStmt";
				 break;
		case 32: return "caseStmt";
				 break;
		case 33: return "caseStmt_rec";
				 break;
		case 34: return "default_";
				 break;
		case 35: return "value";
				 break;
		case 36: return "num";
				 break;
		case 37: return "rnum";
				 break;
		case 38: return "iterativeStmt";
				 break;
		case 39: return "aOrBExpr";
				 break;
		case 40: return "expression";
				 break;
		case 41: return "U";
				 break;
		case 42: return "unary_op";
				 break;
		case 43: return "new_NT";
				 break;
		case 44: return "AnyTerm";
				 break;
		case 45: return "relOp";
				 break;
		case 46: return "logicalOp";
				 break;
		case 47: return "plus_min";
				 break;
		case 48: return "arithExpr";
				 break;
		case 49: return "N7";
				 break;
		case 50: return "term";
				 break;
		case 51: return "term_rec";
				 break;
		case 52: return "factor";
				 break;
		case 53: return "mul_div";
				 break;
		case 54: return "N8";
				 break;
		case 55: return "N4";
				 break;
		case 56: return "N5";
				 break;
		case 57: return "statement";
				 break;
		case 58: return "declareStmt";
				 break;
	}

}

int get_terminal_no(char val[20])
{
    if (strcmp(val,"INTEGER")==0)
    return 62;
else if (strcmp(val,"REAL")==0)
    return 1;
else if (strcmp(val,"BOOLEAN")==0)
    return 2;
else if (strcmp(val,"OF")==0)
    return 3;
else if (strcmp(val,"ARRAY")==0)
    return 4;
else if (strcmp(val,"START")==0)
    return 5;
else if (strcmp(val,"END")==0)
    return 6;
else if (strcmp(val,"DECLARE")==0)
    return 7;
else if (strcmp(val,"MODULE")==0)
    return 8;
else if (strcmp(val,"DRIVER")==0)
    return 9;
else if (strcmp(val,"PROGRAM")==0)
    return 10;
else if (strcmp(val,"RECORD")==0)
    return 11;
else if (strcmp(val,"TAGGED")==0)
    return 12;
else if (strcmp(val,"UNION")==0)
    return 13;
else if (strcmp(val,"GET_VALUE")==0)
    return 14;
else if (strcmp(val,"PRINT")==0)
    return 15;
else if (strcmp(val,"USE")==0)
    return 16;
else if (strcmp(val,"WITH")==0)
    return 17;
else if (strcmp(val,"PARAMETERS")==0)
    return 18;
else if (strcmp(val,"TRUE")==0)
    return 19;
else if (strcmp(val,"FALSE")==0)
    return 20;
else if (strcmp(val,"TAKES")==0)
    return 21;
else if (strcmp(val,"INPUT")==0)
    return 22;
else if (strcmp(val,"RETURNS")==0)
    return 23;
else if (strcmp(val,"AND")==0)
    return 24;
else if (strcmp(val,"OR")==0)
    return 25;
else if (strcmp(val,"FOR")==0)
    return 26;
else if (strcmp(val,"IN")==0)
    return 27;
else if (strcmp(val,"SWITCH")==0)
    return 28;
else if (strcmp(val,"CASE")==0)
    return 29;
else if (strcmp(val,"BREAK")==0)
    return 30;
else if (strcmp(val,"DEFAULT")==0)
    return 31;
else if (strcmp(val,"WHILE")==0)
    return 32;
else if (strcmp(val,"PLUS")==0)
    return 33;
else if (strcmp(val,"MINUS")==0)
    return 34;
else if (strcmp(val,"MUL")==0)
    return 35;
else if (strcmp(val,"DIV")==0)
    return 36;
else if (strcmp(val,"LT")==0)
    return 37;
else if (strcmp(val,"LE")==0)
    return 38;
else if (strcmp(val,"GE")==0)
    return 39;
else if (strcmp(val,"GT")==0)
    return 40;
else if (strcmp(val,"EQ")==0)
    return 41;
else if (strcmp(val,"NE")==0)
    return 42;
else if (strcmp(val,"DEF")==0)
    return 43;
else if (strcmp(val,"ENDDEF")==0)
    return 44;
else if (strcmp(val,"DRIVERDEF")==0)
    return 45;
else if (strcmp(val,"DRIVERENDDEF")==0)
    return 46;
else if (strcmp(val,"COLON")==0)
    return 47;
else if (strcmp(val,"RANGE")==0)
    return 48;
else if (strcmp(val,"SEMICOL")==0)
    return 49;
else if (strcmp(val,"COMMA")==0)
    return 50;
else if (strcmp(val,"ASSIGNOP")==0)
    return 51;
else if (strcmp(val,"SQBO")==0)
    return 52;
else if (strcmp(val,"SQBC")==0)
    return 53;
else if (strcmp(val,"BO")==0)
    return 54;
else if (strcmp(val,"BC")==0)
    return 55;
else if (strcmp(val,"COMMENTMARK")==0)
    return 56;
else if (strcmp(val,"ID")==0)
    return 57;
else if (strcmp(val,"NUM")==0)
    return 58;
else if (strcmp(val,"RNUM")==0)
    return 59;
else if (strcmp(val,"$")==0)
    return 60;
else if (strcmp(val,"E")==0)
    return 61;
else 
    return -1;

}


int get_nonterminal_no(char val[10])
{
    if (strcmp(val,"program")==0)
        return 0;
    else if (strcmp(val,"boolConstt")==0)
        return 1;
    else if (strcmp(val,"moduleDeclarations")==0)
        return 2;
    else if (strcmp(val,"moduleDeclaration")==0)
        return 3;
    else if (strcmp(val,"othermodules")==0)
        return 4;
    else if (strcmp(val,"module")==0)
        return 5;
    else if (strcmp(val,"driverModule")==0)
        return 6;
    else if (strcmp(val,"var_id_num")==0)
        return 7;
    else if (strcmp(val,"input_plist")==0)
        return 8;
    else if (strcmp(val,"datatype")==0)
        return 9;
    else if (strcmp(val,"assignmentStmt")==0)
        return 10;
    else if (strcmp(val,"type")==0)
        return 11;
    else if (strcmp(val,"range")==0)
        return 12;
    else if (strcmp(val,"input_plist_rec")==0)
        return 13;
    else if (strcmp(val,"ret")==0)
        return 14;
    else if (strcmp(val,"output_plist")==0)
        return 15;
    else if (strcmp(val,"output_plist_rec")==0)
        return 16;
    else if (strcmp(val,"moduleDef")==0)
        return 17;
    else if (strcmp(val,"statements")==0)
        return 18;
    else if (strcmp(val,"ioStmt")==0)
        return 19;
    else if (strcmp(val,"moduleReuseStmt")==0)
        return 20;
    else if (strcmp(val,"var")==0)
        return 21;
    else if (strcmp(val,"whichId")==0)
        return 22;
    else if (strcmp(val,"simpleStmt")==0)
        return 23;
    else if (strcmp(val,"whichStmt")==0)
        return 24;
    else if (strcmp(val,"optional")==0)
        return 25;
    else if (strcmp(val,"lvalueIDStmt")==0)
        return 26;
    else if (strcmp(val,"lvalueARRStmt")==0)
        return 27;
    else if (strcmp(val,"index_")==0)
        return 28;
    else if (strcmp(val,"idList")==0)
        return 29;
    else if (strcmp(val,"idList_rec")==0)
        return 30;
    else if (strcmp(val,"conditionalStmt")==0)
        return 31;
    else if (strcmp(val,"caseStmt")==0)
        return 32;
    else if (strcmp(val,"caseStmt_rec")==0)
        return 33;
    else if (strcmp(val,"default_")==0)
        return 34;
    else if (strcmp(val,"value")==0)
        return 35;
    else if (strcmp(val,"num")==0)
        return 36;
    else if (strcmp(val,"rnum")==0)
        return 37;
    else if (strcmp(val,"iterativeStmt")==0)
        return 38;
    else if (strcmp(val,"aOrBExpr")==0)
        return 39;
    else if (strcmp(val,"expression")==0)
        return 40;
    else if (strcmp(val,"U")==0)
        return 41;
    else if (strcmp(val,"unary_op")==0)
        return 42;
    else if (strcmp(val,"new_NT")==0)
        return 43;
    else if (strcmp(val,"AnyTerm")==0)
        return 44;
    else if (strcmp(val,"relOp")==0)
        return 45;
    else if (strcmp(val,"logicalOp")==0)
        return 46;
    else if (strcmp(val,"plus_min")==0)
        return 47;
    else if (strcmp(val,"arithExpr")==0)
        return 48;
    else if (strcmp(val,"N7")==0)
        return 49;
    else if (strcmp(val,"term")==0)
        return 50;
    else if (strcmp(val,"term_rec")==0)
        return 51;
    else if (strcmp(val,"factor")==0)
        return 52;
    else if (strcmp(val,"mul_div")==0)
        return 53;
    else if (strcmp(val,"N8")==0)
        return 54;
    else if (strcmp(val,"N4")==0)
        return 55;
    else if (strcmp(val,"N5")==0)
        return 56;
    else if (strcmp(val,"statement")==0)
        return 57;
    else if (strcmp(val,"declareStmt")==0)
        return 58;
    else
        return -1;
}

// #ifndef t_nont
// #define t_nont
// #include "t_nontDef.h"
// #endif

typedef enum {
	test,//0
	REAL,
	BOOLEAN,
	OF,
	ARRAY,
	START,
	END,
	DECLARE,
	MODULE,
	DRIVER,
	PROGRAM,
	RECORD,
	TAGGED,
	UNION,
	GET_VALUE,
	PRINT,
	USE,
	WITH,
	PARAMETERS,
	TRUE,
	FALSE,
	TAKES,
	INPUT,
	RETURNS,
	AND,
	OR,
	FOR,
	IN,
	SWITCH,
	CASE,
	BREAK,
	DEFAULT,
	WHILE,
	PLUS, 
	MINUS, 
	MUL, 
	DIV, 
	LT, 
	LE, 
	GE, 
	GT, 
	EQ, 
	NE, 
	DEF, 
	ENDDEF,
	DRIVERDEF, 
	DRIVERENDDEF,
	COLON, 
	RANGE, 
	SEMICOL, 
	COMMA, 
	ASSIGNOP, 
	SQBO, 
	SQBC, 
	BO, 
	BC, 
	COMMENTMARK, 
	ID, 
	NUM, 
	RNUM,
	$,
	E, //if nonterminal -> E (aka nothing)
	INTEGER
} keywords; 


typedef enum {
	program,
	nextpart,
	moduleDeclarations,
	moduleDeclaration,
	otherModules,
	module,
	driverModule,
	module_rec,
	input_plist,
	datatype,
	eof_dataType,
	type,
	range,
	input_plist_rec,
	ret,
	output_plist,
	output_plist_rec,
	moduleDef,
	statements,
	ioStmt1,
	ioStmt2,
	var,
	whichId,
	simpleStmt1,
	simpleStmt2,
	simpleStmt3,
	lvalueIDStmt,
	lvalueARRStmt,
	index_, //index giving error hence index_
	idList,
	idList_rec,
	conditionalStmt,
	caseStmt,
	caseStmt_rec,
	default_,  //default giving error hence default_
	value,
	num,
	rnum,
	iterativeStmt1,
	iterativeStmt2,
	expression,
	boolExpr,
	boolExpr_rec,
	arith_rel_expr,
	arith_rel_expr_rec,
	relOp,
	logicalOp,
	plus_min,
	arithExpr,
	arithExpr_rec,
	term,
	term_rec,
	factor,
	mul_div
} NT; 

#endif