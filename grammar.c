#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "t_nont.h"
#include "parserdef.h"
int r_count = 0;

int make_grammar()
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    size_t read;
    int i=0;
    fp = fopen("grammar.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) 
    {
        strcpy(grammar[i],"\0");
        strcpy(grammar[i],line);
        i++;
    }

    fclose(fp);
    if (line)
        free(line);
    return i;
}


void getmodifiedrule(char* rule)
{
    int i = 0;
    int r = 0;
    while(rule[i] != NULL)
    {
        if(rule[i] == '<')
        {
            i = i + 1;
            int j = 0;
            char substr[20] = "\0";
            while(rule[i] != '>')
            {
                substr[j] = rule[i];
                i = i + 1;
                j = j + 1;
            }
            int val = get_nonterminal_no(substr);
            i = i + 1;
            rulelist[r_count][r+1] = val;
            rulelist[r_count][r] = 'N';
            r = r + 2;
        }
        else if(rule[i] == '[')
        {
            i = i + 1;
            int j = 0;
            char substr[20]="\0";
            while(rule[i] != ']')
            {
                substr[j] = rule[i];
                i = i + 1;
                j = j + 1;
            }
            int val = get_terminal_no(substr);
            i = i + 1;
            rulelist[r_count][r+1] = val;
            rulelist[r_count][r] = 't';
            r = r + 2;        
        }
        else if(rule[i] == '=')
        {
            rulelist[r_count][r] = '=';
            r = r + 1;
            i = i + 1;
        }
        else
        {
            break;
        }
    }
    r_count = r_count + 1;
}
void getgrammar(){
        int x=0;
    x=make_grammar();
    int i = 0;
    while(i<x)
    {
        getmodifiedrule(grammar[i]);
        i = i + 1;
    }
}

void printgrammar()
{
    for(int i=0;i<108;i++)
    {
        printf("\n");
        printf("%c%d%c",rulelist[i][0],rulelist[i][1],rulelist[i][2]);
        for(int j =3;j<40;j++)
        {
            if(rulelist[i][j] != 0)
            {
            if(j%2==1)
                printf("%c",rulelist[i][j]);
            else
            {
                printf("%d",rulelist[i][j]);
            }
            }
        }
    }
}

void addtofirstset(int i, int val)
{
    int there = 0;
    for(int j=1;j<20;j++)
    {
        if(first[val][j]== i+1)
        {
            there = 1;
            break;
        }
    }
    if(there == 0)
    {
        first[val][first[val][0]] = i+1;
        first[val][0] = first[val][0] + 1;
    }
}

int getfirst(int i, int j, int iseps,int val)
{
    if(rulelist[i][j] == 't')
    {
        
        if(rulelist[i][j+1] == 61)
        {
            iseps = 1;
            if(val == rulelist[i][1])
            {
                addtofirstset(rulelist[i][j+1],val);
            }
        }
        else
        {
            addtofirstset(rulelist[i][j+1],val);
        }
        
    }
    else if(rulelist[i][j] == 'N')
    {
        iseps = findfirst(rulelist[i][j+1],val);
        if(iseps == 1)
        {
            j = j + 2;
            iseps = getfirst(i,j,0,val);
        }
    }
    return iseps;
}

int findfirst(int c, int val)
{
    int iseps = 0;
    for(int i = 0;i<108;i++)
    {
        if(rulelist[i][1] == c)
        {
            int j = 3;
            iseps = getfirst(i,j,iseps,val);
        }
    }
    return iseps;
}


void firstnfollow()
{
    for(int i = 0; i<r_count;i++)
    {
        int c = rulelist[i][1];
        findfirst(c,c);
    }

}
void printfirst()
{
    for(int i =0;i<62;i++)
    {
        printf("\n%d ",i);
        for(int j =1;j<20;j++)
        {
            if(first[i][j] != 0)
                printf("%d ",first[i][j]);
        }
    }
}


void addtofollowset(int i, int val)
{
    int there = 0;
    for(int j=1;j<40;j++)
    {
        if(follow[val][j]== i+1)
        {
            there = 1;
            break;
        }
    }

    if(there == 0)
    {
        follow[val][follow[val][0]] = i+1;
        follow[val][0] = follow[val][0] + 1;
    }
}

