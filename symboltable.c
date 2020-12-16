//create error file

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include "lexer.h"
#include "t_nont.h"
#include "parserdef.h"
int getvalue(char* str)
{
    int result = 0;
    int len = strlen(str);
    while ((*str >= '0') && (*str <= '9')&& *str)
    {
        result = (result * 10) + ((*str) - '0');
        str++;
    }
    return result;
}
int returntype(char* a, struct symTable* p)
{
    for(int i=0;i<p->entries;i++)
    {
        if(*p->t[i]->name == *a)
        {
            return p->t[i]->type;
        }
    }
    struct symTable* s = p->prev;
    for(int i=0;i<s->entries;i++)
    {
        if(*s->t[i]->name == *a)
        {
            return s->t[i]->type;
        }
    }    
    
    return -1;
}
struct ast* addentry(struct ast* pass,struct symTable* parent)
{
    pass->s = parent;
    struct ast* currast;
    struct tableentry* t = (struct tableentry*)malloc(sizeof(struct tableentry));
    t->name = pass->tk->text;
    t->offset = parent->offset;
    t->type = 0;
    t->name = pass->tk->text;
    t->scope = parent->name;
    currast = pass->next;
    currast->s = parent;
    int offset = 1;
    if(currast->no == ARRAY)
    {
        if(currast->next->no == NUM)
        {
            t->lower = currast->next->tk->n;
            currast->next->s = parent;
            currast->next->next->s = parent;
            currast = currast->next->next->next;
            currast->s = parent;
            t->upper = currast->tk->n;
            t->type = 10;
            currast = currast->next;
            currast->s = parent;
            offset = t->upper - t->lower;
        }
        else
        {
            
        }
        
    }
    if(currast->no == REAL)
    {
        t->type = t->type+3;
        offset = offset*SIZEOFREAL;
    }
    else if(currast->no == INTEGER)
    {
        t->type = t->type + 2;
        offset = offset*SIZEOFNUM;
    }
    else if(currast->no == BOOLEAN)
    {
        t->type = t->type + 4;
        offset = offset*SIZEOFBOOL;
    }
    if(t->type > 9)
    {
        arrays[numarrays] = t;
        numarrays = numarrays + 1;
    }
    variables[numvariables] = t;
    numvariables = numvariables + 1;
    parent->t[parent->entries] = t;
    parent->entries = parent->entries + 1;
    parent->offset = parent->offset + offset;
    return currast;
}

struct ast* addsingleentry (struct ast* pass,struct symTable* parent,int type,int start,int end)
{
    //same as addentry
    pass->s = parent;
    struct tableentry* t = (struct tableentry*)malloc(sizeof(struct tableentry));
    t->name = pass->tk->text;
    t->offset = parent->offset;
    t->scope = parent->name;
    t->type = type;
    t->lower = start;
    t->upper = end;
    if (type%10 == 2)
    {
        parent->offset = parent->offset + SIZEOFNUM*(end-start+1);
    }
    else if(type%10 == 3)
    {
        parent->offset = parent->offset + SIZEOFREAL*(end-start+1);
    }
    else if(type%10 == 4)
    {
        parent->offset = parent->offset + SIZEOFBOOL*(end-start+1);
    }
    if(t->type > 9)
    {
        arrays[numarrays] = t;
        numarrays = numarrays + 1;
    }
    parent->t[parent->entries] = t;
    parent->entries = parent->entries + 1;
    variables[numvariables] = t;
    numvariables = numvariables + 1;
    return pass;
}


int i=0;//global

int lookpres(char* name,struct symTable* parent)
{
    int ispresent = -1;                     //not there
    for( i = 0;i<parent->entries;i++)
    {
        if(*parent->t[i]->name == *name)
        {    
            ispresent = 1;                  //there
            break;
        }
    }
    if(ispresent == -1)
    {
        struct symTable* s = parent->prev;
        for( i = 0;i<s->entries;i++)
        {
            if(*s->t[i]->name == *name)
            {
                ispresent = 0;              //there but
                break;
            }    
        }
    }
    return ispresent;
    //return i;   //return type
}

struct symTable* createparent()
{
    struct symTable* parent= (struct symTable*)malloc(sizeof(struct symTable));
    parent->entries=0;
    for(int j=0;j<20;j++)
    {
        parent->next[j]=NULL;
    }
    parent->offset=0;
    parent->prev=NULL;
    return parent;
}


