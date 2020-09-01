#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE* rfp;
FILE* wfp;

int* indegree;
int sort[100];

typedef struct Graph* graph;
typedef struct Queue* queue;
struct Graph
{
	int size;
	int* node;
	int** matrix;
};

struct Queue
{
	int* key;
	int first;
	int rear;
	int qsize;
	int max_queue_size;
};

graph CreateGraph(int gp_size);
int* Indegree(graph gp);
void DeleteGraph(graph gp);
void InsertEdge(graph G, int a, int b);
void Topsort(graph G);
queue MakeNewQueue(int X);
void DeleteQueue(queue q);
int queue_full(queue queue);
int queue_empty(queue queue);
void Enqueue(queue q, int X);
int Dequeue(queue q);

graph CreateGraph(int gp_size)
{
	graph gp = (graph)malloc(sizeof(struct Graph));
	gp->size = gp_size;
	gp->node = (int*)malloc(sizeof(int)*gp_size + 1);
	gp->matrix = (int**)malloc(sizeof(int*)*(gp_size+1));
	for ( int i = 0; i < gp_size; i++ )
	{
		gp->matrix[i] = (int*)malloc(sizeof(int)*(gp_size+1));
		memset(gp->matrix[i], 0, sizeof(int)*(gp_size+1));
	}
	return gp;
}

int* Indegree(graph gp)
{
	indegree = (int*)malloc(sizeof(int) * 100);
	memset(indegree, 0, sizeof(int)*(100));
	for ( int i = 0; i < gp->size; i++ )
	{
		for ( int j = 0; j < gp->size; j++ )
		{
			indegree[i] += gp->matrix[j][i];
		}
	}
	return indegree;
}

void DeleteGraph(graph gp)
{
	for (int i = 0; i < gp->size; i++ ) free(gp->matrix[i]);
	free(gp->matrix);
	free(gp);
}

void InsertEdge(graph G, int a, int b)
{
	G->matrix[a][b] = 1;
}

void Topsort(graph G)
{
	queue q;
	q = MakeNewQueue(G->size);
	int* node2 = (int*)malloc(sizeof(int)*G->size);
	int* node3 = (int*)malloc(sizeof(int)*G->size);
	int cnt = 0;

	for ( int i = 0; i < G->size; i++ )
	{
		int t = G->node[i];
		node2[t] = i;
		if ( indegree[i] == 0 )
		{
			node3[cnt] = G->node[i];
			cnt++;
		}
	}
	if ( cnt > 1 )
	{
		for ( int j = 0; j < cnt - 1; j++ )
		{
			if ( node3[j] > node3[j + 1] )
			{
				int tmp;
				tmp = node3[j];
				node3[j] = node3[j + 1];
				node3[j + 1] = tmp;
			}
		}
	}
	for ( int j = 0; j < cnt; j++ )	Enqueue(q, node3[j]);

	int* node4 = (int*)malloc(sizeof(int)*G->size);
	for ( int i = 0; i < G->size; i++ )
	{
		int v = Dequeue(q);
		sort[i] = v;
		int cnt2 = 0, tmp;
		for ( int j = 0; j < G->size; j++ )
		{
			if ( G->matrix[node2[v]][j] != 0 )
			{
				indegree[j]--;
				if ( indegree[j] == 0 )
				{
					node4[cnt2] = G->node[j];
					cnt2++;
				}
			}
		}
		if ( cnt2 > 1 )
		{
			for ( int j = 0; j < cnt2; j++ )
			{
				if ( node4[j] > node4[j + 1] )
				{
					tmp = node4[j];
					node4[j] = node4[j + 1];
					node4[j + 1] = tmp;
				}
			}
		}
		for ( int j = 0; j < cnt2; j++ )
		{
			Enqueue(q, node4[j]);
		}
	}
	DeleteQueue(q);
}

queue MakeNewQueue(int X)
{
	queue q;
	q = (queue)malloc(sizeof(struct Queue));
	q->key = (int*)malloc(sizeof(int)*X);
	q->max_queue_size = X;
	q->qsize = 0;
	q->rear= -1;
	q->first = 0;
	return q;
}

void DeleteQueue(queue q)
{
	free(q->key);
	free(q);
}

int queue_full(queue q)
{
	if ( q->qsize == q->max_queue_size )
		return 1;
	return 0;
}

//큐 포인터를 인자로 받아 queue가 비어있는지 확인하는 함수
int queue_empty(queue q)
{
	if ( q->first > q->rear )
		return 1;
	return 0;
}

//큐 포인터와 정수를 인자로 받아 정수를 큐에 enqueue하는 함수
void Enqueue(queue q, int X)
{
	if ( queue_full(q) == 1 )
	{
		return;
	}
	else
	{
		q->key[++(q->rear)] = X;
		(q->qsize)++;
		return;
	}
}

//큐 포인터를 인자로 받아 큐에서 dequeue하는 함수
int Dequeue(queue q)
{
	int front = q->key[q->first];
	q->first++;
	return  front;
}

int main()
{
	rfp = fopen("input.txt", "r");
	wfp = fopen("output.txt", "w");

	graph gp;

	char buffer[100];
	char *node[100] = { NULL };
	*node = (char**)malloc(sizeof(char*) * 100);
	char* ptr;
	ptr = (char*)malloc(sizeof(char) * 100);
	fgets(buffer, 100, rfp);
	ptr = strtok(buffer, " ");
	char node2[100];

	int i = 0;
	while (ptr!=NULL)
	{
		node[i] = ptr;
		node2[(*ptr-48)] = i;
		i++;
		ptr = strtok(NULL, " ");
	}

	gp = CreateGraph(i);

	int cnt = 0, a, b;
	while (1)
	{
		if ( node[cnt] == NULL ) break;
		gp->node[cnt] = *node[cnt] - 48;
		cnt++;
	}
	CreateGraph(cnt);

	while (!feof(rfp) )
	{
		fscanf(rfp, "%d-", &a);
		fscanf(rfp, "%d ", &b);
		gp->matrix[node2[a]][node2[b]] = 1;
	}

	for ( int i = 0; i < cnt; i++ )
	{
		if ( i == 0 )
		{
			fprintf(wfp, "  ");
			for ( int j = 0; j < cnt; j++ )
			{
				fprintf(wfp, "%d ", gp->node[j]);
			}
			fprintf(wfp, "\n");
		}
		fprintf(wfp, "%d ", gp->node[i]);
		for ( int j = 0; j < cnt; j++ )
		{
			fprintf(wfp, "%d ", gp->matrix[i][j]);
		}
		fprintf(wfp, "\n");
	}
	indegree = Indegree(gp);
	Topsort(gp);
	fprintf(wfp, "\n\nTopSort Result : ");
	for ( int i = 0; i < cnt; i++ )
	{
		fprintf(wfp, "%d ", sort[i]);
	}
	fprintf(wfp, "\n");

	DeleteGraph(gp);

	fclose(rfp);
	fclose(wfp);
}