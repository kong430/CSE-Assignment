#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <signal.h>

#define READ_FLAG '0'
#define WRITE_FLAG '1'

int ret;
char* shmaddr;

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
		printf("Program exit\n");
		exit(0);
	}
}

int main(void)
{
	signal(SIGINT, handler);

	int shmid;
	int i;
	char *msg;
	char tmp[50];
	
	shmid = shmget((key_t)1234, 1024, IPC_CREAT|0666);
	if (shmid<0)
	{
		perror("shmget");
		return 0;
	}
		
	shmaddr = shmat(shmid, NULL, 0);
	
	if (shmaddr == (char *)-1)
	{
		perror("attch failed\n");
		return 0;
	}
	shmaddr[0] = WRITE_FLAG;
	msg = shmaddr+1;
			
	while (1)
	{
		if (shmaddr[0]==WRITE_FLAG)
		{	
			fgets(tmp, sizeof(tmp), stdin);
			strcpy(msg, (char *)tmp);
			shmaddr[0] = READ_FLAG;
		}	
	}
	
	return 0;
}
