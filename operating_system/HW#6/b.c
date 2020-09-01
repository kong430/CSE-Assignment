//Dining-Philosophers problem using semaphore (LR solution)
#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

//Six chopsticks and philosophers
sem_t stick[7];
int philoId[6] = {0, 1, 2, 3, 4, 5};

void dining(void* num);

int main(void)
{
	pthread_t philo[7];

	//initialize the 6 semaphore and create 7 thread
	for (int i=0;i<6;i++)
	{
		sem_init(&stick[i], 0, 1);
		pthread_create(&philo[i], NULL, (void*)&dining, (void*)&philoId[i]);
	}

	//wait for all threads to finish	
	for (int i=0;i<6;i++)
	{
		pthread_join(philo[i], NULL);
	}

	//destroy all semaphores
	for (int i=0;i<6;i++)
	{
		sem_destroy(&stick[i]);
	}
}

void dining(void *num)
{
	//philosopher's id
	int id = *(int*)num;

	//eat 5 times per philosopher
	for (int i=0;i<5;i++)
	{
		//if philosopher's id is even number, then obtain right chopstick first
		if (id%2==0)
		{
			sem_wait(&stick[id]);
			printf("철학자[%d]가 오른쪽 젓가락을 집었습니다.\n", id);
			sem_wait(&stick[(id+1)%6]);
			printf("철학자[%d]가 왼쪽 젓가락을 집었습니다.\n", id);
		}
		//if philosopher's id is odd number, then obtain left chopstic first
		else
		{
			sem_wait(&stick[(id+1)%6]);
			printf("철학자[%d]가 왼쪽 젓가락을 집었습니다.\n", id);
			sem_wait(&stick[id]);
			printf("철학자[%d]가 오른쪽  젓가락을 집었습니다.\n", id);
		}

		printf("\t\t철학자[%d]가 식사중입니다...\n", id);
		sleep(1);
		printf("\t\t철학자[%d]가 식사를 마쳤습니다\n", id);
		
		//put down the chopsticks
		sem_post(&stick[id]);
		sem_post(&stick[(id+1)%6]);
	}
	pthread_exit(0);
}
