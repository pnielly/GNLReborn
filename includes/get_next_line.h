#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct s_stock
{
    int fd;
    char *content;
    struct s_stock *next;
} t_stock;

int get_next_line(int fd, char **line);

// utils
char *ft_strjoin(char *s1, char *s2);
char *ft_strchr(char *str, char c);
char *ft_strstr(char *str, char *tofind);
int ft_putstr(char *s);

void ft_clean_stock(t_stock **stock, int fd);
char *ft_itoa(int n);

#endif