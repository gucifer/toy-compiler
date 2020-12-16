//Arpan Parikh 2016A7TS0082
//Pranav Panchumarthi 2017A7PS0153
//Asrita V. Mandalam 2017A7PS1179
#include "lexer.h"
#include "keywords.h"
#include "t_nont.h"
#define MAXBUFLEN 10000
char source[MAXBUFLEN];
void tokenizer(char* str) {
    int len = strlen(str);
    if(count>=len)
    {
        count = count + 1;
    }
    else
    {    
    while(count < len){

    if (str[count] == '!' && str[count+1] == '=')
    {
        token tk;
        tk.no = get_terminal_no("NE");
        strcpy(tk.text, "!=");
        tk.lineno = line;
        count = count + 2;
        tklist[tkcount] = tk;
        tkcount = tkcount + 1;
        break; //printf("%s\n",tk.type);
    }
    else if (str[count] == '=' && str[count+1] == '=')
    {
        token tk;
        tk.no = get_terminal_no("EQ");
        tk.lineno = line;
        count = count + 2;
        tklist[tkcount] = tk;
        tkcount = tkcount + 1;
        break; //printf("%s\n",tk.type);
    }
    else if (str[count] == ':' && str[count+1] == '=')
    {
        token tk;
        tk.no = get_terminal_no("ASSIGNOP");
        tk.lineno = line;
        count = count + 2;
        tklist[tkcount] = tk;
        tkcount = tkcount + 1;
        break; //printf("%s\n",tk.type);
    }
    else if (str[count] == '.' && str[count+1] == '.')
    {
        token tk;
        tk.no = get_terminal_no("RANGE");
        tk.lineno = line;
        count = count + 2;
        tklist[tkcount] = tk;
        tkcount = tkcount + 1;
        break; //printf("%s\n",tk.type);
    }
    else if (str[count] == ':' && str[count+1] != '=')
    {
        token tk;
        tk.no = get_terminal_no("COLON");
        tk.lineno = line;
        count = count + 1;
        tklist[tkcount] = tk;
        tkcount = tkcount + 1;
        break; //printf("%s\n",tk.type);
    }
    else if (str[count] == '>' && str[count+1] == '=')
    {
        token tk;
        tk.no = get_terminal_no("GE");
        tk.lineno = line;
        count = count + 2;
        tklist[tkcount] = tk;
        tkcount = tkcount + 1;
        break; //printf("%s\n",tk.type);
    }
    else if (str[count] == '>' && str[count+1] == '>')
    {
        token tk;
        tk.no = get_terminal_no("ENDDEF");
        tk.lineno = line;
        count = count + 2;
        tklist[tkcount] = tk;
        tkcount = tkcount + 1;
        break; //printf("%s\n",tk.type);
    }
    else if (str[count] == '>' && str[count+1] != '>' && str[count+1]!='=')
    {
        token tk;
        tk.no = get_terminal_no("GT");
        tk.lineno = line;
        count = count + 1;
        tklist[tkcount] = tk;
        tkcount = tkcount + 1;
        break; //printf("%s\n",tk.type);
    }
    else if (str[count] == '<' && str[count+1] == '=')
    {
        token tk;
        tk.no = get_terminal_no("LE");
        tk.lineno = line;
        count = count + 2;
        tklist[tkcount] = tk;
        tkcount = tkcount + 1;
        break; //printf("%s\n",tk.type);
    }
    else if (str[count] == '<' && str[count+1] == '<')
    {
        token tk;
        if(str[count+2] == 'D')
            tk.no = get_terminal_no("DRIVERDEF");
        else
            tk.no = get_terminal_no("DEF");
        tk.lineno = line;
        count = count + 2;
        tklist[tkcount] = tk;
        tkcount = tkcount + 1;
        break; //printf("%s\n",tk.type);
    }
    else if (str[count] == '<' && str[count+1] != '=' && str[count+1] != '<')
    {
        token tk;
        tk.no = get_terminal_no("LT");
        tk.lineno = line;
        count = count + 1;
        tklist[tkcount] = tk;
        tkcount = tkcount + 1;
        break; //printf("%s\n",tk.type);
    }
    else if (str[count] == '+')
    {
        token tk;
        tk.no = get_terminal_no("PLUS");
        tk.lineno = line;
        count = count + 1;
        tklist[tkcount] = tk;
        tkcount = tkcount + 1;
        break; //printf("%s\n",tk.type);
    }
    else if (str[count] == '-')
    {
        token tk;
        tk.no = get_terminal_no("MINUS");
        tk.lineno = line;
        count = count + 1;
        tklist[tkcount] = tk;
        tkcount = tkcount + 1;
        break; //printf("%s\n",tk.type);
    }
    else if (str[count] == ';')
    {
        token tk;
        tk.no = get_terminal_no("SEMICOL");
        tk.lineno = line;
        count = count + 1;
        tklist[tkcount] = tk;
        tkcount = tkcount + 1;
        break; //printf("%s\n",tk.type);
    }
    else if (str[count] == ',')
    {
        token tk;
        tk.no = get_terminal_no("COMMA");
        tk.lineno = line;
        count = count + 1;
        tklist[tkcount] = tk;
        tkcount = tkcount + 1;
        break; //printf("%s\n",tk.type);
    }
    else if (str[count] == '[')
    {
        token tk;
        tk.no = get_terminal_no("SQBO");
        tk.lineno = line;
        count = count + 1;
        tklist[tkcount] = tk;
        tkcount = tkcount + 1;
        break; //printf("%s\n",tk.type);
    }
    else if (str[count] == ']')
    {
        token tk;
        tk.no = get_terminal_no("SQBC");
        tk.lineno = line;
        count = count + 1;
        tklist[tkcount] = tk;
        tkcount = tkcount + 1;
        break; //printf("%s\n",tk.type);
    }
    else if (str[count] == '(')
    {
        token tk;
        tk.no = get_terminal_no("BO");
        tk.lineno = line;
        count = count + 1;
        tklist[tkcount] = tk;
        tkcount = tkcount + 1;
        break; //printf("%s\n",tk.type);
    }
    else if (str[count] == ')')
    {
        token tk;
        tk.no = get_terminal_no("BC");
        tk.lineno = line;
        count = count + 1;
        tklist[tkcount] = tk;
        tkcount = tkcount + 1;
        break; //printf("%s\n",tk.type);
    }
    else if (str[count] == '\n')
    {
        line = line + 1;
        count = count + 1;
    }
    else if(str[count] == '/')
	{ token tk;
            tk.no = get_terminal_no("DIV");
            tk.lineno = line;
            tklist[tkcount] = tk;
            tkcount = tkcount + 1;
             //printf("%s\n",tk.type);
	        count = count +1;
            break;
	}
    else if (str[count] == ' ' || str[count] == '\t')
    {
        count = count + 1;
    }
    else if (str[count] == '*' && str[count+1] != '*')
    {
        token tk;
        tk.no = get_terminal_no("MUL");
        tk.lineno = line;
        count = count + 1;
        tklist[tkcount] = tk;
        tkcount = tkcount + 1;
        break; //printf("%s\n",tk.type);
    }
    else if (str[count] == '*' && str[count+1] == '*')
    {
        count = count + 2;
        while(true)
        {
            count = count + 1;
            if (str[count] == '*' && str[count] == '*')
            {
                count = count + 2;
                break;
            }
            else if (str[count] == '\n')
            {
                line = line + 1;
            }
        }
    }
    else if ((str[count] >= 'a' && str[count] <= 'z') || (str[count] >= 'A' && str[count] <= 'Z'))
    {
        char* substr = (char*)malloc(20*sizeof(char));
        int varlength = 0;
        while(((str[count] >= 'a' && str[count] <= 'z') || (str[count] >= 'A' && str[count] <= 'Z') || (str[count] >= '0' && str[count] <= '9') || str[count] == '_' ) && varlength < 20)
        {
            char var = str[count];
            substr[varlength] = var;
            varlength = varlength + 1;
            count = count + 1;
        }
        while(((str[count] >= 'a' && str[count] <= 'z') || (str[count] >= 'A' && str[count] <= 'Z') || (str[count] >= '0' && str[count] <= '9') || str[count] == '_' ) && varlength == 20)
        {
            count = count +1;
        }
        //printf("count: %d, str: %s\n",count,substr);
        int val = get_keyword(substr);
        // for(int j = 0;j<20; j++)
        // {
        //     substr[j] = '\0';
        // }
        token tk;
        tk.lineno = line;
        if (val != -1)
        {
            tk.no = val;
        }
        else
        {
            tk.no = get_terminal_no("ID");
        }
        tk.text = substr;
        tklist[tkcount] = tk;
        tkcount = tkcount + 1;
        //printf("%s\n",tk.type);
        break; 
    }
    else if (str[count] >= '0' && str[count] <= '9')
    {
        char* substr = (char*)malloc(20*sizeof(char));
        int numlength = 0;
        while(str[count] >= '0' && str[count] <= '9')
        {
            substr[numlength] = str[count];
            numlength = numlength + 1;
            count = count + 1;
        }
        if (str[count] == '.' && str[count+1] == '.')
        {
            token tk;
            tk.no = get_terminal_no("NUM");
            tk.lineno = line;
            tk.text = substr;
            tklist[tkcount] = tk;
            tkcount = tkcount + 1;
            break; //printf("%s\n",tk.type);
             //printf("here\n");
        }
        else if (str[count] == '.' && (str[count+1] >= '0' && str[count+1] <= '9'))
        {
            substr[numlength] = str[count];
            numlength = numlength + 1;
            count = count + 1;
            while(str[count] >= '0' && str[count] <= '9')
            {
                substr[numlength] = str[count];
                numlength = numlength + 1;
                count = count + 1;
            }
            if((str[count] == 'e' || str[count] == 'E') && (str[count+1] == '+' || str[count+1] == '-'))
            {
                substr[numlength] = str[count];
                substr[numlength+1] = str[count+1];
                numlength = numlength + 2;
                count = count + 2;
                while(str[count] >= '0' && str[count] <= '9')
                {
                    substr[numlength] = str[count];
                    numlength = numlength + 1;
                    count = count + 1;
                }
            }
            token tk;
            tk.no = get_terminal_no("RNUM");
            tk.lineno = line;
            tk.text = substr;
            tklist[tkcount] = tk;
            tkcount = tkcount + 1;
            //count = count - 1;
            break; //printf("%s\n",tk.type);
        }
        else
        {
            token tk;
            tk.no = get_terminal_no("NUM");
            tk.lineno = line;
            tk.text = substr;
            tklist[tkcount] = tk;
            tkcount = tkcount + 1;
            break;  //printf("Error1, Wrong Code at line number '%d' count '%d' string '%c'",line,count,str[count]);
        }
        // for(int j = 0;j<20; j++)
        // {
        // substr[j] = '\0';
        // }
    }
        else
        {
            printf("Error, Wrong Code at line number '%d' count '%d' string '%c'\n",line,count,str[count]);
	        count = count + 1;
            break;
        }
    }
    }
    //return tklist;

}

