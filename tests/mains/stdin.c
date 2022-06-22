#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "../../includes/get_next_line.h"

int ft_putstr_endl(char *s)
{
    int i = ft_putstr(s);
    write(1, "\n", 1);
    return i;
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
    int ret = 0;

    (void)av;
    if (ac != 1)
    {
        ft_putstr("Usage:\n./gnl");
        return -1;
    }

    while ((ret = get_next_line(0, &line)) > 0)
    {
        ft_putstr_endl(line);
        // printf("%d\n", ret);
        free(line);
        line = NULL;
    }
    ft_putstr(line);
    // printf("%d\n", ret);
    free(line);
    line = NULL;

    return (0);
}