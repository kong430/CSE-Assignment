#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARGUMENT_NUMBER 20

//Variable to store results for all threads
long long result=0;

void *ThreadFunc(void *n)
{
	long long i;
	long long number = *((long long *)n);
	
	//Variable to store results for individual threads
	long long tResult = 0;
	printf("number=%lld\n", number);

	//Store values in different tResult for each thread
	for (i=0;i<25000000;i++)
	{
		tResult +=number;
	}

	//Store the sum of the results of all threads
	result +=tResult;
}	

int main(void)
{

	pthread_t threadID[ARGUMENT_NUMBER];
	long long argument[ARGUMENT_NUMBER];
	long long i;

	//Create ARGUMENT_NUMBER threads
	for (i=0;i<ARGUMENT_NUMBER;i++)
	{
		argument[i] = i;
		pthread_create(&(threadID[i]), NULL, ThreadFunc, (void *)&argument[i]);
	}
	printf("Main Thread is waiting for Child Thread!\n");
	
	//Wait for ARGUMENT_NUMBER threads to terminate
	for (i=0;i<ARGUMENT_NUMBER;i++)
	{
		pthread_join(threadID[i], NULL);
	}
	printf("result=%lld\n", result);
	return 0;
}
