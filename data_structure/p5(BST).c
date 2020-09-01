#include<stdio.h>
#include<string.h>
#include<stdlib.h>

FILE* rfp;
FILE* wfp;

typedef struct TreeNode *treeptr;
typedef struct TreeNode tree_node;
typedef struct TreeNode
{
	int key;
	treeptr left;
	treeptr right;
};

treeptr InsertNode(int key, treeptr node);
treeptr DeleteNode(int key, treeptr node);
treeptr FindNode(int key, treeptr node);
treeptr FindMax(treeptr node);
void PrintInorder(treeptr node);
void PrintPreorder(treeptr node);
void PrintPostorder(treeptr node);

treeptr InsertNode(int key, treeptr node)
{
	if ( FindNode(key, node) == NULL )
	{
		if ( node == NULL )
		{
			node = (treeptr)malloc(sizeof(tree_node));
			node->key = key;
			node->left = node->right = NULL;
		}
		else if ( key < node->key )
		{
			node->left = InsertNode(key, node->left);
		}
		else if ( key > node->key )
		{
			node->right = InsertNode(key, node->right);
		}
		return node;
	}
	fprintf(wfp, "%d already exists.\n", key);
	return node;
}

treeptr DeleteNode(int key, treeptr node)
{
	if ( FindNode(key, node) != NULL )
	{
		treeptr tmp;
		if ( key < node->key )
		{
			node->left = DeleteNode(key, node->left);
		}
		else if ( key > node->key )
		{
			node->right = DeleteNode(key, node->right);
		}
		else if ( node->left && node->right )
		{
			tmp = FindMax(node->left);
			node->key = tmp->key;
			node->left = DeleteNode(node->key, node->left);
		}
		else
		{
			tmp = node;
			if ( node->left == NULL ) node = node->right; 
			else if ( node->right == NULL ) node = node->left;
			free(tmp);
		}
		return node;
	}
	else
	{
		fprintf(wfp, "Deletion failed. %d does not exist.\n", key);
		return node;
	}
}
treeptr FindNode(int key, treeptr node)
{
	if ( node == NULL ) return NULL;
	if ( key < node->key ) return FindNode(key, node->left);
	else if ( key > node->key ) return FindNode(key, node->right);
	else return node;
}

treeptr FindMax(treeptr node)
{
	if ( node == NULL ) return NULL;
	else
	{
		while ( node->right != NULL )
		{
			node = node->right;
		}
	}
	return node;
}

void PrintInorder(treeptr node)
{
	if ( node )
	{
		PrintInorder(node->left);
		fprintf(wfp, "%d ", node->key);
		PrintInorder(node->right);
	}
}

void PrintPreorder(treeptr node)
{
	if ( node )
	{
		fprintf(wfp, "%d ", node->key);
		PrintPreorder(node->left);
		PrintPreorder(node->right);
	}
}

void PrintPostorder(treeptr node)
{
	if ( node )
	{
		PrintPostorder(node->left);
		PrintPostorder(node->right);
		fprintf(wfp, "%d ", node->key);
	}
}

int main()
{
	rfp = fopen("input.txt", "r");
	wfp = fopen("output.txt", "w");

	treeptr t1 = NULL;

	char* kind;
	kind = (char*)malloc(sizeof(char) * 5);

	int num;

	while ( 1 )
	{
		fscanf(rfp, "%s ", kind);
		if ( feof(rfp) ) break;
		if ( !strcmp(kind, "i") )
		{
			fscanf(rfp, "%d", &num);
			t1 = InsertNode(num, t1);
		}
		else if ( !strcmp(kind, "d") )
		{
			fscanf(rfp, "%d", &num);
			t1 = DeleteNode(num, t1);
		}
		else if ( !strcmp(kind, "f") )
		{
			fscanf(rfp, "%d", &num);
			if ( FindNode(num, t1) )
				fprintf(wfp, "%d is in the tree.\n", num);
			else fprintf(wfp, "%d is not in the tree.\n", num);   
		}
		else if ( !strcmp(kind, "pi") )
		{
			fprintf(wfp, "pi - ");
			PrintInorder(t1);
			fprintf(wfp, "\n");
		}
		else if ( !strcmp(kind, "pr") )
		{
			fprintf(wfp, "pr - ");
			PrintPreorder(t1);
			fprintf(wfp, "\n");
		}
		else if ( !strcmp(kind, "po") )
		{
			fprintf(wfp, "po - ");
			PrintPostorder(t1);
			fprintf(wfp, "\n");
		}
	}
	free(kind);
	free(t1);
}