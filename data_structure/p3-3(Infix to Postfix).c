#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define EmptyTOS (-1)
FILE* rfp;
FILE* wfp;

char* wh;
int su;

typedef struct
{
	int Capacity;
	int TopOfStack;
	char *Array;
}Stack;

//createstack
Stack* CreateStack(int MaxElements)
{
	Stack *S;
	S = malloc(sizeof(Stack));
	S->Array = (char*)malloc(sizeof(char)*MaxElements); //sizeof S
	S->Capacity = MaxElements;
	S->TopOfStack = EmptyTOS;
	return S;
}

/*Stack* createstack_int (int maxelements)
{
	Stack *S;
	S = malloc(sizeof(Stack));
	S->Array = (int*)malloc(sizeof(int)*maxelements); //sizeof s
	S->Capacity = maxelements;
	S->TopOfStack = EmptyTOS;
	return S;
}*/

//isempty
int IsEmpty(Stack *S)
{
	if ( S->TopOfStack == EmptyTOS ) return 1;
	else return 0;
}

//isfull
int IsFull(Stack *S)
{
	if ( S->TopOfStack - 1 >= S->Capacity ) return 1;
	else return 0;
}

//push
void Push(char X, Stack *S)
{
	if ( IsFull(S) == 1 )
		fprintf(wfp, "Full\n");
	else
	{
		S->TopOfStack++;
		S->Array[(S->TopOfStack)] = X;
		return;
	}
}

//pop
char Pop(Stack *S)
{
	if ( IsEmpty(S) == 1 )
	{
		fprintf(wfp, "Empty\n");
		return 0;
	}
	else
	{
		return S->Array[S->TopOfStack--];
	}
}

//precedence
int Pre(char ch)
{
	if ( ch == '(' || ch == ')' )
		return 0;
	if ( ch == '+' || ch == '-' )
		return 1;
	if ( ch == '*' || ch == '/' || ch == '%' )
		return 2;
	return -1;
}

//topofstack
char Top(Stack *S)
{
	if ( !IsEmpty(S) )
	{
		return S->Array[S->TopOfStack];
	}
}

//infix_to_postfix
int infix_to_postfix(char* ch)
{
	char top;
	int ob1, ob2;
	int value = 0;
	int len = strlen(ch);
	Stack *st;
	Stack *post;
	st = CreateStack(100);
	post = CreateStack(100);

	for ( int i = 0; i < len; i++ )
	{
		if ( ch[i] == '+' || ch[i] == '-' || ch[i] == '*' || ch[i] == '/' || ch[i] == '%' )
		{
			while ( !IsEmpty(st) && Pre(Top(st)) >= Pre(ch[i]) )
			{
				top = Pop(st);
				fprintf(wfp, "%c", top);
				value = evaluation(top, st, post);
				continue;
			}
			Push(ch[i], st);
		}
		else if ( ch[i] == '(' )
		{
			Push(ch[i], st);
			continue;
		}
		else if ( ch[i] == ')' )
		{
			top = Pop(st);
			while ( top != '(' )
			{
				fprintf(wfp, "%c", top);
				value = evaluation(top, st, post);
				top = Pop(st);
			}
			continue;
		}
		else
		{
			int int_kind = ch[i] - '0';
			Push(int_kind, post);
			fprintf(wfp, "%c", ch[i]);
			continue;
		}
	}
	while ( !IsEmpty(st) )
	{
		top = Pop(st);
		fprintf(wfp, "%c", top);
		value = evaluation(top, st, post);
	}

	free(st->Array);
	free(post->Array);
	free(st);
	free(post);

	return value;
}

//evaluation
int evaluation(char topof, Stack *cha, Stack* num)
{
	int tot;
	int ob2 = Pop(num);
	int ob1 = Pop(num);
	if ( topof == '+' ) tot = ob1 + ob2, Push(tot, num);
	else if ( topof == '-' ) tot = ob1 - ob2, Push(tot, num);
	else if ( topof == '*' ) tot = ob1 * ob2, Push(tot, num);
	else if ( topof == '/' ) tot = ob1 / ob2, Push(tot, num);
	else if ( topof == '%' ) tot = ob1 % ob2, Push(tot, num);
	return tot;
}

int main()
{
	int cnt = -1;
	int value = 0;
	rfp = fopen("input.txt", "r");
	wfp = fopen("output.txt", "w");
	wh = (char*)malloc(sizeof(char) * 100);

	while ( wh[cnt++] != '#' )
	{
		fscanf(rfp, "%c", &wh[cnt]);
	}
	wh[--cnt] = '\0';

	fprintf(wfp, "Infix Form : ");

	for ( int i = 0; i < cnt; i++ )
	{
		fprintf(wfp, "%c", wh[i]);
	}

	fprintf(wfp, "\nPostfix Form : ");
	value = infix_to_postfix(wh);
	fprintf(wfp, "\nEvaluation Result : %d", value);
	
	fclose(rfp);
	fclose(wfp);
	free(wh);
}