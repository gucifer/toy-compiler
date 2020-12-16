#include "codegen.h"
#include "expeval.c"

void getlabel()
{
    sprintf(conv, "%d", coutreg);       //convert number to string
    strcpy(tret, label);
    strcat(tret,conv);
    clabel++;
}


void getreg()
{
    sprintf(conv, "%d", coutreg);       //convert number to string
    strcpy(tret, reg);
    strcat(tret,conv);
    creg++;
}


void getoutreg()
{
    sprintf(conv, "%d", coutreg);       //convert number to string
    strcpy(tret, outreg);
    strcat(tret,conv);
    coutreg++;
}


void getdefreg()
{
    sprintf(conv, "%d", cdefreg);       //convert number to string
    strcpy(tret, defreg);
    strcat(tret,conv);
    cdefreg++;
}

void whatisdefreg()
{
    sprintf(conv, "%d", cdefreg);       //convert number to string
    strcpy(tret, defreg);
    strcat(tret,conv);
    
}

void init_filewrite()
{
    functiondeffp  = fopen ("codegen.txt", "w");        //for function declarations
    datafp = fopen ("codegen_data.txt", "w");
    bssfp = fopen ("codegen_bss.txt", "w");
    textfp = fopen ("codegen_text.txt", "w");
    fprintf(functiondeffp,"default rel\n\n");
    fprintf(functiondeffp,"global main: \n");

    fprintf(datafp,"extern printf\n");              
    fprintf(datafp,"extern __isoc99_scanf\n");
    fprintf(datafp,"SECTION .data \n");

    fprintf(bssfp,"SECTION .bss\n");

    fprintf(textfp,"SECTION .text\n");        //start from here for function definitions
}



void append_files(FILE *source, FILE *dest)
{
    char byte;

    while (!feof(source)) 
    {
        fread(&byte, sizeof(char), 1, source);
        fwrite(&byte, sizeof(char), 1, dest);
    }

}


int lookup(char* name,struct symTable* parent)
{
    int i;
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
    // return ispresent;
    return i;  
}

