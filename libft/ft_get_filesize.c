//
// Created by Dimon on 24.06.2018.
//

#include "libft.h"

size_t	ft_get_filesize(char *file_name)
{
	int		fd;
	size_t	size;
	int		res;
	char	buf[BUFF_SIZE];

	if ((fd = open(file_name, O_RDONLY)) < 0)
		return (0);
	if (read(fd, NULL, 0) < 0)
		return (0);
	size = 0;
	while ((res = read(fd, buf, BUFF_SIZE)) > 0)
		size += res;
	close(fd);
	return (size);
}
