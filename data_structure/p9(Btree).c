#include <stdio.h>> 
#define M 5
#define true 1
#define false 0

// BTree�� ��� ����ü�� �����մϴ�. 
typedef struct BTreeNode* bTreeNode;
struct BTreeNode // Public�� ������ ����ü �����Դϴ�. 
{
	int data[M-1]; // ��忡 �� �ڷ��� �迭�Դϴ�. 
	bTreeNode childPtr[M]; // ��� ����Ʈ�� �迭�Դϴ�. 
	int leaf; // ���� ������� Ȯ���մϴ�. 
	int n; // �ڷ��� ������ �ǹ��մϴ�. 
}*root = NULL, *np = NULL, *x = NULL;

// ��带 �ʱ�ȭ�ϴ� �Լ��Դϴ�. 
bTreeNode init()
{
	int i;
	np = (bTreeNode)malloc(sizeof(struct BTreeNode)); // ��ü�� �Ҵ��մϴ�. 
	np->leaf = true; // �⺻������ ���� ����Դϴ�. 
	np->n = 0; // �ڷ��� ������ 0���Դϴ�.
	for ( i = 0; i < 6; i++ )
	{
		np->childPtr[i] = NULL; // ������ �ڽ� ��带 �ʱ�ȭ���ݴϴ�. 
	}
	return np;
}

// ���� Ʈ���� �����ִ� ��ȸ �Լ��Դϴ�. 
void traverse(bTreeNode p)
{
	int i;
	// ��, ù��° �ڽ� ������ ���� ������ �ڽ� ������ ���� ������ �������� ���Դϴ�. 
	for ( i = 0; i < p->n; i++ )
	{
		// ���� ��尡 �ƴ϶�� �� ������ �������ϴ�. 
		if ( p->leaf == false )
		{
			traverse(p->childPtr[i]);
		}
		// �����͸� ����մϴ�. 
		printf("%d ", p->data[i]);
	}
	// ���� ��尡 �ƴ϶�� �� ������ �������ϴ�. 
	if ( p->leaf == false )
	{
		traverse(p->childPtr[i]);
	}
}

// n�� �����ϴ� ������ �迭 �����͸� �����ϴ� �Լ��Դϴ�. 
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

// �ڽ��� �����ϴ� �Լ��Դϴ�.
int splitChild(bTreeNode x, int i)
{

	// x��带 �����Ͽ� np1�� np3�� �Ҵ��մϴ�. 
	int j, mid;
	bTreeNode np1, np3, y;

	/*
	���ҵ� ���´� ������ �����ϴ�.
	x -> �������� ����
	np3 -> �� ���������� ����
	np1 -> x�� np3�� �θ� ��尡 �˴ϴ�.
	*/

	np3 = init();
	np3->leaf = true;

	// x�� �θ� ��尡 ���� ���Ӱ� �θ� ��带 ������ִ� ����Դϴ�. 
	if ( i == -1 )
	{

		// M�� �߰����� �������� �����մϴ�. 
		mid = x->data[M / 2];
		x->data[M / 2] = 0;
		x->n--;
		np1 = init();

		// np1�� �θ����̹Ƿ� ���� ��尡 �ƴմϴ�. 
		np1->leaf = false;
		x->leaf = true;
		for ( j = M / 2 + 1; j < M; j++ )
		{

			// np3�� x�� ������ �κ� ��带 �������ϴ�. 
			np3->data[j - (M / 2 + 1)] = x->data[j];
			np3->childPtr[j - (M / 2 + 1)] = x->childPtr[j];
			np3->n++;

			// x�� �� �ɰ��� ���� �κ� ��常 ������ ���ϴ�. 
			x->data[j] = 0;
			x->n--;
		}

		// x�� ��� �ڽ� ��带 NULL�� ����ϴ�. 
		for ( j = 0; j < M + 1; j++ )
		{
			x->childPtr[j] = NULL;
		}
		np1->data[0] = mid;
		np1->childPtr[np1->n] = x;
		np1->childPtr[np1->n + 1] = np3;
		np1->n++;

		// ��Ʈ ���� �������ݴϴ�. 
		root = np1;
	}

	// �̹� �θ� ��尡 �ִ� ����Դϴ�. 
	else
	{
		y = x->childPtr[i];
		mid = y->data[M / 2];
		y->data[M / 2] = 0;
		y->n--;
		for ( j = M / 2 + 1; j < M; j++ )
		{

			// np3�� x�� ������ �ڽ� �κи� �������ϴ�. 
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

// a��� ���Ҹ� �����ϴ� �Լ��Դϴ�. 
void insert(int a)
{
	int i, temp;
	x = root;

	// ���࿡ ��Ʈ ��尡 NULL�̶�� 
	if ( x == NULL )
	{
		root = init();
		x = root;
	}

	// ��Ʈ ��尡 NULL�� �ƴ϶�� 
	else
	{

		// ���� ��������̰� ũ�Ⱑ ��á�ٸ� 
		if ( x->leaf == true && x->n == M )
		{
			temp = splitChild(x, -1);
			x = root;

			// ���� �̵��ϸ� ���Ե� �ڸ��� ã���ϴ�. 
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

		// ������尡 �ƴ� ���Դϴ�. 
		else
		{
			// ���� ������ �̵��մϴ�. 
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