#include "../includes/get_next_line.h"

char *ft_strjoin(char *s1, char *s2)
{
    int i = 0, j = 0, k = -1;
    char *str;

    if (!s1 || !s2)
        return NULL;
    while (s1[i])
        i++;
    while (s2[j])
        j++;
    if (!(str = malloc(i + j + 1)))
        return 0;
    while (s1[++k])
        str[k] = s1[k];
    j = 0;
    while (s2[j])
        str[k++] = s2[j++];
    str[k] = 0;
    return str;
}

char *ft_strchr(char *str, char c)
{
    char *ptr = NULL;
    int i = -1;

    if (!str)
        return NULL;
    while (str[++i])
    {
        if (str[i] == c)
        {
            ptr = str + i;
            break;
        }
    }
    return ptr;
}

void ft_clean_stock(t_stock **stock, int fd)
{
    t_stock *tmp;
    t_stock *tmp2;

    tmp = *stock;
    while (tmp->next)
    {
        if (tmp->fd == fd)
        {
            free(tmp->content);
            tmp->content = NULL;
            tmp2 = *stock;
            if (tmp2 == tmp)
            {
                *stock = tmp->next;
                tmp = tmp->next;
                free(tmp2);
                tmp2 = NULL;
            }
            else
            {
                while (tmp2->next != tmp)
                    tmp2 = tmp2->next;
                tmp2->next = tmp->next;
                free(tmp);
                tmp = NULL;
            }
        }
    }
}

int ft_len(int n)
{
    int i;
    int m;

    i = 0;
    m = n;
    if (n == 0)
        return (1);
    while (n)
    {
        n = n / 10;
        i++;
    }
    if (m < 0)
        i++;
    return (i);
}

char *ft_build_str(int n, char *str, int len)
{
    long v;
    int k;

    if (n == 0)
    {
        str[0] = 48;
    }
    v = (long)n;
    if (v < 0)
    {
        str[0] = '-';
        v = -v;
    }
    str[len] = '\0';
    if (v != 0)
    {
        k = (1 - (n / v)) / 2;
        while (len > k)
        {
            str[--len] = v % 10 + 48;
            v = v / 10;
        }
    }
    return (str);
}

char *ft_itoa(int n)
{
    char *str;
    int len;

    len = ft_len(n);
    if (!(str = malloc(len + 1)))
        return (0);
    return (ft_build_str(n, str, len));
}