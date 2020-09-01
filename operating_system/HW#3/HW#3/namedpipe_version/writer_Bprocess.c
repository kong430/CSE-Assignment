#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

#define MSG_SIZE 80
#define PIPENAME "./named_pipe_file"

void handler(int sig)
{
	if (sig==SIGINT)
	{
		printf("Program Exit\n");
		exit(0);
	}
}

int main(void)
{	
	signal(SIGINT, handler);

	char msg[MSG_SIZE];
	int fd;
	int ret, i;

	fd = open(PIPENAME, O_WRONLY);
	if (fd<0)
	{
		printf("Open failed\n");
		return 0;
	}
	
	printf("Hello, this is A process. I'll give the data to B.\n");
	
	while(1)
	{
		fgets(msg, sizeof(msg), stdin);	
		ret = write(fd, msg, sizeof(msg));
		if (ret<0)
		{
			printf("Write failed\n");
			return 0;
		}
	}
	return 0;
}
