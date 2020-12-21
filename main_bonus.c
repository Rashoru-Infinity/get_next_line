#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "get_next_line_bonus.h"
#include <stdlib.h>

int main(void)
{
	int fd2 = open("get_next_line.c", O_RDONLY);
	int fd1 = open("get_next_line_bonus.c", O_RDONLY);
	char *line = NULL;
	int status;
	for (int i = 0;i < 10;++i)
	{
		if (get_next_line(fd1, &line) >= 0)
			printf("%s\n", line);
		free(line);
		line = NULL;
		if (get_next_line(fd2, &line) >= 0)
			printf("%s\n", line);
		free(line);
		line = NULL;
	}
	while ((status = get_next_line(fd1, &line)) >= 0)
	{
		printf("%s\n", line);
		free(line);
		line = NULL;
		if (status == 0)
			break;
	}
	while ((status = get_next_line(fd2, &line)) >= 0)
	{
		printf("%s\n", line);
		free(line);
		line = NULL;
		if (status == 0)
			break;
	}
	close(fd1);
	close(fd2);
}
