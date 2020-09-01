#include <stdio.h>
#include <stdlib.h>
#define INF 99999

FILE* rfp;
FILE* wfp;

typedef struct Node
{
	int vertex, weight;
	struct node * next;
}Node;

typedef struct Vertex
{
	int vertex, dist;
}Vertex;

// Follows head insertion to give O(1) insertion
Node* addEdge(Node* head, int vertex, int weight)
{
	Node* newNode = (Node*)malloc(sizeof(Node));

	newNode->vertex = vertex;
	newNode->weight = weight;
	newNode->next = head;

	return newNode;
}

// Applies the heapify procedure - O(log N)
void heapify(Vertex minHeap[], int size, int i, int pos[])
{
	Vertex temp;

	while ( (2 * i) <= size )
	{
		if ( (2 * i) + 1 > size )
		{
			if ( minHeap[i].dist > minHeap[2 * i].dist )
			{
				pos[minHeap[i].vertex] = 2 * i;
				pos[minHeap[2 * i].vertex] = i;

				temp = minHeap[i];
				minHeap[i] = minHeap[2 * i];
				minHeap[2 * i] = temp;
			}

			break;
		}

		if ( minHeap[i].dist > minHeap[2 * i].dist || minHeap[i].dist > minHeap[2 * i + 1].dist )
		{
			if ( minHeap[2 * i].dist <= minHeap[(2 * i) + 1].dist )
			{
				pos[minHeap[i].vertex] = 2 * i;
				pos[minHeap[2 * i].vertex] = i;

				temp = minHeap[2 * i];
				minHeap[2 * i] = minHeap[i];
				minHeap[i] = temp;

				i = 2 * i;
			}
			else if ( minHeap[2 * i].dist > minHeap[(2 * i) + 1].dist )
			{
				pos[minHeap[i].vertex] = 2 * i + 1;
				pos[minHeap[2 * i + 1].vertex] = i;

				temp = minHeap[(2 * i) + 1];
				minHeap[(2 * i) + 1] = minHeap[i];
				minHeap[i] = temp;

				i = (2 * i) + 1;
			}
		}
		else
		{
			break;
		}
	}
}

// Build Heap Procedure - O(N)
void buildHeap(Vertex minHeap[], int size, int pos[])
{
	int i;

	for (i = size / 2; i >= 1; --i )
	{
		heapify(minHeap, size, i, pos);
	}
}

// Searches for a node in the Heap in O(1) time and decreases its value
// Then calls Heapify() on it's parent to adjust heap -> totally takes O(log N) time
void decreaseKey(Vertex minHeap[], Vertex newNode, int pos[])
{
	minHeap[pos[newNode.vertex]].dist = newNode.dist;

	int i = pos[newNode.vertex];
	Vertex temp;

	while ( i > 1 )
	{
		if ( minHeap[i / 2].dist > minHeap[i].dist )
		{
			pos[minHeap[i].vertex] = i / 2;
			pos[minHeap[i / 2].vertex] = i;

			temp = minHeap[i / 2];
			minHeap[i / 2] = minHeap[i];
			minHeap[i] = temp;

			i = i / 2;
		}
		else
		{
			break;
		}
	}
}

// Removes and Returns the topmost element - O (log N)
Vertex extractMin(Vertex minHeap[], int size, int pos[])
{
	pos[minHeap[1].vertex] = size;
	pos[minHeap[size].vertex] = 1;

	Vertex min = minHeap[1];

	minHeap[1] = minHeap[size];
	--size;
	heapify(minHeap, size, 1, pos);

	return min;
}

// Dijkstra's Algorithm function
void dijkstra(Node * adjacencyList[], int vertices, int startVertex, int distances[], int parent[])
{
	int i;
	Vertex min;
	Vertex* priorityQueue = (Vertex*)malloc(sizeof(Vertex)*(vertices + 1));
	int* pos = (int*)malloc(sizeof(int)*(vertices + 1));
	
	for ( i = 1; i <= vertices; ++i )
	{
		distances[i] = INF;
		parent[i] = 0;
		priorityQueue[i].dist = INF;
		priorityQueue[i].vertex = i;
		pos[i] = priorityQueue[i].vertex;
	}

	distances[startVertex] = 0;
	priorityQueue[startVertex].dist = 0;
	buildHeap(priorityQueue, vertices, pos);

	for ( i = 1; i <= vertices; ++i )
	{
		min = extractMin(priorityQueue, vertices, pos);
		Node * trav = adjacencyList[min.vertex];
		while ( trav != NULL )
		{
			int u = min.vertex, v = trav->vertex, w = trav->weight;

			if ( distances[u] != INF && distances[v] > distances[u] + w )
			{
				distances[v] = distances[u] + w;
				parent[v] = u;
				
				Vertex change;

				change.vertex = v;
				change.dist = distances[v];
				decreaseKey(priorityQueue, change, pos);
			}
			trav = trav->next;
		}
	}
}

// Recursively looks at a vertex's parent to print the path
void printPath(int parent[], int vertex, int startVertex)
{
	if ( vertex == startVertex )
	{	
		printf("%d ", startVertex);
		return;
	}
	else if ( parent[vertex] == 0 )
	{	
		printf("%d ", vertex);
		return;
	}
	else
	{	
		printPath(parent, parent[vertex], startVertex);
		printf("%d ", vertex);
	}
}

int main()
{
	rfp = fopen("input.txt", "r");
	wfp = fopen("output.txt", "w");

	char buffer[100];
	char *node[100] = { NULL };
	*node = (char**)malloc(sizeof(char*) * 100);
	char* ptr;
	ptr = (char*)malloc(sizeof(char) * 100);
	fgets(buffer, 100, rfp);
	ptr = strtok(buffer, " ");
	char node2[100];
	int i = 0;

	while ( ptr != NULL )
	{
		node[i] = ptr;
		node2[(*ptr - 48)] = i;
		i++;
		ptr = strtok(NULL, " ");
	}

	Node** adjacencyList = (Node**)malloc(sizeof(Node*)*(i + 1));
	for ( int j = 0; j <=i; ++j )
	{
		adjacencyList[j] = (Node*)malloc(sizeof(Node));
	}

	int* distances = (int*)malloc(sizeof(int)*(i + 1));
	int* parent = (int*)malloc(sizeof(int)*(i + 1));
	
	for ( int j = 0; j <= i; ++j )
	{
		adjacencyList[j] = NULL;
	}

	int cnt = 0, a, b, c;
	int start, end;
	char tmp = 0;

	while ( !feof(rfp) )
	{
		if ( tmp == '\n' )
		{
			fscanf(rfp, "%d %d", &start, &end);
			break;
		}
		fscanf(rfp, "%d-%d-%d", &a, &b, &c);
		adjacencyList[a] = addEdge(adjacencyList[a], b, c);
		tmp = fgetc(rfp);
	}
	dijkstra(adjacencyList, i, start, distances, parent);
	printPath(parent, end, start);
}