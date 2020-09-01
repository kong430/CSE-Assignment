#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

#define READ_FLAG '0'
#define WRITE_FLAG '1'

int ret;
char *shmaddr;
int shmid;

void handler(int sig)
{
	if (sig==SIGINT)
	{
		ret = shmdt(shmaddr);
		if (ret==-1)
		{
			perror("detach failed\n");
			exit(0);
		}
		ret = shmctl(shmid, IPC_RMID, 0);
		if (ret ==-1)
		{
			perror("remove failed\n");
			exit(0);
		}
		printf("Program exit\n");
		exit(0);
	}
}

int main(void)
{
	signal(SIGINT, handler);
	char *msg;

	shmid = shmget((key_t)1234, 1024, IPC_CREAT|0666);
	if (shmid ==-1)
	{
		perror("shared memory access is failed\n");
		return 0;
	}

	shmaddr = (char *)shmat(shmid, NULL, 0);
	if (shmaddr == (char *)-1)
	{
		perror("attach failed\n");
		return 0;
	}
	msg = shmaddr+1;

	while(1)
	{	

		if (shmaddr[0]==READ_FLAG)
		{
			printf("data read form shared memory: %s", msg);
			shmaddr[0]=WRITE_FLAG;
		}
	}

	ret = shmdt(shmaddr);
	if (ret==-1)
	{
		perror("detach failed\n");
		return 0;
	}

	ret = shmctl(shmid, IPC_RMID, 0);
	if (ret==-1)
	{
		perror("remove failed\n");
		return 0;
	}
	return 0;
}
