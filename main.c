#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "get_next_line.h"
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char *file_name;
	char eof = 0x1a;
	int fd;
    char *line;
    int status;

	(void)argc;
	(void)argv;

    file_name = "./test.txt";
   	fd = open(file_name, O_CREAT | O_WRONLY | O_RDONLY | O_TRUNC);
	write(fd, "nullbyte\0nullbyte", 17);
	write(fd , &eof, 1);
    // int fd = 0;
	//fd = 0;
    // int line_num = 1;
    while ((status = get_next_line(fd, &line)) >= 0)
    {
        // printf("\n");
        //printf("status:   %d\n", status);
        // printf("read txt: %s\n", line);
        // printf("\n");
        // printf("%d:\t%s\n", line_num, line);
        //if (!line)
           // printf("line is null\n");
        //printf("%s\n", line);
        // line_num++;
		write(1, line, 17);
        free(line);
		if (status == 0)
			break;
    }
    if (status == -1)
        printf("status is -1 !!\n");
    // printf("\n");
    // printf("read txt: %s\n", line);
    // printf("\n");
    // printf("%d:\t%s\n", line_num, line);
    close(fd);
}
