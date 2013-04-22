#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char * argv[])
{
	int fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		printf("Error: errno=%i\n", errno);
		return -1;
	}
	else
	{
		printf("Success!\n");
		close(fd);
		return 0;
	}
}
