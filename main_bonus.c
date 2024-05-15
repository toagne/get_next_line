#include "get_next_line.h"
#include <stdio.h>

int main(void)
{
    char *str;
    int fd1;
	int	fd2;
	int fd3;
    int n;

	n = 4;
    fd1 = open("file1", O_RDONLY);
	fd2 = open("file2", O_RDONLY);
	fd3 = open("file3", O_RDONLY);

	while (n--)
	{
		str = get_next_line(fd1);
		printf("%s", str);
		free(str);
		str = get_next_line(fd2);
		printf("%s", str);
		free(str);
		str = get_next_line(fd3);
		printf("%s", str);
		free(str);
	}
    close(fd1);
	close(fd2);
	close(fd3);
}

