#include<stdio.h>
#include<stdlib.h>
#define MAX_QUEUE_SIZE 100
typedef struct
{
	int Capacity;
	int Front;
	int Rear;
	int Size;
	int *Array;
}Queue;

int rear = -1;
int front = 0;

FILE* rfp;
FILE* wfp;

int num;
char* kind;
int su;

Queue* Createqueue(int MaxElements)
{
	Queue *Q;
	Q = malloc(sizeof(Queue));
	Q->Array = (int*)malloc(sizeof(int)*MaxElements);//sizeof S
	Q->Capacity = MaxElements;
	Q->Size = 0;
	Q->Rear = -1;
	Q->Front = 0;
	return Q;
}

int queue_full(Queue* queue)
{
	if ( queue->Size == queue->Capacity )
		return 1;
	return 0;
}

int queue_empty(Queue *queue)
{
	if ( queue->Front > queue->Rear )
		return 1;
	return 0;
}

void Enqueue(Queue *queue, int num)
{
	if ( queue_full(queue) == 1 )
	{
		fprintf(wfp, "Full\n");
		return;
	}
	else
	{
		queue->Array[++(queue->Rear)] = num;
		(queue->Size)++;
		return;
	}
}

void Dequeue(Queue* queue)
{
	if ( queue_empty(queue) == 1 )
	{
		fprintf(wfp, "Empty\n");
		return;
	}
	else
	{
		fprintf(wfp, "%d\n", queue->Array[queue->Front]);
		queue->Front++;
		return;
	}
}

int main()
{
	rfp = fopen("input.txt", "r");
	wfp = fopen("output.txt", "w");
	fscanf(rfp, "%d", &num);
	Queue* qu = (Queue*)malloc(sizeof(Queue));
	kind = (char*)malloc(sizeof(char)*num);
	const char* ch1 = "enQ";
	const char* ch2 = "deQ";
	qu = Createqueue(100);

	for ( int i = 0; i < num; i++ )
	{
		fscanf(rfp, "%s", kind);

		if ( strcmp(kind, ch1) == 0 )
		{
			fscanf(rfp, "%d", &su);
			Enqueue(qu, su);
		}
		else if ( strcmp(kind, ch2) == 0 )
		{
			Dequeue(qu);
		}
	}
	fclose(rfp);
	fclose(wfp);
	free(qu);
}