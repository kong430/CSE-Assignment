#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct Node* PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef struct
{
	int studentID;
	char* studentName;
}ElementType;

struct Node
{
	ElementType element;
	PtrToNode next;
};

void Insert(ElementType X, List L, Position P)
{
	//�й������� ����
	P = L;
	L = (PtrToNode*)malloc(sizeof(PtrToNode));
	L->element.studentID = X.studentID;
	L->element.studentName = (char*)malloc(sizeof(char) * 30);
	strcpy(P->element.studentName, X.studentName);
	L->next = NULL;
	int in = 0;
	while ( in != 1 )
	{
		if ( P->next == NULL )
		{
			P->next = L;
			in = 1;
		}
		else if ( P->next->element.studentID > L->element.studentID )
		{
			L->next = P->next;
			P->next = L;
			in = 1;
		}
		P = P->next;
	}
}

void Delete(ElementType X, List L)
{
	Position P, Tmp;
	P = FindPrevious(X, L);
	if ( !IsLast(P, L) )
	{
		Tmp = P->next;
		P->next = Tmp->next;
		free(Tmp);
	}
}

Position Find(ElementType X, List L)
{
	Position P;
	P = L->next;
	while ( P != NULL && P->element.studentID != X.studentID )
	{
		P = P->next;
	}
	return P;
}


void PrintList(List L, FILE* F)
{
	fprintf(F, "-----List-----\n");
	if ( L->next == NULL )
	{
		fprintf(F, "No one in the list\n"); //list�� �ƹ��� ���� ��
	}
	else
	{
		while ( L->next != NULL )
		{
			fprintf(F, "%d %s\n", L->element.studentID, L->element.studentName);
			L = L->next;
		}
	}
	fprintf(F, "--------------\n");
}
Position FindPrevious(ElementType X, List L)
{
	Position P;
	P = L;
	while ( P->next != NULL && P->next->element.studentID != X.studentID )
	{
		P = P->next;
	}
	return P;
}

int IsLast(Position P, List L)
{
	return P->next == NULL;
}
//Delete List, IsEmpty, MakeEmpty ����
//Current List ��� ���� �Լ� ���� �߰�
void Current(ElementType X, List L, FILE* F)
{
	Position P;
	fprintf(F, "Current List > %d %s", X.studentID, X.studentName);
	P = L->next;
	while ( P->next != NULL )
	{
		fprintf(F, "Current List > -%d %s", X.studentID, X.studentName);
		P = P->next;
	}
}
int main()
{
	ElementType *el = (ElementType*)malloc(sizeof(ElementType));

	FILE* rfp = fopen("input.txt", "r");

	char kind;

	List* mylist = (List*)malloc(sizeof(List));//head
	Position po;

	FILE* wfp = fopen("output.txt", "w");
	fscanf(rfp, "%c", &kind);
	while ( kind != 'p' )
	{
		if ( kind == "i" )
		{
			fscanf(rfp, "%d", el->studentID);
			fgets(el->studentName, 31, rfp); //�̸��� �ִ� ���̴� 30
			if ( find(*el, mylist) == NULL )
			{
				Insert(*el, mylist, po);
				fprintf(wfp, "Insertion Success : %d\n", el->studentID);
			}
			else fprintf(wfp, "Error!(already in the list)\n");
			//You need to print an error message
			Current(*el, mylist, wfp);
			fscanf(rfp, "%c", &kind);
		}
		else if ( kind == "d" )
		{
			fscanf(rfp, "%d", el->studentID);
			if ( find(*el, mylist) != NULL )
			{
				delete(*el, mylist);
				fprintf(wfp, "Deletion Success : %d\n", el->studentID);
			}
			else fprintf(wfp, "No such student id.\n");
			//print "No such student id."
			Current(*el, mylist, wfp);
			fscanf(rfp, "%c", &kind);
		}
		else if ( kind == "f" )
		{
			fscanf(rfp, "%d", el->studentID);
			if ( find(*el, mylist) != NULL )
			{
				fprintf(wfp, "Find Success : %d %s\n", el->studentID, el->studentName);
			}
			else fprintf(wfp, "Find %s Failed. There is no student ID\n", el->studentID);
			fscanf(rfp, "%c", &kind);
		}
		else if ( kind == "p" )
		{
			PrintList(wfp, mylist);
		}
	}
	fclose(rfp);
	fclose(wfp);
}