int buffread(FILE *fp)
{

if (fp != NULL) {
    size_t newLen = fread(source, sizeof(char), MAXBUFLEN-1, fp);
    if ( ferror( fp ) != 0 ) {
        fputs("Error reading file", stderr);
        return 0;
    } else {
        if(feof(fp))
            return newLen;
        if(newLen < 499)
            return newLen;
        int i = newLen;
        while(source[i] != '\n' && i > 0)
        {
            i--;
        }
        if(i>0)
            fp = fp - newLen+i;
        else
        {
            i = newLen;
        }
        
        source[i++] = '\0'; /* Just to be safe. */
        return i;
    }
}
return 0;
}

void print_tokens()
{

    int c=1;
    printf("%d    ,%d\n ", tklist[0].no,tkcount);
    while(c<tkcount)
    {
    printf("%d    %d\n ", tklist[c].lineno, tklist[c].no);
    c = c + 1;
    }

}

void tokenize(FILE *fp)
{
    while(true)
    {
        int i = buffread(fp);
        if(i == 1 || i == 0)
            break;
        while(count<i+1)
        {
            tokenizer(source);
        }
    }
    fclose(fp);
}

token* nexttoken()
{
    token* tk = &tklist[tk_count];
    tk_count++;
    return tk;
}

// void main()
// {
//     FILE *fp = fopen("t1.txt", "r");
//     tokenize(fp);
// }
