//First Readers-Writers problem
#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

#define COUNTING_NUMBER 10000

void writer(void* num);
void reader();

sem_t S;
sem_t wrt;

int count[5];
int readcount = 0;
int cur_writer, cur_count;
int threadId[5] = {0,1,2,3,4};

int main(void)
{
	//initialize semaphore
	sem_init(&S, 0,1);
	sem_init(&wrt, 0,1);

	pthread_t consumer[3];
	pthread_t producer[6];

	//create two Readers
	for (int i=0;i<2;i++)
	{
		pthread_create(&consumer[i], NULL, (void*)&reader, NULL);
	}
	//create five Writers
	for (int i=0;i<5;i++)
	{
		pthread_create(&producer[i], NULL, (void*)&writer, (void*)&threadId[i]);
	}
	//wait for all threads to finish
	for (int i=0;i<2;i++)
	{
		pthread_join(consumer[i], NULL);
	}
	for (int i=0;i<5;i++)
	{
		pthread_join(producer[i], NULL);
	}

	//destroy semaphore
	sem_destroy(&S);
	sem_destroy(&wrt);
}

//the writer accesses the critical section, writes the writer_id to the cur_writer, and writes the total number of times the writer has accessed the critical section in the cur_count
void writer(void *num)
{
	int writer_id = *(int*)num;
	for(int i=0;i<COUNTING_NUMBER;i++)
	{
		usleep(100000);
		sem_wait(&wrt);
		cur_writer = writer_id;
		count[writer_id]++;
		cur_count = count[writer_id];
		sem_post(&wrt);
	}
}

//the reader reads cur_writer and cur_count and print them
void reader()
{
	for(int i =0 ;i<COUNTING_NUMBER;i++)
	{
		usleep(30000);
		sem_wait(&S);

		//increase the number of readers in the critical section
		readcount++;
		if(readcount == 1)
		{
			//Wait until there is no writer
			sem_wait(&wrt);
		}
		sem_post(&S);
		
		//perform a read operation
		printf("The most recent writer id: [%d], count: [%d]\n",cur_writer, cur_count);
		sem_wait(&S);
		
		//decrease the number of readers
		readcount--;

		//if there is no readers in the critical section
		if(readcount==0)
		{
			sem_post(&wrt);
		}
		sem_post(&S);
	}
}
