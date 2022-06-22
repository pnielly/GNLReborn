#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "../../includes/get_next_line.h"

int ft_putstr_file(char *s, int fd)
{
	int i = 0;
	while (s[i])
		i++;
	write(fd, s, i);
	return i;
}

int ft_putstr_file_endl(char *s, int fd)
{
	int i = ft_putstr_file(s, fd);
	write(fd, "\n", 1);
	return i;
}

int ft_putstr_endl(char *s)
{
	return ft_putstr_file_endl(s, 1);
}

int ft_putstr(char *s)
{
	int i = -1;

	if (!s)
		return -1;
	while (s[++i])
	{
		write(1, &s[i], 1);
	}
	return i;
}

int ft_atoi(char *s)
{
	int ret = 0, i = 0, sign = 1;
	char *num = "0123456789";

	if (!s)
		return 0;
	while (s[i] && !ft_strchr(num, s[i]) && !(ft_strchr("+-", s[i]) && s[i + 1] && ft_strchr(num, s[i + 1])))
		i++;
	if (!s[i])
		return 0;
	if (s[i] == '-')
		sign = -1;
	if (ft_strchr("+-", s[i]))
		i++;
	while (s[i] && ft_strchr(num, s[i]))
	{
		ret = ret * 10 + s[i] - 48;
		i++;
	}
	return ret * sign;
}

int main(int ac, char **av)
{
	char *line = NULL;
	int ret[3], i = 0;
	ret[0] = 1;
	ret[1] = 1;
	ret[2] = 1;

	if (ac != 4)
	{
		ft_putstr("Usage:\n./gnl [path/to/file1] [path/to/file2] [path/to/file3]");
		return -1;
	}
	int fds[3];
	fds[0] = open(av[1], O_RDONLY);
	fds[1] = open(av[2], O_RDONLY);
	fds[2] = open(av[3], O_RDONLY);

	int fd_out[3];
	fd_out[0] = open("./tests/res/multi_fd1", O_WRONLY | O_CREAT, 0644);
	fd_out[1] = open("./tests/res/multi_fd2", O_WRONLY | O_CREAT, 0644);
	fd_out[2] = open("./tests/res/multi_fd3", O_WRONLY | O_CREAT, 0644);

	while (ret[0] > 0 || ret[1] > 0 || ret[2] > 0)
	{
		if (ret[i % 3] > 0)
		{
			ret[i % 3] = get_next_line(fds[i % 3], &line);
			// ft_putstr(ft_itoa(i % 3));
			if (i > 2)
				ft_putstr_file_endl("", fd_out[i % 3]);
			ft_putstr_file(line, fd_out[i % 3]);
			// ft_putstr_file(ft_itoa(ret[i % 3]), fd_out[i % 3]);
			free(line);
			line = NULL;
		}
		i++;
	}

	return (0);
}