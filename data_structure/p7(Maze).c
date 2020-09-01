#include<stdio.h>
#include<stdlib.h>
#include<time.h>

FILE* rfp;
FILE* wfp;

int n;
int cnt = 0;
int* parent;
char** maze;

/*n*n 배열의 각각의 칸을 왼쪽 위에서 오른쪽 아래로 번호를 매겼을 때,
좌표 (x,y) 에 해당하는 번호를 return*/
int getIndex(int x, int y)
{
	int index = n * (x / 2) + 1 + y / 2;
	return index;
}

//부모노드를 찾아주는 함수
int getParent(int* parent, int in)
{
	while ( parent[in] >0 ) in = parent[in];
	return in;
}

//두 set을 합치는 함수(두 부모노드를 합치는 함수)
int* Union(int* parent, char kind, int x, int y)
{
	int a, b;
	int index1, index2;
	if ( kind == '|' )
	{
		index1 = getIndex(x, y - 1);
		index2 = getIndex(x, y + 1);
		a = getParent(parent, index1);
		b = getParent(parent, index2);
	}
	else if ( kind == '-' )
	{
		index1 = getIndex(x - 1, y);
		index2 = getIndex(x + 1, y);
		a = getParent(parent, index1);
		b = getParent(parent, index2);
	}

	if ( a == b ) return parent;
	else
	{
		parent[b] = a;
		maze[x][y] = ' ';
		return parent;
	}	
}

char** MakeMaze(char** maze, int n)
{
	maze = (char**)malloc(sizeof(char*)*(2 * n + 2));
	for ( int i = 0; i <= 2 * n + 2; i++ )
	{
		maze[i] = (char*)malloc(sizeof(char)*(2 * n + 2));
	}

	for ( int i = 0; i <= 2 * n; i++ )
	{
		for ( int j = 0; j <= 2 * n; j++ )
		{
			if ( i % 2 == 0 && j % 2 == 0 ) maze[i][j] = '+';
			else if ( i % 2 == 0 && j % 2 == 1 ) maze[i][j] = '-';
			else if ( i % 2 == 1 && j % 2 == 0 ) maze[i][j] = '|';
			else maze[i][j] = ' ';
		}
	}
	maze[1][0] = ' ';
	maze[2 * n - 1][2 * n] = ' ';

	return maze;
}

int main()
{
	rfp = fopen("input.txt", "r");
	wfp = fopen("output.txt", "w");

	fscanf(rfp, "%d", &n);

	parent = (int*)malloc(sizeof(int)*(n*n+1));

	for ( int i = 1; i <=n*n; i++ )
	{
		parent[i] = 0;
	}

	MakeMaze(maze, n);

	while (1)
	{
		srand(time(0));
		int x = rand() % (2 * n);
		int y = rand() % (2 * n);

		if ( maze[x][y] != '-' && maze[x][y] != '|' ) continue;
		else if ( x != 0 && x != 2 * n && y != 0 && y != 2 * n )
		{
			if ( maze[x][y] == '-' ) parent = Union(parent, '-', x, y);
			else if ( maze[x][y] == '|' )
			{
				parent = Union(parent, '|', x, y);
			}
			for ( int i = 1; i <= n * n; i++ )
			{
				if ( parent[i] == 0 ) cnt++;
			}
			if ( cnt == 1 ) break;
			cnt = 0;
		}
	}
	for ( int i = 0; i <= 2 * n; i++ )
	{
		for ( int j = 0; j <= 2 * n; j++ )
		{
			fprintf(wfp, "%c", maze[i][j]);
		}
		fprintf(wfp, "\n");
	}
	for ( int i = 0; i <= 2 * n + 2; i++ )
	{
		free(maze[i]);
	}
	free(maze);
	free(parent);
}
