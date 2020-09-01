#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE* rfp;
FILE* wfp;

typedef struct AVLNode* Position;
typedef struct AVLNode* AVLTree;

struct AVLNode
{
	int element;
	AVLTree left;
	AVLTree right;
	int height;
};

int Height(Position P);
AVLTree Insert(int X, AVLTree T);
Position SingleRotateWithLeft(Position K2);
Position SingleRotateWithRight(Position K2);
Position DoubleRotateWithLeft(Position K2);
Position DoubleRotateWithRight(Position K2);

int Max(int a, int b)
{
	if ( a > b ) return a;
	else return b;
}

int Height(Position P)
{
	if ( P == NULL )
		return -1;
	else return P->height;
}

Position SingleRotateWithLeft(Position K2)
{
	Position K1;
	K1 = K2->left;
	K2->left = K1->right;
	K1->right = K2;

	K2->height = Max(Height(K2->left), Height(K2->right)) + 1;
	K1->height = Max(Height(K1->left), K2->height) + 1;

	return K1;
}

Position SingleRotateWithRight(Position K2)
{
	Position K1;
	K1 = K2->right;
	K2->right = K1->left;
	K1->left = K2;

	K2->height = Max(Height(K2->left), Height(K2->right)) + 1;
	K1->height = Max(Height(K1->right), K2->height) + 1;

	return K1;
}

Position DoubleRotateWithLeft(Position K3)
{
	K3->left = SingleRotateWithRight(K3->left);
	return SingleRotateWithLeft(K3);
}

Position DoubleRotateWithRight(Position K3)
{
	K3->right = SingleRotateWithLeft(K3->right);
	return SingleRotateWithRight(K3);
}

AVLTree Insert(int X, AVLTree T)

{
	if ( T == NULL )
	{
		T = (AVLTree)malloc(sizeof(struct AVLNode));
		T->element = X;
		T->height = 0;
		T->left = T->right = NULL;
	}
	else if ( X < T->element )
	{
		T->left = Insert(X, T->left);
		if ( Height(T->left) - Height(T->right) == 2 )
		{
			if ( X < T->left->element ) T = SingleRotateWithLeft(T);
			else T = DoubleRotateWithLeft(T);
		}
	}
	else if ( X > T->element )
	{
		T->right = Insert(X, T->right);
		if ( Height(T->right) - Height(T->left) == 2 )
		{
			if ( X > T->right->element ) T = SingleRotateWithRight(T);
			else T = DoubleRotateWithRight(T);
		}
	}
	T->height = Max(Height(T->left), Height(T->right)) + 1;
	return T;
}

AVLTree Find(int num, AVLTree T)
{
	if ( T == NULL ) return NULL;
	if ( num < T->element )
		return Find(num, T->left);
	else if ( num > T->element )
		return Find(num, T->right);
	else return T;
}

void PrintInorder(AVLTree T)
{
	if ( T )
	{
		PrintInorder(T->left);
		fprintf(wfp, "%d(%d) ", T->element, T->height);
		PrintInorder(T->right);
	}
}

int main()
{
	rfp = fopen("input.txt", "r");
	wfp = fopen("output.txt", "w");
	
	AVLTree t1 = NULL;

	int num;
	fscanf(rfp, "%d", &num);
	t1 = Insert(num, t1);
	PrintInorder(t1);
	fprintf(wfp, "\n");

	while ( 1 )
	{
		if ( feof(rfp) ) break;
		fscanf(rfp, "%d", &num);
		
		if ( Find(num, t1) )
		{
			fprintf(wfp, "%d already in the tree!\n", num);
		}
		else
		{
			t1 = Insert(num, t1);
			PrintInorder(t1);
			fprintf(wfp, "\n");
		}
	}
}
