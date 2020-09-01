#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define EmptyTOS (-1)

FILE* rfp;
FILE* wfp;

int num;
char* kind;
int su;

typedef struct
{
	int Capacity;
	int TopOfStack;
	int *Array;
}Stack;

Stack* CreateStack(int MaxElements)
{
	Stack *S;
	S = malloc(sizeof(Stack));
	S->Array = (int*)malloc(sizeof(int)*MaxElements); //sizeof S
	S->Capacity = MaxElements;
	S->TopOfStack = EmptyTOS;
	return S;      // main 함수 안에서 Stack 변수를 동적할당 했으므로 CreateStack 함수의 자료형은
				   // Stack 포인터여야함
}

int IsEmpty(Stack *S)
{
	if ( S->TopOfStack == EmptyTOS ) return 1;
	else return 0;
}

int IsFull(Stack *S)
{
	if ( S->TopOfStack - 1 >= S->Capacity ) return 1;
	else return 0;
}

void Push(int X, Stack *S)
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

void Pop(Stack *S)
{
	if ( IsEmpty(S) == 1 )
	{
		fprintf(wfp, "Empty\n");
		return;
	}
	else
	{
		fprintf(wfp, "%d\n", S->Array[S->TopOfStack]);
		S->TopOfStack--;
	}
	return;
}

int main()
{
	rfp = fopen("input.txt", "r");
	wfp = fopen("output.txt", "w");
	fscanf(rfp, "%d", &num);
	Stack* st = (Stack*)malloc(sizeof(Stack));
	kind = (char*)malloc(sizeof(char)*num);
	const char* ch1 = "push";
	const char* ch2 = "pop";
	st = CreateStack(num + 1);

	for ( int i = 0; i < num; i++ )
	{
		fscanf(rfp, "%s", kind);

		if ( strcmp(kind, ch1) == 0 )
		{
			fscanf(rfp, "%d", &su);
			Push(su, st);
		}
		else if ( strcmp(kind, ch2) == 0 )
		{
			Pop(st);
		}
	}
	fclose(rfp);
	fclose(wfp);
	free(st->Array);
	free(st);
	malloc(S);
}