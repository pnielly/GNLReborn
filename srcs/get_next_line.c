#include "../includes/get_next_line.h"

t_stock *ft_newlst(int fd)
{
    t_stock *new;

    if (!(new = malloc(sizeof(t_stock))))
        return NULL;
    new->fd = fd;
    new->content = "";
    new->next = NULL;
    return new;
}

t_stock *get_fd_stock(t_stock **stock, int fd)
{
    t_stock *tmp;

    if (!*stock)
    {
        if (!(*stock = ft_newlst(fd)))
            return (NULL);
    }
    tmp = *stock;
    // printf("tmp->fd = %d but fd is %d\n", tmp->fd, fd);
    while (tmp->next)
    {
        // ft_putstr("YOOOOOOOOo");
        // printf("fd = %d et content = %s\n", tmp->fd, tmp->content);
        if (tmp->fd == fd)
            break;
        tmp = tmp->next;
    }
    if (tmp->fd != fd)
    {
        tmp->next = ft_newlst(fd);
        tmp = tmp->next;
    }
    return tmp;
}

char *dispatch_lines(t_stock **cur)
{
    char *ret;
    char *tmp;
    int i = 0, j = -1, len = 0;

    // get new value of line
    if (!(*cur)->content)
        return "";
    while ((*cur)->content[i] && (*cur)->content[i] != '\n')
        i++;
    if (!(ret = malloc(i + 1)))
        return NULL;
    while (++j < i)
        ret[j] = (*cur)->content[j];
    ret[i] = 0;

    // update cur->content
    while ((*cur)->content[len])
        len++;
    if (!(tmp = malloc(len - i + 1)))
        return NULL;
    j = -1;
    while (++j < len - i + 1)
        tmp[j] = (*cur)->content[j + i + 1];
    free((*cur)->content);
    (*cur)->content = tmp;

    return ret;
}

int get_next_line(int fd, char **line)
{
    static t_stock *stock = NULL;
    char *buf;
    t_stock *cur; // current
    int ret;
    char *str;

    if (!line || fd < 0 || BUFFER_SIZE <= 0)
        return -1;
    if (!(buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
        return -1;
    ret = 1;
    if (!(cur = get_fd_stock(&stock, fd)))
        return -1;
    // printf("cur->fd = %d\n", cur->fd);
    while (ret && !ft_strchr(cur->content, '\n'))
    {
        if ((ret = read(fd, buf, BUFFER_SIZE)) < 0)
            return -1;
        buf[ret] = 0;
        str = ft_strjoin(cur->content, buf);
        if (cur->content[0])
            free(cur->content);
        cur->content = str;
    }
    free(buf);
    buf = NULL;
    if (!(*line = dispatch_lines(&cur)))
        return -1;
    // if (!ret)
    //     ft_clean_stock(&stock, fd);
    return ret ? 1 : 0;
}