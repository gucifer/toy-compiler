#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lexer.h"
#include "t_nont.h"
#include "parserdef.h"
// struct tree t;
// struct tree* root = &t;

// struct tree* traverseleft()
// {
//     struct tree* node = root;
//     while(node->child[0] != NULL)
//     {
//         node = node->child[0];
//     }
//     return node;
// }
int numastnodes = 0;
int numparsernodes = 0;
struct ast* makeastnode(int no,int ruleno,char type, struct tree* node,struct ast* parent)
{
    struct ast* main = (struct ast*)malloc(sizeof(struct ast));
    main->no = no;
    main->ruleno = ruleno;
    main->type = type;
    main->t = node;
    if(node->tk != NULL)
        main->tk = node->tk;
    main->visited = 0;
    main->next = NULL;
    main->parent = parent;
    main->child = NULL;
}

struct ast* makeast(struct tree* node,struct ast* parent)
{
    struct ast* main = (struct ast*)malloc(sizeof(struct ast));
    struct ast* c;
    main->next = NULL;
    switch(node->ruleno)
    {
        case 0://<program>=<moduleDeclarations><othermodules><driverModule><othermodules>
            main = makeastnode(0,0,'N',node,NULL);
            c = makeast(node->child[0],main);
            if(c==NULL)
            {
            c = makeast(node->child[1],main);
            if(c==NULL)
            {
                c = makeast(node->child[2],main);
                if(c==NULL)
                {
                    c = makeast(node->child[3],main);
                }
                else
                {
                    main->child = c;
                    while(c->next != NULL)
                        c = c->next;
                    c->next = makeast(node->child[3],main);
                }
                
            }
            else
            {
                main->child = c;
                while(c->next != NULL)
                    c = c->next;
                c->next = makeast(node->child[2],main);
                while(c->next != NULL)
                    c = c->next;
                c->next = makeast(node->child[3],main);   
            }
            }
            else
            {            
            main->child = c;
            while(c->next != NULL)
                c = c->next;
            c->next = makeast(node->child[1],main);
            while(c->next != NULL)
                c = c->next;
            c->next = makeast(node->child[2],main);
            while(c->next != NULL)
                c = c->next;
            c->next = makeast(node->child[3],main);
            numastnodes = numastnodes + 1;
            numparsernodes = numparsernodes + 4;
            }
            break;
        case 1://<moduleDeclarations>=<moduleDeclaration><moduleDeclarations>
            main = makeastnode(3,1,'N',node->child[0],parent);
            main->child = makeast(node->child[0],parent);
            main->next = makeast(node->child[1],parent);
            numastnodes = numastnodes + 1;
            numparsernodes = numparsernodes + 2;
            break;
        case 2://<moduleDeclarations>=[E]
            main = NULL;
            break;
        case 3://<moduleDeclaration>=[DECLARE][MODULE][ID][SEMICOL]
            main = makeastnode(3,3,'N',node,parent);
            main->child = makeastnode(DECLARE,3,'t',node->child[0],parent);
            main->child->next = makeastnode(MODULE,3,'t',node->child[1],parent);
            main->child->next->next = makeastnode(ID,3,'t',node->child[2],parent);
            numastnodes = numastnodes + 4;
            numparsernodes = numparsernodes + 4;
            break;
        case 4://<othermodules>=<module><othermodules>
            main = makeastnode(5,4,'N',node->child[0],parent);
            main->child = makeast(node->child[0],parent);
            main->next = makeast(node->child[1],parent);
            numastnodes = numastnodes + 1;
            numparsernodes = numparsernodes + 2;
            break;
        case 5://<othermodules>=[E]
            main = NULL;
            break;
        case 6://<driverModule>=[DRIVERDEF][DRIVER][PROGRAM][ENDDEF]<moduleDef>
            main = makeastnode(DRIVER,6,'t',node->child[1],parent);
            main->child = makeast(node->child[4],main);
            numastnodes = numastnodes + 1;
            numparsernodes = numparsernodes + 5;
            break;
        case 7://<module>=[DEF][MODULE][ID][ENDDEF][TAKES][INPUT][SQBO]<input_plist>[SQBC][SEMICOL]<ret><moduleDef>
            main = makeastnode(MODULE,7,'t',node->child[1],parent);
            main->next = makeastnode(ID,7,'t',node->child[2],parent);
            main->next->next = makeastnode(8,7,'N',node->child[7],parent);
            main->next->next->child = makeast(node->child[7],main);
            c  = main->next;
            while(c->next != NULL)
                c = c->next;
            c->next = makeast(node->child[10],main);
            while(c->next != NULL)
                c = c->next;
            c->next = makeast(node->child[11],main);
            numastnodes = numastnodes + 3;
            numparsernodes = numparsernodes + 12;
            break;
        case 8://<ret>=[RETURNS][SQBO]<output_plist>[SQBC][SEMICOL]
            main = makeastnode(RETURNS,8,'t',node->child[0],parent);
            main->child = makeast(node->child[2],parent);
            numastnodes = numastnodes + 1;
            numparsernodes = numparsernodes + 5;
            break;
        case 9://<ret>=[E]
            main = NULL;
            numparsernodes = numparsernodes + 1;
            break;
        case 10://<input_plist>=[ID][COLON]<datatype><input_plist_rec>
            main = makeastnode(ID,10,'t',node->child[0],parent);
            main->next = makeast(node->child[2],parent);
            main->next->next = makeast(node->child[3],parent);
            numastnodes = numastnodes + 1;
            numparsernodes = numparsernodes + 4;
            break;
        case 11://<input_plist_rec>=[COMMA][ID][COLON]<input_plist_rec>
            main = makeastnode(ID,11,'t',node->child[1],parent);
            main->next = makeast(node->child[3],parent);
            main->next->next = makeast(node->child[4],parent);  
            numastnodes = numastnodes + 1;
            numparsernodes = numparsernodes + 4;
            break;
        case 12://<input_plist_rec>=[E]
            main = NULL;
            numparsernodes = numparsernodes + 1;
            break;
        case 13://<output_plist>=[ID][COLON]<type><output_plist_rec>
            main = makeastnode(ID,13,'t',node->child[0],parent);
            main->next = makeast(node->child[2],parent);
            main->next->next = makeast(node->child[3],parent);
            numastnodes = numastnodes + 1;
            numparsernodes = numparsernodes + 4;
            break;
        case 14://<output_plist_rec>=[COMMA][ID][COLON]<type><output_plist_rec>
            main = makeastnode(ID,14,'t',node->child[1],parent);
            main->next = makeast(node->child[3],parent);
            main->next->next = makeast(node->child[4],parent);  
            numastnodes = numastnodes + 1;
            numparsernodes = numparsernodes + 5;
            break;
        case 15://<output_plist_rec>=[E]
            main = NULL;
            numparsernodes = numparsernodes + 1;
            break;
        case 16://<datatype>=<type>
            main = makeast(node->child[0],parent);
            numparsernodes = numparsernodes + 1;
            break;
        case 17://<datatype>=[ARRAY][SQBO]<range>[SQBC][OF]<type>
            main = makeastnode(ARRAY,17,'t',node->child[0],parent);
            main->next = makeast(node->child[2],parent);
            c = main->next;
            while(c->next != NULL)
                c = c->next;
            c->next = makeast(node->child[5],parent);
            numastnodes = numastnodes + 1;
            numparsernodes = numparsernodes + 6;
            break;
        case 18://<type>=[INTEGER]
            main = makeastnode(INTEGER,18,'t',node->child[0],parent);
            numastnodes = numastnodes + 1;
            numparsernodes = numparsernodes + 1;
            break;
        case 19://<type>=[REAL]
            main = makeastnode(REAL,19,'t',node->child[0],parent);
            numastnodes = numastnodes + 1;
            numparsernodes = numparsernodes + 1;
            break;
        case 20://<type>=[BOOLEAN]
            main = makeastnode(BOOLEAN,20,'t',node->child[0],parent);
            numastnodes = numastnodes + 1;
            numparsernodes = numparsernodes + 1;
            break;
        case 21://<moduleDef>=[START]<statements>[END]
            main = makeastnode(START,21,'t',node->child[0],parent);
            main->next = makeastnode(18,21,'N',node->child[1],parent);
            main->next->child = makeast(node->child[1],main->next);
            main->next->next = makeastnode(END,21,'t',node->child[2],parent);
            numastnodes = numastnodes + 3;
            numparsernodes = numparsernodes + 3;
            break;
        case 22://<statements>=<statement><statements>
            main = makeastnode(57,22,'N',node->child[0],parent);
            main->child = makeast(node->child[0],main);
            main->next = makeast(node->child[1],parent);
            numastnodes = numastnodes + 1;
            numparsernodes = numparsernodes + 2;
            break;
        case 23://<statements>=[E]
            main = NULL;
            numparsernodes = numparsernodes + 1;
            break;
        case 24://<statement>=<ioStmt>
            main = makeast(node->child[0],parent);
            numparsernodes = numparsernodes + 1;
            break;
        case 25://<statement>=<simpleStmt>
            main = makeast(node->child[0],parent);
            numparsernodes = numparsernodes + 1;
            break;
        case 26://<statement>=<declareStmt>
            main = makeast(node->child[0],parent);
            numparsernodes = numparsernodes + 1;
            break;
        case 27://<statement>=<conditionalStmt>
            main = makeast(node->child[0],parent);
            numparsernodes = numparsernodes + 1;
            break;
        case 28://<statement>=<iterativeStmt>
            main = makeast(node->child[0],parent);
            numparsernodes = numparsernodes + 1;
            break;
        case 29://<ioStmt>=[GET_VALUE][BO][ID][BC][SEMICOL]
            main = makeastnode(GET_VALUE,29,'t',node->child[0],parent);
            main->next = makeastnode(ID,29,'t',node->child[2],parent);
            numastnodes = numastnodes + 2;
            numparsernodes = numparsernodes + 5;
            break;
        case 30://<ioStmt>=[PRINT][BO]<var>[BC][SEMICOL]
            main = makeastnode(PRINT,30,'t',node->child[0],parent);
            main->next = makeast(node->child[2],parent);
            numastnodes = numastnodes + 1;
            numparsernodes = numparsernodes + 5;
            break;
        case 31://<boolConstt>=[TRUE]
            main = makeastnode(TRUE,31,'t',node->child[0],parent);
            numastnodes = numastnodes + 1;
            numparsernodes = numparsernodes + 1;
            break;
        case 32://<boolConstt>=[FALSE]
            main = makeastnode(FALSE,32,'t',node->child[0],parent);
            numastnodes = numastnodes + 1;
            numparsernodes = numparsernodes + 1;
            break;
        case 33://<var_id_num>=[ID]<whichId>
            main = makeastnode(ID,33,'t',node->child[0],parent);
            main->next = makeast(node->child[1],parent);
            numastnodes = numastnodes + 1;
            numparsernodes = numparsernodes + 1;
            break;
        case 34://<var_id_num>=<num>
            main = makeast(node->child[0],parent);
            numparsernodes = numparsernodes + 1;
            break;
        case 35://<var_id_num>=<rnum>
            main = makeast(node->child[0],parent);
            numparsernodes = numparsernodes + 1;
            break;
        case 36://<var>=<var_id_num> 
            main = makeast(node->child[0],parent);
            numparsernodes = numparsernodes + 1;
            break;
        case 37://<var>=<boolConstt>
            main = makeast(node->child[0],parent);
            numparsernodes = numparsernodes + 1;
            break;
        case 38://<whichId>=[SQBO][ID][SQBC]
            main = makeastnode(SQBO,38,'t',node->child[0],parent);
            main->next = makeastnode(ID,38,'t',node->child[1],parent);
            main->next->next = makeastnode(SQBC,38,'t',node->child[2],parent);
            numastnodes = numastnodes + 3;
            numparsernodes = numparsernodes + 3;
            break;
        case 39://<whichId>=[E]
            main = NULL;
            numparsernodes = numparsernodes + 1;
            break;
        case 40://<simpleStmt>=<assignmentStmt>
            main = makeast(node->child[0],parent);
            numparsernodes = numparsernodes + 1;
            break;
        case 41://<simpleStmt>=<moduleReuseStmt>
            main = makeast(node->child[0],parent);
            numparsernodes = numparsernodes + 1;
            break;       
        case 42://<assignmentStmt>=[ID]<whichStmt>
            main = makeastnode(ID,42,'t',node->child[0],parent);
            main->next = makeast(node->child[1],parent);
            numastnodes = numastnodes + 1;
            numparsernodes = numparsernodes + 2;
            break;
        case 43://<whichStmt>=<lvalueIDStmt>
            main = makeast(node->child[0],parent);
            numparsernodes = numparsernodes + 1;
            break;      
        case 44://<whichStmt>=<lvalueARRStmt>
            main = makeast(node->child[0],parent);
            numparsernodes = numparsernodes + 1;
            break;  
        case 45://<lvalueIDStmt>=[ASSIGNOP]<expression>[SEMICOL]
            main = makeastnode(ASSIGNOP,45,'t',node->child[0],parent);
            main->next = makeastnode(40,45,'N',node->child[1],parent);
            main->next->child = makeast(node->child[1],parent);
            numastnodes = numastnodes + 2;
            numparsernodes = numparsernodes + 3;
            break;
        case 46://<lvalueARRStmt>=[SQBO]<index_>[SQBC][ASSIGNOP]<expression>[SEMICOL]
            main = makeastnode(SQBO,46,'t',node->child[0],parent);
            main->next = makeast(node->child[1],parent);
            main->next->next = makeastnode(SQBC,46,'t',node->child[2],parent);
            main->next->next->next = makeastnode(ASSIGNOP,46,'t',node->child[3],parent);
            main->next->next->next->next = makeastnode(40,46,'N',node->child[4],parent);
            main->next->next->next->next->child = makeast(node->child[4],parent);  
            numastnodes = numastnodes + 4;
            numparsernodes = numparsernodes + 6;
            break;
        case 47://<index_>=[NUM]
            main = makeastnode(NUM,47,'t',node->child[0],parent);
            numastnodes = numastnodes + 1;
            numparsernodes = numparsernodes + 1;
            break;
        case 48://<index_>=[ID]
            main = makeastnode(ID,48,'t',node->child[0],parent);
            numastnodes = numastnodes + 1;
            numparsernodes = numparsernodes + 1;
            break;  
        case 49://<moduleReuseStmt>=<optional>[USE][MODULE][ID][WITH][PARAMETERS]<idList>[SEMICOL]
            main = makeast(node->child[0],parent);
            c = main;   
            while(c->next != NULL)
                c = c->next;
            c->next = makeastnode(USE,49,'t',node->child[1],parent);
            c = c->next;
            c->next = makeastnode(ID,49,'t',node->child[2],parent);
            c = c->next;
            c->next = makeastnode(WITH,49,'t',node->child[3],parent);
            c = c->next;
            c->next = makeastnode(PARAMETERS,49,'t',node->child[4],parent);
            c = c->next;
            c->next = makeastnode(29,49,'N',node->child[5],parent);
            c->next->child = makeast(node->child[5],c->next);
            numastnodes = numastnodes + 5;
            numparsernodes = numparsernodes + 8;
            break;
        case 50://<optional>=[SQBO]<idList>[SQBC][ASSIGNOP]
            main = makeastnode(SQBO,50,'t',node->child[0],parent);
            c = main;   
            c->next = makeast(node->child[1],parent);
            while (c->next != NULL)
                c = c->next;
            c->next = makeastnode(SQBC,50,'t',node->child[2],parent);
            c->next->next = makeastnode(ASSIGNOP,50,'t',node->child[3],parent);  
            numastnodes = numastnodes + 3;
            numparsernodes = numparsernodes + 4;
            break;
        case 51://<optional>=[E]
            main = NULL;
            numparsernodes = numparsernodes + 1;
            break;
        case 52://<idList>=[ID]<idList_rec>
            main = makeastnode(ID,52,'t',node->child[0],parent);
            main->next = makeast(node->child[1],parent);
            numastnodes = numastnodes + 1;
            numparsernodes = numparsernodes + 2;
            break;
        case 53://<idList_rec>=[COMMA][ID]<idList_rec>
            main = makeastnode(ID,53,'t',node->child[1],parent);
            main->next = makeast(node->child[2],parent);
            numastnodes = numastnodes + 1;
            numparsernodes = numparsernodes + 3;
            break;     
        case 54://<idList_rec>=[E]
            main = NULL;
            numparsernodes = numparsernodes + 1;
            break;
        case 55://<expression>=<aOrBExpr>
            main = makeast(node->child[0],parent);
            numparsernodes = numparsernodes + 1;
            break;
        case 56://<expression>=<U>
            main = makeast(node->child[0],parent);
            numparsernodes = numparsernodes + 1;
            break;
        case 57://<U>=<plus_min><new_NT>
            main = makeast(node->child[0],parent);
            main->next = makeast(node->child[1],parent);
            numparsernodes = numparsernodes + 2;
            break;
        case 58://<new_NT>=[BO]<arithExpr>[BC]
            main = makeastnode(BO,58,'t',node->child[0],parent);
            c = main;   
            c->next = makeast(node->child[1],parent);
            while(c->next != NULL)
                c = c->next;
            c->next = makeastnode(BC,58,'t',node->child[2],parent);
            numastnodes = numastnodes + 2;
            numparsernodes = numparsernodes + 3;
            break;
        case 59://<new_NT>=<var_id_num>
            main = makeast(node->child[0],parent);
            numparsernodes = numparsernodes + 1;
            break;
        case 60://<aOrBExpr>=<AnyTerm><N7>
            main = makeast(node->child[0],parent);
            c = main;   
            while(c->next != NULL)
                c = c->next;
            c->next = makeast(node->child[1],parent);
            numparsernodes = numparsernodes + 2;
            break;
        case 61://<N7>=<logicalOp><AnyTerm><N7>
            main = makeast(node->child[0],parent);
            c = main;   
            while(c->next != NULL)
                c = c->next;
            c->next = makeast(node->child[1],parent);
            while(c->next != NULL)
                c = c->next;
            c->next = makeast(node->child[2],parent);
            while(c->next != NULL)
                c = c->next;
            numparsernodes = numparsernodes + 3;
            break;
        case 62://<N7>=[E]
            main = NULL;
            break;
        case 63://<AnyTerm>=<arithExpr><N8>
            main = makeast(node->child[0],parent);
            c = main;   
            while(c->next != NULL)
                c = c->next;
            c->next = makeast(node->child[1],parent);
            numparsernodes = numparsernodes + 2;
            break;
        case 64://<AnyTerm>=<boolConstt>
            main = makeast(node->child[0],parent);
            numparsernodes = numparsernodes + 1;
            break;
        case 65://<N8>=<relOp><arithExpr>
            main = makeast(node->child[0],parent);
            c = main;   
            while(c->next != NULL)
                c = c->next;
            c->next = makeast(node->child[1],parent);
            numparsernodes = numparsernodes + 2;
            break;
        case 66://<N8>=[E]
            main = NULL;
            break;
        case 67://<arithExpr>=<term><N4>
            main = makeast(node->child[0],parent);
            c = main;   
            while(c->next != NULL)
                c = c->next;
            c->next = makeast(node->child[1],parent);
            numparsernodes = numparsernodes + 2;
            break;
        case 68://<N4>=<plus_min><term><N4>
            main = makeast(node->child[0],parent);
            c = main;   
            while(c->next != NULL)
                c = c->next;
            c->next = makeast(node->child[1],parent);
            while(c->next != NULL)
                c = c->next;
            c->next = makeast(node->child[2],parent);
            while(c->next != NULL)
                c = c->next;
            numparsernodes = numparsernodes + 3;
            break;
        case 69://<N4>=[E]
            main = NULL;
            numparsernodes = numparsernodes + 1;
            break;
        case 70://<term>=<factor><N5>
            main = makeast(node->child[0],parent);
            c = main;   
            while(c->next != NULL)
                c = c->next;
            c->next = makeast(node->child[1],parent);
            numparsernodes = numparsernodes + 2;
            break;
        case 71://<N5>=<mul_div><factor><N5>
            main = makeast(node->child[0],parent);
            c = main;   
            while(c->next != NULL)
                c = c->next;
            c->next = makeast(node->child[1],parent);
            while(c->next != NULL)
                c = c->next;
            c->next = makeast(node->child[2],parent);
            while(c->next != NULL)
                c = c->next;
            numparsernodes = numparsernodes + 3;
            break;
        case 72://<N5>=[E]
            main = NULL;
            break;
        case 73://<factor>=[BO]<aOrBExpr>[BC]
            main = makeastnode(BO,73,'t',node->child[0],parent);
            c = main;   
            c->next = makeast(node->child[1],parent);
            while(c->next != NULL)
                c = c->next;
            c->next = makeastnode(BC,73,'t',node->child[2],parent);
            numastnodes = numastnodes + 2;
            numparsernodes = numparsernodes + 3;
            break;      
        case 74://<factor>=<var_id_num>
            main = makeast(node->child[0],parent);
            numparsernodes = numparsernodes + 1;
            break;
        case 75://<mul_div>=[MUL]
            main = makeastnode(MUL,75,'t',node->child[0],parent);  
            numastnodes = numastnodes + 1;
            numparsernodes = numparsernodes + 1;
            break; 
        case 76://<mul_div>=[DIV]
            main = makeastnode(DIV,76,'t',node->child[0],parent);  
            numastnodes = numastnodes + 1;
            numparsernodes = numparsernodes + 1;
            break;                        
        case 77://<plus_min>=[PLUS]
            main = makeastnode(PLUS,77,'t',node->child[0],parent);  
            numastnodes = numastnodes + 1;
            numparsernodes = numparsernodes + 1;
            break;                        
        case 78://<plus_min>=[MINUS]
            main = makeastnode(MINUS,78,'t',node->child[0],parent);  
            numastnodes = numastnodes + 1;
            numparsernodes = numparsernodes + 1;
            break;                        
        case 79://<relOp>=[LT]
            main = makeastnode(LT,79,'t',node->child[0],parent);  
            numastnodes = numastnodes + 1;
            numparsernodes = numparsernodes + 1;
            break;                        
        case 80://<relOp>=[LE]
            main = makeastnode(LE,80,'t',node->child[0],parent);  
            numastnodes = numastnodes + 1;
            numparsernodes = numparsernodes + 1;
            break;                        
        case 81://<relOp>=[GT]
            main = makeastnode(GT,81,'t',node->child[0],parent);  
            numastnodes = numastnodes + 1;
            numparsernodes = numparsernodes + 1;
            break;                        
        case 82://<relOp>=[GE]
            main = makeastnode(GE,82,'t',node->child[0],parent);  
            numastnodes = numastnodes + 1;
            numparsernodes = numparsernodes + 1;
            break;                        
        case 83://<relOp>=[EQ]
            main = makeastnode(EQ,83,'t',node->child[0],parent);  
            numastnodes = numastnodes + 1;
            numparsernodes = numparsernodes + 1;
            break;                                              
        case 84://<relOp>=[NE]
            main = makeastnode(NE,84,'t',node->child[0],parent);  
            numastnodes = numastnodes + 1;
            numparsernodes = numparsernodes + 1;
            break;                        
        case 85://<logicalOp>=[AND]
            main = makeastnode(AND,85,'t',node->child[0],parent);  
            numastnodes = numastnodes + 1;
            numparsernodes = numparsernodes + 1;
            break;                        
        case 86://<logicalOp>=[OR]
            main = makeastnode(OR,86,'t',node->child[0],parent);  
            numastnodes = numastnodes + 1;
            numparsernodes = numparsernodes + 1;
            break; 
        case 87://<declareStmt>=[DECLARE]<idList>[COLON]<datatype>[SEMICOL]
            main = makeastnode(DECLARE,87,'t',node->child[0],parent);
            c = main;
            while(c->next != NULL)
                c = c->next;
            c->next = makeast(node->child[1],parent);
            while(c->next != NULL)
                c = c->next;
            c->next = makeastnode(COLON,87,'t',node->child[2],parent);
            c->next->next = makeast(node->child[3],parent);
            while(c->next != NULL)
                c = c->next;
            numastnodes = numastnodes + 2;
            numparsernodes = numparsernodes + 5;
            break;    
        case 88://<conditionalStmt>=[SWITCH][BO][ID][BC][START][CASE]<caseStmt><default_>[END]
            main = makeastnode(SWITCH,88,'t',node->child[0],parent);
            c = main;   
            c->next = makeastnode(ID,88,'t',node->child[2],parent);
            c->next->next = makeastnode(START,88,'t',node->child[4],parent);
            c->next->next->next = makeastnode(CASE,88,'t',node->child[5],parent);
            while(c->next != NULL)
                c = c->next;
            c->next = makeast(node->child[6],parent);
            while(c->next != NULL)
                c = c->next;
            c->next = makeast(node->child[7],parent);
            while(c->next != NULL)
                c = c->next;
            c->next = makeastnode(END,88,'t',node->child[8],parent);
            numastnodes = numastnodes + 5;
            numparsernodes = numparsernodes + 9;
            break;    
        case 89://<caseStmt>=<value>[COLON]<statements>[BREAK][SEMICOL]<caseStmt_rec>
            main = makeast(node->child[0],parent);
            c = main;   
            c->next = makeastnode(COLON,89,'t',node->child[1],parent);
            while(c->next != NULL)
                c = c->next;
            c->next = makeast(node->child[2],parent);
            c->next->next = makeastnode(BREAK,89,'t',node->child[3],parent);
            while(c->next != NULL)
                c = c->next;
            c->next = makeast(node->child[5],parent);
            numastnodes = numastnodes + 2;
            numparsernodes = numparsernodes + 6;
            break;  
        case 90://<caseStmt_rec>=[CASE]<value>[COLON]<statements>[BREAK][SEMICOL]<caseStmt_rec>
            main = makeastnode(CASE,90,'t',node->child[0],parent);
            c = main;   
            c->next = makeast(node->child[1],parent);
            while(c->next != NULL)
                c = c->next;
            c->next = makeastnode(COLON,90,'t',node->child[2],parent);
            c->next->next = makeast(node->child[3],parent);
            while(c->next != NULL)
                c = c->next;
            c->next = makeastnode(BREAK,90,'t',node->child[4],parent);
            c->next->next = makeast(node->child[6],parent);
            numastnodes = numastnodes + 1;
            numparsernodes = numparsernodes + 7;
            break;   
        case 91://<caseStmt_rec>=[E]
            main = NULL;
            numparsernodes = numparsernodes + 1;
            break;
        case 92://<default_>=[DEFAULT][COLON]<statements>[BREAK][SEMICOL]
            main = makeastnode(DEFAULT,91,'t',node->child[0],parent);
            c = main;   
            c->next = makeastnode(COLON,90,'t',node->child[1],parent);
            c->next->next = makeast(node->child[2],parent);
            while(c->next != NULL)
                c = c->next;
            c->next = makeastnode(BREAK,90,'t',node->child[3],parent);
            numastnodes = numastnodes + 3;
            numparsernodes = numparsernodes + 5;
            break;   
        case 93://<default_>=[E]
            main = NULL;
            numparsernodes = numparsernodes + 1;
            break;
        case 94://<value>=<num>
            main = makeast(node->child[0],parent);
            numparsernodes = numparsernodes + 1;
            break;
        case 95://<value>=[TRUE]
            main = makeastnode(TRUE,95,'t',node->child[0],parent);
            numastnodes = numastnodes + 1;
            numparsernodes = numparsernodes + 1;
            break;
        case 96://<value>=[FALSE]
            main = makeastnode(FALSE,96,'t',node->child[0],parent);
            numastnodes = numastnodes + 1;
            numparsernodes = numparsernodes + 1;
            break;
        case 97://<iterativeStmt>=[FOR][BO][ID][IN]<range>[BC][START]<statements>[END]
            main = makeastnode(FOR,97,'t',node->child[0],parent);
            c = main;   
            c->next = makeastnode(BO,97,'t',node->child[1],parent);
            c->next->next = makeastnode(ID,97,'t',node->child[2],parent);
            c->next->next->next = makeastnode(IN,97,'t',node->child[3],parent);
            while(c->next != NULL)
                c = c->next;
            c->next = makeast(node->child[4],parent);
            c->next->next = makeastnode(BC,97,'t',node->child[5],parent);
            c->next->next->next = makeastnode(START,97,'t',node->child[6],parent);
            while(c->next != NULL)
                c = c->next;
            c->next = makeast(node->child[7],parent);
            while(c->next != NULL)
                c = c->next;
            c->next = makeastnode(END,97,'t',node->child[8],parent);
            numastnodes = numastnodes + 7;
            numparsernodes = numparsernodes + 9;
            break;  
        case 98://<iterativeStmt>=[WHILE][BO]<aOrBExpr>[BC][START]<statements>[END]
            main = makeastnode(WHILE,98,'t',node->child[0],parent);
            c = main;   
            c->next = makeastnode(BO,98,'t',node->child[1],parent);
            while(c->next != NULL)
                c = c->next;
            c->next = makeast(node->child[2],parent);
            c->next->next = makeastnode(BC,98,'t',node->child[3],parent);
            c->next->next->next = makeastnode(START,98,'t',node->child[4],parent);
            while(c->next != NULL)
                c = c->next;
            c->next = makeast(node->child[5],parent);
            while(c->next != NULL)
                c = c->next;
            c->next = makeastnode(END,98,'t',node->child[6],parent);
            numastnodes = numastnodes + 5;
            numparsernodes = numparsernodes + 7;
            break;        
        case 99://<range>=<index_>[RANGE]<index_>
            main = makeast(node->child[0],parent);
            c = main;   
            while(c->next != NULL)
                c = c->next;
            c->next = makeastnode(RANGE,99,'t',node->child[1],parent);
            c->next->next = makeast(node->child[2],parent);
            numastnodes = numastnodes + 1;
            numparsernodes = numparsernodes + 3;
            break;
        case 100://<num>=<plus_min>[NUM]
            main = makeast(node->child[0],parent);
            c = main;
            while(c->next != NULL)
                c = c->next;
            c->next = makeastnode(NUM,100,'t',node->child[1],parent);
            numastnodes = numastnodes + 1;
            numparsernodes = numparsernodes + 2;
            break;
        case 101://<num>=[NUM]
            main = makeastnode(NUM,101,'t',node->child[0],parent);
            numastnodes = numastnodes + 1;
            numparsernodes = numparsernodes + 1;
            break;
        case 102://<rnum>=<plus_min>[RNUM]
            main = makeast(node->child[0],parent);
            c = main;
            while(c->next != NULL)
                c = c->next;
            c->next = makeastnode(RNUM,102,'t',node->child[1],parent);
            numastnodes = numastnodes + 1;
            numparsernodes = numparsernodes + 2;
            break;
        case 103://<rnum>=[RNUM]
            main = makeastnode(RNUM,103,'t',node->child[0],parent);
            numastnodes = numastnodes + 1;
            numparsernodes = numparsernodes + 1;
            break; 
    }
    if(main != NULL)
        main->parent = parent;
    return main;
}

// void main()
// {
//     struct tree* node; //node is root node
//     makeast(node,NULL);
// }