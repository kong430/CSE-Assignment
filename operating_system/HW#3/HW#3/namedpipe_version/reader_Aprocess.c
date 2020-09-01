#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

#define PIPENAME "./named_pipe_file"

void handler(int sig)
{
	if (sig==SIGINT)
	{
		printf("Program exit\n");
		exit(0);
	}
}

int main()
{	
	signal(SIGINT, handler);

	int ret;
	char msg[512];
	int fd;
	pid_t pid;

	ret = access(PIPENAME, F_OK);
	if (ret==0)
	{
		unlink(PIPENAME);
	}
	ret = mkfifo(PIPENAME, 0666);
	if (ret<0)
	{
		printf("Creation of named pipe failed\n");
		return 0;
	}

	fd = open(PIPENAME, O_RDWR);
	if (fd<0)
	{
		printf("Opening of named pipe failed\n");
		return 0;
	}
	
	printf("Hello, this is B process. give me the data.\n");
	
	while(1)
	{
		ret = read(fd, msg, sizeof(msg));
		if (ret<0)
		{
			printf("Read failed\n");
			return 0;
		}
		printf("%s", msg);
	}
	return 0;
}
