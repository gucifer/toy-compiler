#ifndef PARSEDEF
#define PARSEDEF
#define SIZEOFREAL 8
#define SIZEOFBOOL 2
#define SIZEOFNUM 4
char rulelist[108][40];
char grammar[108][150];
int first[62][20];
int follow[62][40];
int parsetable[62][62];
struct tree{
	struct tree* parent;
	struct tree* child[20];
	int no;
	char type;
	int visited;
	int ruleno;
	token* tk;
};

struct stack{
	struct stack *next;
	int no;
	char type;
};

struct ast{
    struct ast* parent;
    struct ast* child;
    struct ast* next;
    struct tree* t;
    token* tk;
	int no;
    int ruleno;
	char type;
	int visited;
	struct symTable* s;
};
// struct token{
// 	int no;
// };
struct tableentry{
    int type; //1->array   2->num   3->rnum 4->boolean 1x -> id x = 1,2,3,4
    int offset;
    char* scope;
    char* name;
	int lower;
	int upper;
};

struct symTable{
    char* name;
    struct tableentry* t[100];
	int entries;
    struct symTable* next[20];
    struct symTable* prev;
	int offset;
};

struct module{
	int inp;
	int out;
	char* name;
	int order;
};
struct tableentry* variables[100];
int numvariables = 0;
struct tableentry* arrays[100];
int numarrays = 0;
struct symTable* symlist[100];
int numsym = 0;
struct tree t;
struct stack s;
struct stack* st=&s;
struct tree* root = &t;
struct tree* tr = &t;
struct tree* t1 = &t;
int parsetable[62][62];
token tk;
token* tkpt;
struct ast* mainast;
struct ast* pass;
int nmod = 0;
struct module* modulelist[100];
#endif // !PARSEDEF