void evalexpr(struct ast* currast)
{
    char *a = (char*)malloc(100*sizeof(char));
    if(currast->type == 'N')
        currast = currast->child;
    while(currast != NULL)
    {
        switch(currast->no)
        {
            case PLUS:
                strcat(a,'+');
            case MINUS:
                strcat(a,'-');
            case MUL:
                strcat(a,'*');
            case DIV:
                strcat(a,'/');
            case BC:
                strcat(a,')');
            case BO:
                strcat(a,'(');
            case ID:
                strcat(a,currast->tk->text);
            case NUM:
                strcat(a,currast->tk->text);
        }
        currast = currast->next;
    }
    strcpy(infix,a);
    exprasm();
}
void codegenerator(struct ast* pass, struct symTable* parent,FILE *fp)
{
    switch(pass->ruleno)
    {
        struct ast* currast;
        struct ast* t;
        struct symTable* s;
        char temp[15],temp2[15];
        int ispresent;
        int count;
        int type;
        int lookupres;
        case 0://<program>=<moduleDeclarations><othermodules><driverModule><othermodules>
            
            init_filewrite();

            currast = pass->child;
            while(currast != NULL)
            {
                codegenerator(currast,currast->s,fp);
                currast = currast->next;
            }

            // append_files(functiondeffp,datafp);
            // append_files(functiondeffp,bssfp);
            // append_files(functiondeffp,textfp);

            break;
        case 1://<moduleDeclarations>=<moduleDeclaration><moduleDeclarations>
            currast = pass->child;
            codegenerator(currast,currast->s,fp);
            break;
        case 2://<moduleDeclarations>=[E]
            break;
        case 3://<moduleDeclaration>=[DECLARE][MODULE][ID][SEMICOL]
            break;
        case 4://<othermodules>=<module><othermodules>
            currast = pass;
            codegenerator(pass->child,pass->child->s,fp);
            codegenerator(pass->next,pass->next->s,fp);
            break;
        case 5://<othermodules>=[E]
            break;
        case 6://<driverModule>=[DRIVERDEF][DRIVER][PROGRAM][ENDDEF]<moduleDef>
            fprintf(datafp,"main:      ;Function begins");
            codegenerator(pass->child,pass->child->s,datafp);
            fprintf(datafp,"\tpop     rbp\n");          
            fprintf(datafp,"\tret\n");
            fprintf(datafp,"; main End of function\n");
            // clabel=0;
            // creg=0;
            break;
        case 7://<module>=[DEF][MODULE][ID][ENDDEF][TAKES][INPUT][SQBO]<input_plist>[SQBC][SEMICOL]<ret><moduleDef>
            fprintf(functiondeffp,"global %s: function\n",pass->next->tk->text);
            fprintf(textfp,"%s:        ;Function begins",pass->next->tk->text);
            currast = pass->next->next;
            codegenerator(currast->child,currast->s,textfp);         
            while(currast->no != START)
                currast = currast->next;
            coutreg=0;
            currast = pass;
            while(currast->ruleno != 8 && currast != NULL)
                currast = currast->next;
            currast = currast->child;
            while(currast !=NULL)                           
            {
                getoutreg();
                lookupres=lookup(currast->tk->text,currast->s);
                fprintf(textfp,"\tmov     %s, dword [rbp-%d]\n",tret,currast->s->t[lookupres]->offset);
                currast = currast->next->next;
            }
            currast = pass;
            while(currast->ruleno != 8)
                currast = currast->next;
            codegenerator(currast,currast->s,textfp);          
            coutreg=0;
            fprintf(textfp,"\tleave\n");
            fprintf(textfp,"\tret\n");
            fprintf(textfp,"; %s End of function\n",pass->next->tk->text);

            creg=0;
            clabel=0;
            break;
        case 8://<ret>=[RETURNS][SQBO]<output_plist>[SQBC][SEMICOL]
            codegenerator(pass->next,pass->next->s,fp);
            break;
        case 9://<ret>=[E]
            break;
        case 10://<input_plist>=[ID][COLON]<datatype><input_plist_rec>
            currast = pass;
            lookupres=lookup(pass->tk->text,pass->s);
            fprintf(fp,"\tmov     dword [rbp-%d], edi\n",pass->s->t[lookupres]->offset);
            creg++;
            codegenerator(currast->next,currast->next->s,fp);
            break;
        case 11://<input_plist_rec>=[COMMA][ID][COLON]<datatype><input_plist_rec>
            currast = pass;
            if(creg==1)
            {
                lookupres=lookup(pass->tk->text,pass->s);
                fprintf(fp,"\tmov     dword [rbp-%d], esi\n",pass->s->t[lookupres]->offset);
                creg++;
            }
            else if(creg==2)
            {
                lookupres=lookup(pass->tk->text,pass->s);
                fprintf(fp,"\tmov     dword [rbp-%d], edx\n",pass->s->t[lookupres]->offset);
                creg++;
            }
            else if (creg==3)
            {
                lookupres=lookup(pass->tk->text,pass->s);
                fprintf(fp,"\tmov     dword [rbp-%d], ecx\n",pass->s->t[lookupres]->offset);
                creg++;
            }
            else
            {
                getreg();
                lookupres=lookup(pass->tk->text,pass->s);
                fprintf(fp,"\tmov     dword [rbp-%d], %s\n",pass->s->t[lookupres]->offset,tret);
            }
            
            if(currast->next != NULL)
                codegenerator(currast->next,currast->next->s,fp);
            break;
        case 12://<input_plist_rec>=[E]
            break;
        case 13://<output_plist>=[ID][COLON]<type><output_plist_rec>  
            getoutreg();
            lookupres=lookup(pass->tk->text,pass->s);
            fprintf(fp,"\tmov     dword [rbp-%d], %s\n",pass->s->t[lookupres]->offset,tret);
            codegenerator(pass->next->next,pass->next->next->s,fp);
            break; 
        case 14://<output_plist_rec>=[COMMA][ID][COLON]<type><output_plist_rec>
            getoutreg();
            lookupres=lookup(pass->tk->text,pass->s);
            fprintf(fp,"\tmov     dword [rbp-%d], %s\n",pass->s->t[lookupres]->offset,tret);
            codegenerator(pass->next->next,pass->next->next->s,fp);
            break;
        case 15://<output_plist_rec>=[E]
            break;
        case 16://<datatype>=<type>
            break;
        case 17://<datatype>=[ARRAY][SQBO]<range>[SQBC][OF]<type>
            break;
        case 18://<type>=[INTEGER]
            break;
        case 19://<type>=[REAL]
            break;
        case 20://<type>=[BOOLEAN]
            break;
        case 21://<moduleDef>=[START]<statements>[END]
            
            while(pass->next->no != END)
            {
                codegenerator(pass->next->child,pass->next->child->s,fp);
                pass = pass->next;
            }
            break;
        case 22://<statements>=<statement><statements>
            
            codegenerator(pass->child,pass->child->s,fp);
            if(pass->next != NULL)
                codegenerator(pass->next,pass->next->s,fp);
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
            lookupres=lookup(pass->next->tk->text,pass->next->s);
            fprintf(fp,"mov     eax, dword [rbp-%d]\n",pass->s->t[lookupres]->offset);
            fprintf(fp,"cdqe\n");
            fprintf(fp,"mov     rdi, rax\n");
            fprintf(fp,"mov     eax, 0\n");
            fprintf(fp,"call    __isoc99_scanf\n");

            break;
        case 30://<ioStmt>=[PRINT][BO]<var>[BC][SEMICOL]
            
            codegenerator(pass->next,pass->next->s,fp);    //mov     eax, sinput
            fprintf(fp,"\tcall    printf         ; call our print function\n");
            break;
        case 31://<boolConstt>=[TRUE]
            break;
        case 32://<boolConstt>=[FALSE]
            break;
        case 33://<var_id_num>=[ID]<whichId>
            
            if(pass->next != NULL)
                codegenerator(pass->next,pass->next->s,fp);
            else
            {
                lookupres=lookup(pass->tk->text,pass->s);
                fprintf(fp,"\tmov     eax, dword [rbp-%d] \n",pass->s->t[lookupres]->offset);
                fprintf(fp,"\tmov     esi, eax \n");
                fprintf(fp,"\tmov     eax, 0  \n");
                fprintf(fp,"\tcall    printf\n");
            }
            
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
        lookupres=lookup(pass->next->tk->text,pass->next->s);
            fprintf(fp,"\tmov     eax, dword [rbp-%d] \n",pass->next->s->t[lookupres]->offset);
            fprintf(fp,"\tmov     esi, eax \n");
            fprintf(fp,"\tmov     eax, 0  \n");
            fprintf(fp,"\tcall    printf\n");
            currast = pass->next->next;
            codegenerator(currast->next,currast->next->s,fp);
            break;
        case 39://<whichId>=[E]
            break;
        case 40://<simpleStmt>=<assignmentStmt>
            break;
        case 41://<simpleStmt>=<moduleReuseStmt>
            break;       
        case 42://<assignmentStmt>=[ID]<whichStmt>
            codegenerator(pass->next,pass->next->s,fp);    //mov     eax, dword [rbp-8H]
            if(pass->next->ruleno==45)
            {
                lookupres=lookup(pass->tk->text,pass->s);
                fprintf(fp,"\tmov     dword [rbp-%d], eax\n",pass->s->t[lookupres]->offset);
            }
            if(pass->next->ruleno == 46)
            {
                lookupres = lookup(pass->tk->text,pass->next->next->s);
                int type = pass->s->t[lookupres]->type;
                if(type%10 == 2)
                    type = SIZEOFNUM;
                if(type%10 == 3)
                    type = SIZEOFREAL;
                if(type%10 == 4)
                    type = SIZEOFBOOL;
                if(pass->next->next->no == ID)
                {
                    lookupres = lookup(pass->next->next->tk->text,pass->next->next->s);
                    fprintf(fp,"\tmul dword [rbp-%d], %d\n",pass->s->t[lookupres]->offset,type);
                    fprintf(fp,"\tmov ebx, dword [rbp-%d]\n",pass->s->t[lookupres]->offset);
                    lookupres=lookup(pass->tk->text,pass->s);
                    fprintf(fp,"\tmov     dword [rbp-ebx-%d], eax\n",pass->s->t[lookupres]->offset);
                    fprintf(fp,"mov eax,ebx");
                    lookupres = lookup(pass->next->next->tk->text,pass->next->next->s);
                    fprintf(fp,"div %d",type);
                    fprintf(fp,"mov dword[rbp-%d], eax ",pass->s->t[lookupres]->offset);
                }
                else
                {
                    fprintf(fp,"\tmul ebx, %s\n",pass->next->next->tk->text);   
                    fprintf(fp,"\tmov     dword [rbp-ebx-%d], eax\n",pass->s->t[lookupres]->offset);
                }
                
            }
            break;
        case 43://<whichStmt>=<lvalueIDStmt>
            break;      
        case 44://<whichStmt>=<lvalueARRStmt>
            break;  
        case 45://<lvalueIDStmt>=[ASSIGNOP]<expression>[SEMICOL]    
            evalexpr(pass->next);          
            fprintf(fp,"\tmov     eax, expreg\n"); 
            fprintf(fp,"\n");
            break;
        case 46://<lvalueARRStmt>=[SQBO]<index_>[SQBC][ASSIGNOP]<expression>[SEMICOL]
            evalexpr(pass->next->next->next->next);  
            fprintf(fp,"\tmov     eax, expreg\n"); 
            fprintf(fp,"\n");
            break;
        case 47://<index_>=[NUM]        
            lookupres=lookup(pass->tk->text,pass->s);
            fprintf(fp,"\tmov     dword [rbp-%d], eax\n",pass->s->t[lookupres]->offset);
            break;
        case 48://<index_>=[ID]     
            lookupres=lookup(pass->tk->text,pass->s);    
            fprintf(fp,"\tmov     dword [rbp-%d], eax\n",pass->s->t[lookupres]->offset);
            break;  
        case 49://<moduleReuseStmt>=<optional>[USE][MODULE][ID][WITH][PARAMETERS]<idList>[SEMICOL] 
            if(flagoptional==0)
            {
                flagoptional=1;
                break;
            }
            else
            if(flagoptional==1)
            {
                currast=pass;
                while (currast->no!=ID)
                {
                    currast=currast->next;
                }
                pass=currast;
                while (currast->no!=PARAMETERS)
                {
                    currast=currast->next;
                }
                codegenerator(currast->next->child,currast->next->child->s,fp);
                fprintf(fp,"\tcall    %s\n",pass->tk->text);
                coutreg=0;
                flagoptional=0;
            }
            break;
        case 50://<optional>=[SQBO]<idList>[SQBC][ASSIGNOP] 
            flagoptional=1;
            currast=pass;
            while (currast->no!=ASSIGNOP)
            {
                currast=currast->next;
            }      
            codegenerator(currast->next,currast->next->s,fp);         
            currast=pass->next->child;
            while(currast != NULL)
            {
                getoutreg();
                lookupres=lookup(currast->tk->text,currast->s);
                fprintf(fp,"\tmov     dword [rbp-%d], %s\n",currast->s->t[lookupres]->offset,tret);
                currast = currast->next;
            }
            codegenerator(pass->next,pass->next->s,fp);
            // while (currast->no!=29)
            // {
            //     currast=currast->next;
            // }
            break;
        case 51://<optional>=[E]
            break;
        case 52://<idList>=[ID]<idList_rec>         
            codegenerator(pass->next,pass->next->s,fp);
            lookupres=lookup(pass->tk->text,pass->s);
            fprintf(fp,"\tmov     edx, dword [rbp-%d]\n",pass->s->t[lookupres]->offset);
            fprintf(fp,"\tpush    rdx\n");
            break;
        case 53://<idList_rec>=[COMMA][ID]<idList_rec>
            if(pass->next != NULL)            
                codegenerator(pass->next,pass->next->s,fp);
            lookupres=lookup(pass->tk->text,pass->s);
            fprintf(fp,"\tmov     edx, dword [rbp-%d]\n",pass->s->t[lookupres]->offset);
            fprintf(fp,"\tpush    rdx\n");
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
            codegenerator(pass->next,pass->next->s,fp);
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
            codegenerator(pass->next,pass->next->s,fp);
            break;      
        case 74://<factor>=<var_id_num>
            break;
        case 75://<mul_div>=[MUL]   //hardcode
            fprintf(fp, "\tmul");                 //accepts only one argument ;mul ebx ;multiplies ebx by eax 
            break; 
        case 76://<mul_div>=[DIV]   //hardcode
            fprintf(fp, "\tdiv");                 //accepts only one arg. Divides whatever given in eax by value passed to instruction
            break;                        
        case 77://<plus_min>=[PLUS]            
            fprintf(fp, "\tadd");
            break;                        
        case 78://<plus_min>=[MINUS]            
            fprintf(fp,"\tsub");
            break;                        
        case 79://<relOp>=[LT]
            fprintf(fp,"\tjl");
            break;                        
        case 80://<relOp>=[LE]
            fprintf(fp,"\tjle");
            break;                        
        case 81://<relOp>=[GT]
            fprintf(fp,"\tjg");
            break;                        
        case 82://<relOp>=[GE]
            fprintf(fp,"\tjge");
            break;                        
        case 83://<relOp>=[EQ]
            fprintf(fp,"\tje");
            break;                                              
        case 84://<relOp>=[NE]
            fprintf(fp,"\tjne");
            break;                        
        case 85://<logicalOp>=[AND]
            fprintf(fp, "\tand");
            break;                        
        case 86://<logicalOp>=[OR]
            fprintf(fp, "\tor");
            break; 
        case 87://<declareStmt>=[DECLARE]<idList>[COLON]<datatype>[SEMICOL]   
            //No assembly code was generated for just declaring these variables                                         ; 0067 _ C3
            break;    
        case 88://<conditionalStmt>=[SWITCH][BO][ID][BC][START][CASE]<caseStmt><default_>[END] 
            if(pass->next->tk->n!=NULL)
            {
                getdefreg();
                lookupres=lookup(pass->next->tk->text,pass->next->s);
                fprintf(fp,"\tmov     eax, dword [rbp-%d] \n",pass->next->s->t[lookupres]->offset);
                switchstart=clabel;
                iterswitch=1;
                codegenerator(pass->next->next->next->next,pass->next->next->next->next->s,fp);
                whatisdefreg();
                fprintf(fp,"\tjmp %s ",tret);
                iterswitch =0;
                codegenerator(pass->next->next->next->next,pass->next->next->next->next->s,fp);
                codegenerator(pass->next->next->next->next->next,pass->next->next->next->next->next->s,fp);
            }
            // clabel=0;
            break;    
        case 89://<caseStmt>=<value>[COLON]<statements>[BREAK][SEMICOL]<caseStmt_rec>     
            if(iterswitch==1)  
            {
                fprintf(fp,"\tcmp     eax, ");
                codegenerator(pass->next,pass->next->s,fp);
                fprintf(fp,"\n");
                getlabel();
                fprintf(fp,"\tje %s\n",tret);
                codegenerator(pass->next->next->next,pass->next->next->next->s,fp);
                break;
            }
            strcpy(temp, label);
            strcat(temp,switchstart);
            fprintf(fp,"%s: ",temp);   
            switchstart++; 
            codegenerator(pass->next,pass->next->s,fp);
            fprintf(fp,"\n");
            whatisdefreg();
            fprintf(fp,"jmp     %s",tret); 
            codegenerator(pass->next->next->next,pass->next->next->next->s,fp);
            break;  
        case 90://<caseStmt_rec>=[CASE]<value>[COLON]<statements>[BREAK][SEMICOL]<caseStmt_rec>
            if(iterswitch==1)  
            {
                fprintf(fp,"\tcmp     eax, ");
                codegenerator(pass->next,pass->next->s,fp);
                fprintf(fp,"\n");
                getlabel();
                fprintf(fp,"\tje %s\n",tret);
                codegenerator(pass->next->next->next->next->next,pass->next->next->next->next->next->s,fp);
                break;
            }
            strcpy(temp, label);
            strcat(temp,switchstart);
            fprintf(fp,"%s: ",temp);   
            switchstart++;    
            codegenerator(pass->next->next->next,pass->next->next->next->s,fp);
            fprintf(fp,"\n");
            whatisdefreg();
            fprintf(fp,"jmp     %s",tret);  
            codegenerator(pass->next->next->next->next->next,pass->next->next->next->next->next->s,fp);
            break;   
        case 91://<caseStmt_rec>=[E]
            break;
        case 92://<default_>=[DEFAULT][COLON]<statements>[BREAK][SEMICOL]
            whatisdefreg();
            fprintf(fp,"%s: ",tret);    
            codegenerator(pass->next->next,pass->next->next->s,fp);
            break;   
        case 93://<default_>=[E]
            break;
        case 94://<value>=<num>
            break;
        case 95://<value>=[TRUE]
            fprintf(fp,"1");
            break;
        case 96://<value>=[FALSE]
            fprintf(fp,"0");
            break;
        case 97://<iterativeStmt>=[FOR][BO][ID][IN]<range>[BC][START]<statements>[END]      

            // codegenerator(pass->next->next->next->next,pass->next->next->next->next->s,fp);
            
            currast=pass;
            while(currast->no!=ID)
            {
                currast=currast->next;
            }
            pass=currast;
            
            currast=currast->next;
            currast=currast->next;//at index_
            lookupres=lookup(currast->tk->text,currast->s);
            fprintf(fp,"\tmov     tempreg, dword [rbp-%d]\n",currast->s->t[lookupres]->offset);
            lookupres=lookup(pass->tk->text,pass->s);
            fprintf(fp,"\tmov     dword [rbp-%d], tempreg\n",pass->s->t[lookupres]->offset);
            struct ast* currast2;
            currast2=currast;
            while(currast2->next->no!=BC)
            {
                currast2=currast2->next;
            }
            getlabel();
            fprintf(fp,"\tjmp, %s\n",tret);
            strcpy(temp,tret);
            getlabel();
            fprintf(fp,"%s:\n",tret);
            strcpy(temp2,tret);
            while(currast->no!=START)
            {
                currast=currast->next;
            }
            codegenerator(currast->next,currast->next->s,fp);
            fprintf(fp,"%s:\n",temp);
            lookupres=lookup(currast2->tk->text,currast2->s);
            fprintf(fp,"\tmov     tempreg, dword [rbp-%d]\n",currast2->s->t[lookupres]->offset);
            lookupres=lookup(pass->tk->text,pass->s);
            fprintf(fp,"\tcmp     dword [rbp-%d], tempreg\n",pass->s->t[lookupres]->offset);
            fprintf(fp,"\tjle, %s\n",temp2);

            //         mov     dword [rbp-8H], 0                       ; 0047 _ C7. 45, F8, 00000000
            //         jmp     ?_002                                   ; 004E _ EB, 0B

            // ?_001:  mov     dword [rbp-4H], 1                       ; 0050 _ C7. 45, FC, 00000001
            //         add     dword [rbp-8H], 1                       ; 0057 _ 83. 45, F8, 01
            // ?_002:  cmp     dword [rbp-8H], 1                       ; 005B _ 83. 7D, F8, 01
            //         jle     ?_001   
            break;  
        case 98://<iterativeStmt>=[WHILE][BO]<aOrBExpr>[BC][START]<statements>[END]
           
            getlabel();
            fprintf(fp,"\tjmp     %s\n",tret);
            strcpy(temp,tret);
            getlabel();
            fprintf(fp,"%s:\n",tret);
            strcpy(temp2,tret);
            codegenerator(pass->next->next->next->next->next,pass->next->next->next->next->next->s,fp);
            fprintf(fp,"%s:\n",temp);
            codegenerator(pass->next->next,pass->next->next->s,fp);
            //fprintf(fp,"cmp     dword [rbp-8H], 0 ")      //not sure what to compare
            fprintf(fp,"\tjnz     %s\n",temp2);
            
            break;        
        case 99://<range>=<index_>[RANGE]<index_>
            codegenerator(pass->next,pass->next->s,fp);
            break;
        case 100://<num>=<plus_min>[NUM]
            fprintf(fp,"%s",pass->tk->text);
            break;
        case 101://<num>=[NUM]
            fprintf(fp,"%s",pass->tk->text);  
            break;
        case 102://<rnum>=<plus_min>[RNUM]
            fprintf(fp,"%s",pass->tk->text);
            break;
        case 103://<rnum>=[RNUM]
            fprintf(fp,"%s",pass->tk->text);  
            break; 
    }
}
