#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int	fd;

	fd = open("file.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	char *tmp = get_next_line(fd);
	while (tmp)
	{
	printf("%s", tmp);
	free(tmp);
	tmp = get_next_line(fd);
	}
	//printf("%s", tmp);
	close(fd);
	return (0);
}
