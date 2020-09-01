#include<stdio.h>
#include<stdlib.h>

FILE* rfp;
FILE* wfp;

int *num;
int *tmpNum;

void MSort(int *A, int *TmpArray, int Left, int Right);
void Merge(int *A, int *TmpArray, int Lpos, int Rpos, int RightEnd);

void MSort(int *A, int *TmpArray, int Left, int Right)
{
	int Center;
	if ( Left < Right )
	{
		Center = (Left + Right) / 2;
		MSort(A, TmpArray, Left, Center);
		MSort(A, TmpArray, Center + 1, Right);
		Merge(A, TmpArray, Left, Center + 1, Right);
	}
}

void Merge(int *A, int *TmpArray, int Lpos, int Rpos, int RightEnd)
{
	int i, LeftEnd, NumElements, TmpPos;
	LeftEnd = Rpos - 1;
	TmpPos = Lpos;
	NumElements = RightEnd - Lpos + 1;

	while ( Lpos <= LeftEnd && Rpos <= RightEnd )
	{
		if ( A[Lpos] <= A[Rpos] ) TmpArray[TmpPos++] = A[Lpos++];
		else TmpArray[TmpPos++] = A[Rpos++];
	}
	while ( Lpos <= LeftEnd ) TmpArray[TmpPos++] = A[Lpos++];
	while ( Rpos <= RightEnd ) TmpArray[TmpPos++] = A[Rpos++];

	for ( i = 0; i < NumElements; i++, RightEnd--)
	{
		A[RightEnd] = TmpArray[RightEnd];
	}
	for ( int j = RightEnd+1; j<RightEnd+1+i; j++)
	{
		fprintf(wfp, "%d ", A[j]);
	}
	fprintf(wfp, "\n");
}

int main()
{
	rfp = fopen("input.txt", "r");
	wfp = fopen("output.txt", "w");

	int input_num;
	fscanf(rfp, "%d", &input_num);
	num = (int*)malloc(sizeof(int) * input_num);
	tmpNum = (int*)malloc(sizeof(int) * input_num);

	for ( int i = 0; i < input_num; i++ )
	{
		fscanf(rfp, "%d\n", &num[i]);
	}

	fprintf(wfp, "input : \n");
	for ( int i = 0; i < input_num; i++ )
	{
		fprintf(wfp, "%d ", num[i]);
	}

	fprintf(wfp, "\n\nIterative : \n");
	MSort(num, tmpNum, 0, input_num-1);


	free(num);
	free(tmpNum);

	fclose(wfp);
	fclose(wfp);
}