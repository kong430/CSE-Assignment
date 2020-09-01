#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE* wfp;
FILE* rfp;

typedef struct ListNode *Position;
typedef Position List;
typedef struct HashTbl *HashTable;

typedef struct ListNode
{
	int element;
	int index;
}ListNode;

typedef struct HashTbl
{
	int TableSize;
	List TheLists;
}HashTbl;

HashTable makeHashTable(int size);
void Insert(HashTable H, int value, int solution);
void delete(HashTable H, int value, int solution);
int find(HashTable H, int value, int solution);
void print(HashTable H);
int Hash(HashTable H, int value, int solution);

HashTable makeHashTable(int size)
{
	HashTable hash = (HashTable)malloc(sizeof(struct HashTbl)*size);
	hash->TableSize = size;
	hash->TheLists = (Position)malloc(sizeof(ListNode)*size);
	for ( int i = 0; i < size; i++ )
	{
		hash->TheLists[i].element = 0;
		hash->TheLists[i].index = i;
	}
	return hash;
}

void Insert(HashTable H, int value, int solution)
{
	if ( find(H, value, solution)!= -1) fprintf(wfp, "Already exists\n");
	else
	{
		H->TheLists[Hash(H, value, solution)].element = value;
		fprintf(wfp, "Inserted %d\n", value);
	}
}

void delete(HashTable H, int value, int solution)
{
	if ( find(H, value, solution) == -1) fprintf(wfp, "%d not exists\n", value);
	else
	{
		int delin = find(H, value, solution);
		H->TheLists[delin].element = 0;
		fprintf(wfp, "Deleted %d\n", value);
	}
}

int find(HashTable H, int value, int solution)
{
	int in = -1, i = 0;

	while ( i < H->TableSize )
	{
		if ( H->TheLists[i].element == value )
		{
			in = H->TheLists[i].index;
			i++;
		}
		else i++;
	}
	return in;
}

void print(HashTable H)
{
	for ( int i = 0; i < H->TableSize; i++ )
	{
		fprintf(wfp, "%d ", H->TheLists[i].element);
	}
	fprintf(wfp, "\n");
}

int Hash(HashTable H, int value,  int solution)
{
	int i = 0;
	if ( solution == 1 )
	{
		value = value % H->TableSize;
		while ( H->TheLists[value].element != 0 )
		{
			value = (value + 1) % H->TableSize;
		}
		return value;
	}
	else if ( solution == 2 )
	{
		int hold = value;
		value = value % H->TableSize;
		while ( H->TheLists[value].element != 0 )
		{
			value = hold;
			i++;
			value = (value + i * i) % H->TableSize;
		}
		return value;
	}
	else
	{
		int hold = value;
		value = value % H->TableSize;
		while ( H->TheLists[value].element != 0 )
		{
			value = hold;
			i++;
			value = (value + i * (7 - value % 7)) % H->TableSize;
		}
		return value;
	}
}

int main()
{
	rfp = fopen("input.txt", "r");
	wfp = fopen("output.txt", "w");

	int tcase, tbsize, x, sol;
	char* solution = (char*)malloc(sizeof(char) * 10);
	char kind;
	fscanf(rfp, "%d", &tcase);

	while ( tcase )
	{
		tcase--;
		fscanf(rfp, "%s", solution);
		fscanf(rfp, "%d\n", &tbsize);
		HashTable hash = makeHashTable(tbsize);

		if ( !strcmp(solution, "Linear") ) sol = 1;
		else if ( !strcmp(solution, "Quadratic") ) sol = 2;
		else sol = 3;
		fprintf(wfp, "%s\n", solution);

		while ( 1 )
		{
			fscanf(rfp, "%c", &kind);
			if ( kind == 'i' )
			{
				fscanf(rfp, "%d\n", &x);
				Insert(hash, x, sol);
			}
			else if ( kind == 'd' )
			{
				fscanf(rfp, "%d\n", &x);
				delete(hash, x, sol);
			}
			else if ( kind == 'f' )
			{
				fscanf(rfp, "%d\n", &x);
				if ( find(hash, x, sol) != -1 ) fprintf(wfp, "%d\n", find(hash, x, sol));
				else fprintf(wfp, "Not found\n");
			}
			else if ( kind == 'p' )
			{
				fscanf(rfp, "\n");
				print(hash);
				fprintf(wfp, "\n");
			}
			else break;
		}
		free(hash->TheLists);
		free(hash);
	}
	fclose(rfp);
	fclose(wfp);
}