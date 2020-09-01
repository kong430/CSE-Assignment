#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE* rfp;
FILE* wfp;

typedef struct threaded_tree* threaded_ptr;
typedef struct threaded_tree
{
	short int left_thread;
	threaded_ptr left_child;
	char data;
	threaded_ptr right_child;
	short int right_thread;
};

threaded_ptr insucc(threaded_ptr tree)
{
	threaded_ptr tmp;
	tmp = tree;
	tmp = tree->right_child;
	if ( tree->right_thread != 1 )
	{
		while ( tmp->left_thread != 1 )
		{
			tmp = tmp->left_child;
		}
	}
	return tmp;
}

void thread_inorder(threaded_ptr ptr)
{
	threaded_ptr tmp;
	tmp = ptr;

	for ( int i = 0; i < 9; i++ )
	{
		tmp = insucc(tmp);
		if ( tmp == ptr ) break;
		fprintf(wfp, "%c ", tmp->data);
	}
	fprintf(wfp, "\n");
}

int main()
{
	int num;
	char node_name[10];
	rfp = fopen("input.txt", "r");
	wfp = fopen("output.txt", "w");

	fscanf(rfp, "%d\n", &num);

	threaded_ptr root, n1, n2, n3, n4, n5, n6, n7, n8, n9;
	root = (threaded_ptr)malloc(sizeof(struct threaded_tree));
	n1 = (threaded_ptr)malloc(sizeof(struct threaded_tree));
	n2 = (threaded_ptr)malloc(sizeof(struct threaded_tree));
	n3 = (threaded_ptr)malloc(sizeof(struct threaded_tree));
	n4 = (threaded_ptr)malloc(sizeof(struct threaded_tree));
	n5 = (threaded_ptr)malloc(sizeof(struct threaded_tree));
	n6 = (threaded_ptr)malloc(sizeof(struct threaded_tree));
	n7 = (threaded_ptr)malloc(sizeof(struct threaded_tree));
	n8 = (threaded_ptr)malloc(sizeof(struct threaded_tree));
	n9 = (threaded_ptr)malloc(sizeof(struct threaded_tree));

	for ( int i = 0; i <num; i++ )
	{
		fscanf(rfp, "%c ", &node_name[i]);
	}

	root->data = ' ', root->left_child = n1, root->left_thread = 0, root->right_child = root, root->right_thread = 0;
	n1->data = node_name[0], n1->left_child = n2, n1->left_thread = 0, n1->right_child = n3, n1->right_thread = 0;
	n2->data = node_name[1], n2->left_child = n4, n2->left_thread = 0, n2->right_child = n5, n2->right_thread = 0;
	n3->data = node_name[2], n3->left_child = n6, n3->left_thread = 0, n3->right_child = n7, n3->right_thread = 0;
	n4->data = node_name[3], n4->left_child = n8, n4->left_thread = 0, n4->right_child = n9, n4->right_thread = 0;
	n5->data = node_name[4], n5->left_child = n2, n5->left_thread = 1, n5->right_child = n1, n5->right_thread = 1;
	n6->data = node_name[5], n6->left_child = n1, n6->left_thread = 1, n6->right_child = n3, n6->right_thread = 1;
	n7->data = node_name[6], n7->left_child = n3, n7->left_thread = 1, n7->right_child = root, n7->right_thread = 1;
	n8->data = node_name[7], n8->left_child = root, n8->left_thread = 1, n8->right_child = n4, n8->right_thread = 1;
	n9->data = node_name[8], n9->left_child = n4, n9->left_thread = 1, n9->right_child = n2, n9->right_thread = 1;

	thread_inorder(root);

	fclose(rfp);
	fclose(wfp);
}