int followfirst(int i, int val,int it)
{
    it = it + 1;
    int iseps = 0;
    for(int j=1;j<first[i][0];j++)
    {
        addtofollowset(first[i][j]-1,val);
        if(first[i][j] == 62)
            iseps = 1;
    }
    if(iseps == 1)
        findfollow(i,val,it);
    return iseps;
}

void findfollow(int i,int val,int it)
{
    it = it + 1;
    if(i==0)
    {
        addtofollowset(60,val);
        addtofollowset(45,0);
    }
    else if((i == val && it == 1) || (i != val))
    {
        for(int j=0;j<100;j++)
        {
            for(int k = 3;k<40;k++)
            {
                if(rulelist[j][k] == i && rulelist[j][k-1] == 'N')
                {
                    if(rulelist[j][k+1] == 't')
                    {
                        addtofollowset(rulelist[j][k+2],val);
                    }
                    else if(rulelist[j][k+1] == 'N')
                    {
                        int iseps = followfirst(rulelist[j][k+2],val,it);
                        if(iseps == 1)
                            findfollow(rulelist[j][k+4],val,it);
                    }
                    else if(rulelist[j][1] != i)
                    {
                        findfollow(rulelist[j][1],val,it);
                    }
                    
                }
            }
        }
        
    }
    
}

void printfollow()
{
    for(int i =0;i<61;i++)
    {
        printf("\n%d ",i);
        for(int j =0;j<40;j++)
        {
            if(follow[i][j] != 0)
                printf("%d ",follow[i][j]);
        }
    }
}

void populategrammar()
{
    getgrammar();
    //printgrammar();
    for(int i=0;i<61;i++)
    {
        first[i][0]=1;
    }
    for(int i=0;i<61;i++)
        findfirst(i,i);
    //printfirst();
    for(int i=0;i<61;i++)
    {
        follow[i][0]=1;
    }
    for(int i=0;i<61;i++)
       findfollow(i,i,0);
    //findfollow();
    //printfollow();
}

void parsenonterm(int i,int j)
{
    if(rulelist[i][j] == 'N')
    {
        for(int k=1;k<first[rulelist[i][j+1]][0];k++)
        {
            parsetable[rulelist[i][1]][first[rulelist[i][j+1]][k]-1] = i+1;
            if(first[rulelist[i][j+1]][k] == 62)
            {
                parsenonterm(i,j+2);
            }
        }
    } 
    if(rulelist[i][j] == 't')
    {
        parsetable[rulelist[i][1]][rulelist[i][j+1]] = i+1;
    }
}

void generateparsetable()
{
    for(int i = 0;i<104;i++)
    {
        if(rulelist[i][3] == 't')
        {
            parsetable[rulelist[i][1]][rulelist[i][4]] = i+1;
            if(rulelist[i][4] == 61)
            {
                for(int j=1;j<follow[rulelist[i][1]][0];j++)
                {
                    parsetable[rulelist[i][1]][follow[rulelist[i][1]][j]-1] = i+1;
                }
            }
        }
        else if(rulelist[i][3] == 'N')
        {
            for(int j=1;j<first[rulelist[i][4]][0];j++)
            {
                parsetable[rulelist[i][1]][first[rulelist[i][4]][j]-1] = i+1;
                if(first[rulelist[i][4]][j]==62)
                {
                    if(rulelist[i][5] == 'N')
                    {
                        parsenonterm(i,5);
                    }
                    else if(rulelist[i][5] == 't')
                    {
                        parsetable[rulelist[i][1]][rulelist[i][5]] = i + 1;
                    }
                    else
                    {
                        for(int k=1;k<follow[rulelist[i][4]][0];k++)
                        {
                            parsetable[rulelist[i][1]][follow[rulelist[i][4]][k]-1] = i+1;
                        }
                    }
                }
            }
        }
    }
}

void printparsetable()
{
    for(int j=0;j<61;j++)
    {
        printf("\n %d ",j);
        for(int i=0;i<61;i++)
        {
            if(parsetable[j][i] != 0)
                printf("%d,%d ",i,parsetable[j][i]);
        }
    }
}

// void main()
// {
//     populategrammar();
//     generateparsetable();
//     //printfirst();
//     printparsetable();
// }