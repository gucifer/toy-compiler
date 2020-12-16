#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lexer.h"
#include "parserdef.h"


// token* nexttoken()
// {
// 	return NULL;
// }

void trinit()
{
	tr->type = 'N';
	tr->no = 0;
	for(int i=0;i<10;i++)
		tr->child[i] = NULL;
	tr->parent = NULL;
}

void stinit()
{
	st->type = 'N';
	st->no = 0;
	st->next = NULL;
}

void push(int r)
{
	int i = 3;
	char rule[40];
	for(int k =0;k<40;k++)
	{
		rule[k] = rulelist[r][k];
	}
	struct stack s1;
	struct stack* s2 = &s1;
	struct stack* s3 = &s1;
	while((rule[i] != 0)&&(rule[i] != NULL))
	{
 		struct stack* top = (struct stack*)malloc(sizeof(struct stack));
		top->type = rule[i];
		i = i + 1;
		top->no = rule[i];
		i = i + 1;
		top->next = NULL;
		s3->next = top;
		s3 = s3->next;
	}
	s3->next = st;
	st = s2->next;
}

void pop()
{
	st = st->next;
}

int tracechild()
{
	int i = 0;
	while(tr->child[i] != NULL)
	{
		if(tr->child[i]->visited == 0)
			break;
		else
			i = i + 1;
	}
	if(tr->child[i] == NULL)
		return -1;
	return i;
}

int ptracechild()
{
	int i = 0;
	while(t1->child[i] != NULL)
	{
		if(t1->child[i]->visited == 0)
			i = i + 1;
		else
			break;
	}
	if(t1->child[i] == NULL)
		return -1;
	return i;

}

void addnode(int r)
{
	int i = 3;
	int j = 0;
	//printf("qwe %d %s\n",r,rulelist[r]);
	char rule[40];
	for(int k =0;k<40;k++)
	{
		rule[k] = rulelist[r][k];
	}
	while((rule[i] != 0)&&(rule[i] != NULL))
	{
 		struct tree* node = (struct tree*)malloc(sizeof(struct tree));
 		node->visited = 0;
		for(int a =0 ;a<10;a++)
 			node->child[a] = NULL;
		node->type = rule[i];
		node->parent = tr;
		//node->ruleno = r;
		if(node->type == 't')
			node->tk = tkpt;
		else
		{
			node->tk = NULL;
		}
		i = i + 1;
		node->no = rule[i];
		i = i + 1;
		tr->child[j] = node;
		//printf("as,%d\n",tr->child[j]->visited);

		j = j + 1;
	}
}

void parse()
{
	//printf("\nbla%d",tk.no);
	if (st == NULL)
	{
		return;
	}
	else if(st->type == 'N')
	{
		int rule;
		rule = parsetable[st->no][tk.no] - 1;
		if(rule == -1)
			printf("here");
		pop(st);
		push(rule);
		addnode(rule);
		tr->visited = 1;
		tr->ruleno = rule;
		int i = tracechild();
		if(i != -1)
		{
			tr = tr->child[i];
			parse(tk);
		}
		else
		{
			tr = tr->parent;
			//parse(tk);
		}

	}
	else
	{
		if(tk.no == st->no)
		{
			pop(st);
			tr->visited = 1;
			tr->tk = tkpt;
			assigntoken();
		}
		else if(st->no == 61)
		{
			pop(st);
			tr->visited = 1;
			tr = tr->parent;
			//tr = tr->parent;
			// int i = tracechild();
			// tr = tr->child[i];
			//parse(tk);
		}
		else
		{
			pop(st);
			printf("Error\n");
		}
		
	}

}
void assigntoken()
{
	tkpt = nexttoken();
	tk.no = tkpt->no;
	tk.lineno = tkpt->lineno;
	tk.n = tkpt->n;
	tk.text = tkpt->text;
	tk.f = tkpt->f;
}

void generateptree()
{
	trinit();
	stinit();
	int rule;
	assigntoken();
	//tk.no=0;
	// char str[10]="N0=T1";
	// strcpy(&parsetable[0][0],str);
	//printf("%d %s\n",parsetable[st->no][tk.no],rulelist[parsetable[st->no][tk.no]]);
	rule = parsetable[st->no][tk.no]-1;
	pop(st);
	push(rule);
	addnode(rule);
	tr->visited = 1;
	tr = tr->child[0];
	//assigntoken();
	//tk.no=1;
	while(tk.no != -1)
	{
		parse();
		//printf("\nbla\n");
		while(tracechild() == -1)
		{
			if(tr->parent != NULL)
				tr = tr->parent;
			else
				break;
		}
		int i = tracechild();
		if(i != -1)
		{
		 	tr = tr->child[i];
		 	//assigntoken();
		 	//tk.no=-1;
		}
		else
		{
			break;
		}

	}
	tk_count = 0;
	tr = root;
}

void printtree()
{
	printf("Root: %c%d\n",t1->type,t1->no);
	for(int j=0;j<10;j++)
	{
		if(t1->child[j] != NULL)
		{
			t1 = t1->child[j];
			while(t1->parent != NULL)
			{
				if(t1->parent != NULL)
					if(t1->type == 't')
					printf("Child of %c%d: %c%d\n",t1->parent->type,t1->parent->no,t1->type,t1->no);
				t1->visited = 0;
				while(ptracechild() == -1)
				{
					if(t1->parent != NULL)
						t1 = t1->parent;
					else
						break;
				}
				int i = ptracechild();
				if(i != -1)
				{
					t1 = t1->child[i];
					//assigntoken();
					//tk.no=-1;
				}
			}
		}
	}
}

// void main()
// {
// 	generateptree();
// }