#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "codegen.h"
#define BLANK ' '
#define TAB '\t'
#define MAX 100000

long int popsym();
long int eval_pre();
char infix[MAX], prefix[MAX];
long int stack[MAX];
int top;
int isempty();
int white_space(char symbol);

void infix_to_prefix();
int priority(char symbol);
void pushsym(long int symbol);
long int popsym();
long int eval_pre();
#include <stdio.h>
#include <stdlib.h>

// Represents a node of the required tree
typedef struct node
{
	char data;
	struct node *left, *right;
} node;

// Function to recursively build the expression tree
char *add(node **p, char *a)
{

	// If its the end of the expression
	if (*a == '\0')
		return '\0';

	while (1)
	{
		char *q = "null";
		if (*p == NULL)
		{

			// Create a node with *a as the data and
			// both the children set to null
			node *nn = (node *)malloc(sizeof(node));
			nn->data = *a;
			nn->left = NULL;
			nn->right = NULL;
			*p = nn;
		}
		else
		{

			// If the character is an operand
			if (*a >= 'a' && *a <= 'z')
			{
				return a;
			}

			// Build the left sub-tree
			q = add(&(*p)->left, a + 1);

			// Build the right sub-tree
			q = add(&(*p)->right, q + 1);

			return q;
		}
	}
}

// Function to print the infix expression for the tree
void inr(node *p) // recursion
{
	if (p == NULL)
	{
		return;
	}
	else
	{
		inr(p->left);
		printf("%c ", p->data);
		inr(p->right);
	}
}

// Function to print the postfix expression for the tree
void postr(node *p, int i)
{
	if (p == NULL)
	{
		return;
	}
	else
	{
		postr(p->left, 0);
		fprintf(fp, "mov leftexpr, exprleft");
		postr(p->right, 1);
		fprintf(fp, "mov rightexpr, exprright");
		printf("%c ", p->data);
		switch (p->data)
		{
		case '+':
			fprintf(fp, "add exprleft, exprright");
		case '-':
			fprintf(fp, "sub exprleft,exprright");
		case '*':
			fprintf(fp, "mov eax, exprleft");
			fprintf(fp, "mul eax, exprright");
			fprintf(fp, "mov exprleft, eax");
		case '/':
			fprintf(fp, "mov eax, exprleft");
			fprintf(fp, "div eax, exprright");
			fprintf(fp, "mov exprleft, eax");
		default:
			fprintf(fp, "mov exprleft, %s", p->data);
		}
		if (i == 1)
			fprintf(fp, "mov exprright, exprleft");
	}
}

void exprasm()
{
	top = -1;
	gets(infix);
	infix_to_prefix();
	node *s = NULL;
	add(&s, prefix);
	postr(s, 0);
} /*End of main()*/

void infix_to_prefix()
{
	int i, j, p, n;
	char next;
	char symbol;
	char temp;
	n = strlen(infix);
	p = 0;

	for (i = n - 1; i >= 0; i--)
	{
		symbol = infix[i];
		if (!white_space(symbol))
		{
			switch (symbol)
			{
			case ')':
				pushsym(symbol);
				break;
			case '(':
				while ((next = popsym()) != ')')
					prefix[p++] = next;
				break;
			case '+':
			case '-':
			case '*':
			case '/':
			case '%':
				while (!isempty() && priority(stack[top]) > priority(symbol))
					prefix[p++] = popsym();
				pushsym(symbol);
				break;
			default: /*if an operand comes*/
				prefix[p++] = symbol;
			}
		}
	}
	while (!isempty())
		prefix[p++] = popsym();
	prefix[p] = '\0'; /*End prefix with'\0' to make it a string*/

	for (i = 0, j = p - 1; i < j; i++, j--)
	{
		temp = prefix[i];
		prefix[i] = prefix[j];
		prefix[j] = temp;
	}
} /*End of infix_to_prefix()*/

/* This function returns the priority of the operator */
int priority(char symbol)
{
	switch (symbol)
	{
	case ')':
		return 0;
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
	case '%':
		return 2;
	default:
		return 0;
	} /*End of switch*/
} /*End of priority()*/

void pushsym(long int symbol)
{
	top = top + 1;
	stack[top] = symbol;
} /*End of pushsym()*/

long int popsym()
{
	if (top == -1)
	{
		return stack[++top];
	}
	return (stack[top--]);
} /*End of popsym()*/
int isempty()
{
	if (top == -1)
		return 1;
	else
		return 0;
}

int white_space(char symbol)
{
	if (symbol == BLANK || symbol == TAB || symbol == '\0')
		return 1;
	else
		return 0;
} /*End of white_space()*/

long int eval_pre()
{
	long int a, b, temp, result;
	int i;

	for (i = strlen(prefix) - 1; i >= 0; i--)
	{
		if (prefix[i] <= '9' && prefix[i] >= '0')
			pushsym(prefix[i] - 48);
		else
		{
			b = popsym();
			a = popsym();
			switch (prefix[i])
			{
			case '+':
				temp = b + a;
				break;
			case '-':
				temp = b - a;
				break;
			case '*':
				temp = b * a;
				break;
			case '/':
				temp = b / a;
				break;
			case '%':
				temp = b % a;
				break;
			}
			pushsym(temp);
		}
	}
	result = popsym();
	return result;
} /*End of eval_pre */