void semanalyzer(struct ast* pass, struct symTable* parent)
{
    switch(pass->ruleno)
    {
        struct ast* currast;
        struct ast* t;
        struct symTable* s;//= (struct symTable*)malloc(sizeof(struct symTable));
        char* temp;// = (char *)malloc((strlen("DRIVER")+1)*sizeof(char));
        int ispresent;
        int count;
        int type;
        case 0://<program>=<moduleDeclarations><othermodules><driverModule><othermodules>
            currast = pass->child;
            while(currast != NULL)
            {
                semanalyzer(currast,parent);
                currast = currast->next;
            }
            break;
        case 1://<moduleDeclarations>=<moduleDeclaration><moduleDeclarations>
            currast = pass->child;
            semanalyzer(currast,parent);
            currast = pass->next;
            break;
        case 2://<moduleDeclarations>=[E]
            break;
        case 3://<moduleDeclaration>=[DECLARE][MODULE][ID][SEMICOL]
            break;
        case 4://<othermodules>=<module><othermodules>
            currast = pass;
            semanalyzer(pass->child,parent);
            if(pass->next->ruleno == 4)
                semanalyzer(pass->next,parent);
            break;
        case 5://<othermodules>=[E]
            break;
        case 6://<driverModule>=[DRIVERDEF][DRIVER][PROGRAM][ENDDEF]<moduleDef>
            s = (struct symTable*)malloc(sizeof(struct symTable));
            temp = (char *)malloc((strlen("DRIVER")+1)*sizeof(char));
            temp = "DRIVER";
            s->entries = 0;
            s->name = temp;
            s->offset = 0;
            pass->s = s;
            for(int j =0;j<20;j++)
            {    
                if(parent->next[j] == NULL)
                {
                    parent->next[j] = s;
                    s->prev = parent;
                    break;
                }
            }
            symlist[numsym] = s;
            numsym = numsym + 1;
            semanalyzer(pass->child,s);
            break;
        case 7://<module>=[DEF][MODULE][ID][ENDDEF][TAKES][INPUT][SQBO]<input_plist>[SQBC][SEMICOL]<ret><moduleDef>
             s = (struct symTable*)malloc(sizeof(struct symTable));
            // for(int i =0;i<20;i++)
            //     s->name[i] = pass->tk->text[i];
            s->name = pass->next->tk->text;
            s->offset = 0;
            s->entries = 0;
            currast = pass->next->next;
            struct module* m = (struct module*)malloc(sizeof(struct module));
            m->name = pass->next->tk->text;
            for(int i =0;i<20;i++)
            {    if(parent->next[i] == NULL)
                 {   parent->next[i] = s;
                    s->prev = parent;
                    break;
                 }
            }
            t = currast->child;
            count = 0;
            while (t->next != NULL)
            {
                count = count + 1;
                t = t->next;
            }
            m->inp = count/2;
            t = currast ->next;
            count = 0;
            while (t->next->ruleno != 21)
            {
                count = count + 1;
                t = t->next;
            }
            m->out = (count-1)/2;
            modulelist[nmod] = m;
            symlist[numsym] = s;
            numsym = numsym + 1;
            semanalyzer(currast->child,s);
            semanalyzer(currast->next,s);
            //semanalyzer(currast->next->next,s);
            break;
        case 8://<ret>=[RETURNS][SQBO]<output_plist>[SQBC][SEMICOL]
            semanalyzer(pass->child,parent);
            semanalyzer(pass->next,parent);
            break;
        case 9://<ret>=[E]
            break;
        case 10://<input_plist>=[ID][COLON]<datatype><input_plist_rec>
            currast = addentry(pass,parent);
            semanalyzer(currast->next,parent);
            break;
        case 11://<input_plist_rec>=[COMMA][ID][COLON]<datatype><input_plist_rec>
            currast = addentry(pass,parent);
            if(currast->next != NULL)
                semanalyzer(currast->next,parent);
            break;
        case 12://<input_plist_rec>=[E]
            break;
        case 13://<output_plist>=[ID][COLON]<type><output_plist_rec>
            currast = addentry(pass,parent);
            semanalyzer(currast->next,parent);
            break;
        case 14://<output_plist_rec>=[COMMA][ID][COLON]<type><output_plist_rec>
            currast = addentry(pass,parent);
            if(currast->next != NULL)
                semanalyzer(currast->next,parent);
            break;
        case 15://<output_plist_rec>=[E]
            break;
        case 16://<datatype>=<type>
            break;
        case 17://<datatype>=[ARRAY][SQBO]<range>[SQBC][OF]<type>
            // main = makeastnode(ARRAY,17,'t',node->child[0],parent);
            // main->next = makeast(node->child[2],parent);
            // main->next->next = makeast(node->child[5],parent);
            break;
        case 18://<type>=[INTEGER]
            break;
        case 19://<type>=[REAL]
            break;
        case 20://<type>=[BOOLEAN]
            break;
        case 21://<moduleDef>=[START]<statements>[END]
            s = (struct symTable*)malloc(sizeof(struct symTable));
            // for(int i =0;i<20;i++)
            //     s->name[i] = pass->tk->text[i];
            temp = (char *)malloc((strlen("START")+1)*sizeof(char));
            temp = "START";
            s->name = temp;
            s->offset = 0;
            s->entries = 0;
            for(int i =0;i<20;i++)
            {    if(parent->next[i] == NULL)
                 {  parent->next[i] = s;
                    s->prev = parent;
                    break;
                 }
            }
            pass->s = s;
            semanalyzer(pass->next->child,s);
            symlist[numsym] = s;
            numsym = numsym + 1;
            break;
        case 22://<statements>=<statement><statements>
            pass->s = parent;
            semanalyzer(pass->child,parent);
            if(pass->next != NULL)
                if(pass->next->ruleno == 22)
                    semanalyzer(pass->next,parent);
            break;
        case 23://<statements>=[E]
            break;
        case 24://<statement>=<ioStmt>
            break;
        case 25://<statement>=<simpleStmt>
            break;
        case 26://<statement>=<declareStmt>
            break;
        case 27://<statement>=<conditionalStmt>
            break;
        case 28://<statement>=<iterativeStmt>
            break;
        case 29://<ioStmt>=[GET_VALUE][BO][ID][BC][SEMICOL]
            pass->s = parent;
            pass->next->s = parent;
            ispresent = lookpres(pass->next->tk->text,parent);
            if(ispresent == -1)
            {    
                erlist[numerr] = pass->next->tk;
                numerr = numerr + 1;
            }
            break;
        case 30://<ioStmt>=[PRINT][BO]<var>[BC][SEMICOL]
            pass->s = parent;
            semanalyzer(pass->next,parent);
            break;
        case 31://<boolConstt>=[TRUE]
            break;
        case 32://<boolConstt>=[FALSE]
            break;
        case 33://<var_id_num>=[ID]<whichId>
            pass->s = parent;
            ispresent = lookpres(pass->tk->text,parent);
            if(ispresent == -1)
            {    
                erlist[numerr] = pass->tk;
                numerr = numerr + 1;
            }
            if(pass->next != NULL)
                semanalyzer(pass->next,parent);
            break;
        case 34://<var_id_num>=<num>
            break;
        case 35://<var_id_num>=<rnum>
            break;
        case 36://<var>=<var_id_num> 
            break;
        case 37://<var>=<boolConstt>
            break;
        case 38://<whichId>=[SQBO][ID][SQBC]
            pass->s = parent;
            pass->next->s = parent;
            pass->next->next->s = parent;
            currast = pass->next->next;
            ispresent = lookpres(pass->next->tk->text,parent);
            if(ispresent == -1)
            {    
                erlist[numerr] = pass->next->tk;
                numerr = numerr + 1;
            }
            semanalyzer(currast->next,parent);
            break;
        case 39://<whichId>=[E]
            break;
        case 40://<simpleStmt>=<assignmentStmt>
            break;
        case 41://<simpleStmt>=<moduleReuseStmt>
            break;       
        case 42://<assignmentStmt>=[ID]<whichStmt>
            t = pass;
            type = returntype(pass->tk->text,parent);
            int tp = 0;
            while (t->next != NULL)
            {
                if ((t->type == 't')&& (t->no == ID))
                {
                    if(t->ruleno != 48)
                    {
                        if(returntype(t->tk->text,parent) != type)
                            tp = -1;
                    }
                    else
                    {
                        if(returntype(t->tk->text,parent) != 2)
                            tp = -1;
                    }
                    if (tp == -1)
                        break;
                }
                t = t->next;
            }
            pass->s = parent;
            ispresent = lookpres(pass->tk->text,parent);
            if(ispresent == -1)
            {    
                erlist[numerr] = pass->next->tk;
                numerr = numerr + 1;
            }
            semanalyzer(pass->next,parent);
            break;
        case 43://<whichStmt>=<lvalueIDStmt>
            break;      
        case 44://<whichStmt>=<lvalueARRStmt>
            break;  
        case 45://<lvalueIDStmt>=[ASSIGNOP]<expression>[SEMICOL]
            pass->s = parent;
            pass->next->s = parent;
            semanalyzer(pass->next->child,parent);
            break;
        case 46://<lvalueARRStmt>=[SQBO]<index_>[SQBC][ASSIGNOP]<expression>[SEMICOL]
            pass->s = parent;
            semanalyzer(pass->next,parent);
            pass->next->next->s = parent;
            pass->next->next->next->s = parent;
            pass->next->next->next->next->s = parent;
            semanalyzer(pass->next->next->next->next->child,parent);  
            break;
        case 47://<index_>=[NUM]
            pass->s = parent;
            break;
        case 48://<index_>=[ID]
            pass->s = parent;
            ispresent = lookpres(pass->tk->text,parent);
            if(ispresent == -1)
            {    
                erlist[numerr] = pass->next->tk;
                numerr = numerr + 1;
            }
            break;  
        case 49://<moduleReuseStmt>=<optional>[USE][MODULE][ID][WITH][PARAMETERS]<idList>[SEMICOL]
            pass->s = parent;
            ispresent = lookpres(pass->next->tk->text,parent);
            currast = pass->next;
            pass->next->s = parent;
            if(ispresent == -1)
            {    
                erlist[numerr] = pass->next->tk;
                numerr = numerr + 1;
            }
            else
            {
                currast = currast->next;
                currast->s = parent; //WITH
                currast->next->s = parent;//PARAMETERS
                currast = currast->next;
                int count = 0;
                currast = currast->next->child;
                while(currast != NULL)
                {
                    int ispresent = lookpres(currast->tk->text,parent);
                    if(ispresent == -1)
                    {    
                        erlist[numerr] = pass->next->tk;
                        numerr = numerr + 1;
                    }
                    currast->s = parent;
                    currast = currast->next;
                    count = count + 1;
                }
                for(int i = 0;i<100;i++)
                {
                    if(modulelist[i] == NULL)
                        break;
                    if(modulelist[i]->name == pass->next->tk->text)
                    {
                        if(modulelist[i]->inp == count)
                        {    break;}
                        else
                        {
                            printf("Error");
                        }
                        
                    }
                }
            }
            
            break;
        case 50://<optional>=[SQBO]<idList>[SQBC][ASSIGNOP]
            pass->s = parent;
            semanalyzer(pass->next,parent);
            break;
        case 51://<optional>=[E]
            break;
        case 52://<idList>=[ID]<idList_rec>
        //idlist
            pass->s = parent;
            semanalyzer(pass->next,parent);
            break;
        case 53://<idList_rec>=[COMMA][ID]<idList_rec>
        //idlist
            pass->s = parent;
            semanalyzer(pass->next,parent);
            break;     
        case 54://<idList_rec>=[E]
            break;
        case 55://<expression>=<aOrBExpr>
            break;
        case 56://<expression>=<U>
            break;
        case 57://<U>=<plus_min><new_NT>
            break;
        case 58://<new_NT>=[BO]<arithExpr>[BC]
            pass->s = parent;
            semanalyzer(pass->next,parent);
            pass->next->next->s = parent;
            break;
        case 59://<new_NT>=<var_id_num>
            break;
        case 60://<aOrBExpr>=<AnyTerm><N7>
            break;
        case 61://<N7>=<logicalOp><AnyTerm><N7>
            break;
        case 62://<N7>=[E]
            break;
        case 63://<AnyTerm>=<arithExpr><N8>
            break;
        case 64://<AnyTerm>=<boolConstt>
            break;
        case 65://<N8>=<relOp><arithExpr>
            break;
        case 66://<N8>=[E]
            break;
        case 67://<arithExpr>=<term><N4>
            break;
        case 68://<N4>=<plus_min><term><N4>
            break;
        case 69://<N4>=[E]
            break;
        case 70://<term>=<factor><N5>
            break;
        case 71://<N5>=<mul_div><factor><N5>
            break;
        case 72://<N5>=[E]
            break;
        case 73://<factor>=[BO]<aOrBExpr>[BC]
            pass->s = parent;
            semanalyzer(pass->next,parent);
            pass->next->next->s = parent;
            break;      
        case 74://<factor>=<var_id_num>
            break;
        case 75://<mul_div>=[MUL]       
            pass->s=parent;
            break; 
        case 76://<mul_div>=[DIV]
            pass->s=parent; 
            break;                        
        case 77://<plus_min>=[PLUS]
            pass->s=parent;
            break;                        
        case 78://<plus_min>=[MINUS]
            pass->s=parent;  
            break;                        
        case 79://<relOp>=[LT]
            pass->s=parent;  
            break;                        
        case 80://<relOp>=[LE]
            pass->s=parent; 
            break;                        
        case 81://<relOp>=[GT]
            pass->s=parent;  
            break;                        
        case 82://<relOp>=[GE]
            pass->s=parent;  
            break;                        
        case 83://<relOp>=[EQ]
            pass->s=parent; 
            break;                                              
        case 84://<relOp>=[NE]
            pass->s=parent; 
            break;                        
        case 85://<logicalOp>=[AND]
            pass->s=parent;  
            break;                        
        case 86://<logicalOp>=[OR]
            pass->s=parent;  
            break; 
        case 87://<declareStmt>=[DECLARE]<idList>[COLON]<datatype>[SEMICOL]     //check it
            pass->s = parent;
            currast = pass;
            while(currast->no != COLON)
            {
                currast = currast->next;
            }
            type = 0;
            int start = 0;
            int end = 0;
            if(currast->next->no == ARRAY)
            {
                type = 10;
                if(currast->next->next->no == NUM)
                    start = getvalue(currast->next->next->tk->text);
                currast = currast->next->next->next;
                if(currast->next->no == NUM)
                    end = getvalue(currast->next->tk->text);
                currast = currast->next;
            }
            if (currast->next->no == INTEGER)
                type = type + 2;
            if (currast->next->no == REAL)
                type = type + 3;
            if (currast->next->no == BOOLEAN)
                type = type + 4;
                
            while(pass->next->no != COLON)
            {
                addsingleentry(pass->next,parent,type,start,end);
                pass->s = parent;
                pass->next->s = parent;
                pass = pass->next;
            }

            //t[entries] to t[entries-i].type=datatype;
            break;    
        case 88://<conditionalStmt>=[SWITCH][BO][ID][BC][START][CASE]<caseStmt><default_>[END] //check id is num
            if(pass->next->tk->n!=NULL)
            {
                pass->s=parent;
                pass->next->next->s=parent;
                pass->next->next->next->s=parent;
                semanalyzer(pass->next->next->next->next,parent);
                semanalyzer(pass->next->next->next->next->next,parent);
                pass->next->next->next->next->next->next->s=parent;
            }
            else
            {
                printf("ERROR\n");
            }
            
            break;    
        case 89://<caseStmt>=<value>[COLON]<statements>[BREAK][SEMICOL]<caseStmt_rec>
            s = (struct symTable*)malloc(sizeof(struct symTable));
            // for(int i =0;i<20;i++)
            //     s->name[i] = pass->tk->text[i];
            temp = (char *)malloc((strlen("START")+1)*sizeof(char));
            temp = "CASE";
            s->name = temp;
            s->offset = 0;
            s->entries = 0;
            for(int i =0;i<20;i++)
            {    if(parent->next[i] == NULL)
                 {   parent->next[i] = s;
                    s->prev = parent;
                    break;
                 }
            }
            pass->s = s;
            semanalyzer(pass->next,s);
            pass->next->next->s=s;
            semanalyzer(pass->next->next->next,parent);
            symlist[numsym] = s;
            numsym = numsym + 1;
            break;  
        case 90://<caseStmt_rec>=[CASE]<value>[COLON]<statements>[BREAK][SEMICOL]<caseStmt_rec>
            s = (struct symTable*)malloc(sizeof(struct symTable));
            // for(int i =0;i<20;i++)
            //     s->name[i] = pass->tk->text[i];
            temp = (char *)malloc((strlen("START")+1)*sizeof(char));
            temp = "CASE";
            s->name = temp;
            s->offset = 0;
            s->entries = 0;
            for(int i =0;i<20;i++)
            {    if(parent->next[i] == NULL)
                 {   parent->next[i] = s;
                    s->prev = parent;
                    break;
                 }
            }
            pass->s = s;
            semanalyzer(pass->next,parent);
            pass->next->next->s=s;
            semanalyzer(pass->next->next->next,s);
            pass->next->next->next->next->s=s;
            if(pass->next->next->next->next->next->ruleno == 90)
                semanalyzer(pass->next->next->next->next->next,parent);
            symlist[numsym] = s;
            numsym = numsym + 1;
            break;   
        case 91://<caseStmt_rec>=[E]
            break;
        case 92://<default_>=[DEFAULT][COLON]<statements>[BREAK][SEMICOL]

            s = (struct symTable*)malloc(sizeof(struct symTable));
            // for(int i =0;i<20;i++)
            //     s->name[i] = pass->tk->text[i];
            temp = (char *)malloc((strlen("START")+1)*sizeof(char));
            temp = "DEFAULT";
            s->name = temp;
            s->offset = 0;
            s->entries = 0;
            for(int i =0;i<20;i++)
            {    if(parent->next[i] == NULL)
                 {   parent->next[i] = s;
                    s->prev = parent;
                    break;
                 }
            }
            pass->s = s;
            pass->next->s=s;
            semanalyzer(pass->next->next,s);
            pass->next->next->next->s=s;
            symlist[numsym] = s;
            numsym = numsym + 1;
            break;   
        case 93://<default_>=[E]
            break;
        case 94://<value>=<num>
            break;
        case 95://<value>=[TRUE]
            break;
        case 96://<value>=[FALSE]
            break;
        case 97://<iterativeStmt>=[FOR][BO][ID][IN]<range>[BC][START]<statements>[END]

            s = (struct symTable*)malloc(sizeof(struct symTable));
            // for(int i =0;i<20;i++)
            //     s->name[i] = pass->tk->text[i];
            temp = (char *)malloc((strlen("START")+1)*sizeof(char));
            temp = "FORLOOP";
            s->name = temp;
            s->offset = 0;
            s->entries = 0;
            for(int i =0;i<20;i++)
            {    if(parent->next[i] == NULL)
                 {   parent->next[i] = s;
                    s->prev = parent;
                    break;
                 }
            }
            pass->s = s;
            pass->next->s=s;
            pass->next->next->next->s=s;
            semanalyzer(pass->next->next->next->next,s);
            pass->next->next->next->next->next->s=s;
            pass->next->next->next->next->next->next->s=s;
            semanalyzer(pass->next->next->next->next->next->next->next,s);
            pass->next->next->next->next->next->next->next->next->s=s;
            symlist[numsym] = s;
            numsym = numsym + 1;
            break;  
        case 98://<iterativeStmt>=[WHILE][BO]<aOrBExpr>[BC][START]<statements>[END]
           s = (struct symTable*)malloc(sizeof(struct symTable));
            // for(int i =0;i<20;i++)
            //     s->name[i] = pass->tk->text[i];
            temp = (char *)malloc((strlen("START")+1)*sizeof(char));
            temp = "WHILELOOP";
            s->name = temp;
            s->offset = 0;
            s->entries = 0;
            for(int i =0;i<20;i++)
            {    if(parent->next[i] == NULL)
                 {   parent->next[i] = s;
                    s->prev = parent;
                    break;
                 }
            }
            pass->s = s;
            pass->next->s=s;
            semanalyzer(pass->next->next,s);
            pass->next->next->next->s=s;
            pass->next->next->next->next->s=s;
            semanalyzer(pass->next->next->next->next->next,s);
            pass->next->next->next->next->next->next->s=s;
            symlist[numsym] = s;
            numsym = numsym + 1;
            break;        
        case 99://<range>=<index_>[RANGE]<index_>
            pass->s=parent;
            semanalyzer(pass->next,parent);
            break;
        case 100://<num>=<plus_min>[NUM]
            pass->s=parent; 
            break;
        case 101://<num>=[NUM]
            pass->s=parent; 
            break;
        case 102://<rnum>=<plus_min>[RNUM]
            pass->s=parent; 
            break;
        case 103://<rnum>=[RNUM]
            pass->s=parent; 
            break; 
    }
}
