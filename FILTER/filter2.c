#include <fcntl.h> //read
#include <unistd.h>
#include <errno.h> //perror
#include <stdlib.h> //malloc
#include <stdio.h> //printf

#ifndef BUFFER_SIZE
    #define BUFFER_SIZE 1024
#endif

int ft_strlen(char *str)
{
    int i = 0;

    while (str[i] != '\0')
        i++;
    return (i);
}

char *ft_substr(char *str, int start, int len)
{
    char *new_str;
    int j = 0;

    if (ft_strlen(str) <= start)
        len = 0;
    else if ((ft_strlen(str) - start) < len)
        len = ft_strlen(str) - start;
    new_str = malloc(sizeof(char) * (len + 1));
    if (!new_str)
        return (NULL);
    while (j < len)
    {
        new_str[j] = str[start + j];
        j++;
    }
    new_str[j] = '\0';
    return (new_str);
}

char *ft_strjoin(char *s1, char *s2)
{
    int i = 0;
    int j = 0;
    int len_1 = ft_strlen(s1);
    int len_2 = ft_strlen(s2);
    char *new_str;

    new_str = malloc(sizeof(char) * (len_1 + len_2 + 1));
    if (!new_str)
        return (NULL);
    while (s1[i])
    {
        new_str[j] = s1[i];
        j++;
        i++;
    }
    i = 0;
    while (s2[i])
    {
        new_str[j] = s2[i];
        j++;
        i++;
    }
    new_str[j] = '\0';
    return (new_str);
}

int if_filter(char *str, char *filter, int i)
{
    int j = 0;

    while (filter[j])
    {
        if (str[i] == filter[j])
        {
            i++;
            j++;
        }
        else
            return (0);
    }
    return (1);
}

void print_buffer(char *str, char *filter)
{
    int i = 0;
    int j = 0;

    while (str[i])
    {
        if (str[i] == filter[0] && if_filter(str, filter, i))
        {
            j = 0;
            while (filter[j])
            {
                printf("*");
                j++;
            }
            i = i + j;
        }
        else
        {
            printf("%c", str[i]);
            i++;
        }
    }
}

int func_read_print(int fd, char *filter)
{
    ssize_t bytes_read = 0;
    char    *buffer;
    char    *temp_buffer_print = NULL;
    char    *buffer_print = NULL;
    char    *rest;
    int     len_filter = ft_strlen(filter);

    buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if(!buffer)
    {
        perror("Error malloc");
        return (-1);
    }
    rest = malloc(1);
    if(!rest)
    {
        perror("Error malloc");
        return (-1);
    }
    rest[0] = '\0';
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        buffer[bytes_read] = '\0';
        if ((temp_buffer_print = ft_substr(buffer, 0, bytes_read - (len_filter + 1))) == NULL)
        {
            free(buffer);
            free(rest);
            perror("Error malloc");
            return (-1);
        }
        if ((buffer_print = ft_strjoin(rest, temp_buffer_print)) == NULL)
        {
            free(buffer);
            free(rest);
            free(temp_buffer_print);
            perror("Error malloc");
            return (-1);
        }
        print_buffer(buffer_print, filter);
        free(temp_buffer_print);
        free(buffer_print);
        free(rest);
        if ((rest = ft_substr(buffer, bytes_read - (len_filter + 1), (len_filter + 1))) == NULL)
        {
            free(buffer);
            perror("Error malloc");
            return (-1);
        }
    }
    if (bytes_read == 0 && rest)
        print_buffer(rest, filter);
    else if (bytes_read == -1)
    {
        free(rest);
        perror("Error read");
        return (-1);
    }
    free(buffer);
    free(rest);
    return (0);
}

int main (int argc, char **argv)
{
    if (argc != 2 || argv[1][0] == '\0')
        return (1);
    if (func_read_print(STDIN_FILENO, argv[1]) == -1)
        return (1);
    return (0);
}
