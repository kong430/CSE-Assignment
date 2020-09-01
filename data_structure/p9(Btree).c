#include <stdio.h>> 
#define M 5
#define true 1
#define false 0

// BTree의 노드 구조체를 선언합니다. 
typedef struct BTreeNode* bTreeNode;
struct BTreeNode // Public과 동일한 구조체 선언입니다. 
{
	int data[M-1]; // 노드에 들어갈 자료의 배열입니다. 
	bTreeNode childPtr[M]; // 노드 포인트의 배열입니다. 
	int leaf; // 리프 노드인지 확인합니다. 
	int n; // 자료의 개수를 의미합니다. 
}*root = NULL, *np = NULL, *x = NULL;

// 노드를 초기화하는 함수입니다. 
bTreeNode init()
{
	int i;
	np = (bTreeNode)malloc(sizeof(struct BTreeNode)); // 객체를 할당합니다. 
	np->leaf = true; // 기본적으로 리프 노드입니다. 
	np->n = 0; // 자료의 개수는 0개입니다.
	for ( i = 0; i < 6; i++ )
	{
		np->childPtr[i] = NULL; // 각각의 자식 노드를 초기화해줍니다. 
	}
	return np;
}

// 현재 트리를 보여주는 순회 함수입니다. 
void traverse(bTreeNode p)
{
	int i;
	// 즉, 첫번째 자식 노드부터 가장 마지막 자식 노드까지 전부 밑으로 내려가는 것입니다. 
	for ( i = 0; i < p->n; i++ )
	{
		// 리프 노드가 아니라면 더 밑으로 내려갑니다. 
		if ( p->leaf == false )
		{
			traverse(p->childPtr[i]);
		}
		// 데이터를 출력합니다. 
		printf("%d ", p->data[i]);
	}
	// 리프 노드가 아니라면 더 밑으로 내려갑니다. 
	if ( p->leaf == false )
	{
		traverse(p->childPtr[i]);
	}
}

// n개 존재하는 데이터 배열 데이터를 정렬하는 함수입니다. 
void sort(int *p, int n)
{
	int i, j, temp;
	for ( i = 0; i < n; i++ )
	{
		for ( j = i; j <= n; j++ )
		{
			if ( p[i] > p[j] )
			{
				temp = p[i];
				p[i] = p[j];
				p[j] = temp;
			}
		}
	}
}

// 자식을 분할하는 함수입니다.
int splitChild(bTreeNode x, int i)
{

	// x노드를 분할하여 np1과 np3을 할당합니다. 
	int j, mid;
	bTreeNode np1, np3, y;

	/*
	분할된 형태는 다음과 같습니다.
	x -> 왼쪽으로 가고
	np3 -> 그 오른쪽으로 가고
	np1 -> x와 np3의 부모 노드가 됩니다.
	*/

	np3 = init();
	np3->leaf = true;

	// x의 부모 노드가 없어 새롭게 부모 노드를 만들어주는 경우입니다. 
	if ( i == -1 )
	{

		// M의 중간값을 기준으로 분할합니다. 
		mid = x->data[M / 2];
		x->data[M / 2] = 0;
		x->n--;
		np1 = init();

		// np1는 부모노드이므로 리프 노드가 아닙니다. 
		np1->leaf = false;
		x->leaf = true;
		for ( j = M / 2 + 1; j < M; j++ )
		{

			// np3는 x의 오른쪽 부분 노드를 가져갑니다. 
			np3->data[j - (M / 2 + 1)] = x->data[j];
			np3->childPtr[j - (M / 2 + 1)] = x->childPtr[j];
			np3->n++;

			// x는 반 쪼개서 왼쪽 부분 노드만 가지고 갑니다. 
			x->data[j] = 0;
			x->n--;
		}

		// x의 모든 자식 노드를 NULL로 만듭니다. 
		for ( j = 0; j < M + 1; j++ )
		{
			x->childPtr[j] = NULL;
		}
		np1->data[0] = mid;
		np1->childPtr[np1->n] = x;
		np1->childPtr[np1->n + 1] = np3;
		np1->n++;

		// 루트 노드로 설정해줍니다. 
		root = np1;
	}

	// 이미 부모 노드가 있는 경우입니다. 
	else
	{
		y = x->childPtr[i];
		mid = y->data[M / 2];
		y->data[M / 2] = 0;
		y->n--;
		for ( j = M / 2 + 1; j < M; j++ )
		{

			// np3은 x의 오른쪽 자식 부분만 가져갑니다. 
			np3->data[j - (M / 2 + 1)] = y->data[j];
			np3->n++;
			y->data[j] = 0;
			y->n--;
		}
		x->childPtr[i + 1] = y;
		x->childPtr[i + 1] = np3;
	}
	return mid;
}

// a라는 원소를 삽입하는 함수입니다. 
void insert(int a)
{
	int i, temp;
	x = root;

	// 만약에 루트 노드가 NULL이라면 
	if ( x == NULL )
	{
		root = init();
		x = root;
	}

	// 루트 노드가 NULL이 아니라면 
	else
	{

		// 현재 리프노드이고 크기가 꽉찼다면 
		if ( x->leaf == true && x->n == M )
		{
			temp = splitChild(x, -1);
			x = root;

			// 값을 이동하며 삽입될 자리를 찾습니다. 
			for ( i = 0; i < (x->n); i++ )
			{
				if ( (a > x->data[i]) && (a < x->data[i + 1]) )
				{
					i++;
					break;
				}
				else if ( a < x->data[0] )
				{
					break;
				}
				else
				{
					continue;
				}
			}
			x = x->childPtr[i];
		}

		// 리프노드가 아닐 때입니다. 
		else
		{
			// 리프 노드까지 이동합니다. 
			x = x->childPtr[i];
		}
	}
	x->data[x->n] = a;
	sort(x->data, x->n);
	x->n++;
}

int main(void)
{
	int  n, t;
	scanf("%d", &n);
	for ( int i = 0; i < n; i++ )
	{
		scanf("%d", &t);
		insert(t);
	}

	traverse(root);
	return 0;
}