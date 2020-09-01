#include<stdio.h>
#include<stdlib.h>

FILE* rfp;
FILE* wfp;

typedef struct HeapStruct* heap_struct;
struct HeapStruct
{
	int Capacity;
	int Size;
	int* elements;
};

heap_struct Make_heap(heap_struct H, int num)
{
	H->elements = (int*)malloc(sizeof(int)*(num + 1));
	H->Capacity = num;
	H->Size = 0;
	return H;
}

int IsFull(heap_struct H)
{
	if ( H->Capacity <= H->Size ) return 1;
	else return 0;
}

int Exist(int x, heap_struct H)
{
	int i = H->Size;
	while ( i != 0 )
	{
		if ( H->elements[i] == x )
		{
			return 1;
		}
		i--;
	}
	return 0;
}

void Insert(int x, heap_struct H)
{
	int i = 0;
	if ( IsFull(H) )
	{
		fprintf(wfp, "heap is full\n");
		return;
	}
	else if (Exist(x, H) )
	{
		fprintf(wfp, "%d is already in the heap.\n", x);
		return;
	}
	else
	{
		i = ++H->Size;
		while ( i != 1 && x > H->elements[i / 2] )
		{
			H->elements[i] = H->elements[i / 2];
			i /= 2;
		}
		H->elements[i] = x;
	}
	fprintf(wfp, "insert %d\n", x);
}

void Find(int x, heap_struct H)
{
	int i = H->Size;
	while ( i != 0 )
	{
		if ( H->elements[i] == x )
		{
			fprintf(wfp, "%d is in the heap.\n", x);
			return;
		}
		i--;
	}
	fprintf(wfp, "%d is not in the heap.\n", x);
}

void Print(heap_struct H)
{
	for ( int i = 1; i <= H->Size; i++ )
	{
		fprintf(wfp, "%d ", H->elements[i]);
	}
	fprintf(wfp, "\n");
}

int main()
{
	rfp = fopen("input.txt", "r");
	wfp = fopen("output.txt", "w");

	int num, ele;
	char kind;
	fscanf(rfp, "%d\n", &num);

	heap_struct hs = (heap_struct)malloc(sizeof(struct HeapStruct)*(num + 1));
	hs = Make_heap(hs, num);
	
	fscanf(rfp, "%c", &kind);

	while (1)
	{
		if ( kind == 'i' )
		{
			fscanf(rfp, "%d\n", &ele);
			Insert(ele, hs);
		}
		else if ( kind == 'f' )
		{
			fscanf(rfp, "%d\n", &ele);
			Find(ele, hs);
		}
		else if ( kind == 'p' )
		{
			Print(hs);
			break;
		}
		fscanf(rfp, "%c ", &kind);
	}
	free(hs);
	fclose(rfp);
	fclose(wfp);
}