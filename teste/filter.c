#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
    #define BUFFER_SIZE 200
#endif

int ft_strlen(char *str)
{
    int i = 0;

    while (str[i])
        i++;
    return (i);
}

char *ft_strdup(char *str)
{
    int i = 0;
    int len = ft_strlen(str);
    char *new_str;

    new_str = malloc(sizeof(char) * (len + 1));
    if (!new_str)
        return (NULL);
    while (str[i])
    {
        new_str[i] = str[i];
        i++;
    }
    new_str[i] = '\0';
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
        i++;
        j++;
    }
    i = 0;
    while (s2[i])
    {
        new_str[j] = s2[i];
        i++;
        j++;
    }
    new_str[j] = '\0';
    return (new_str);
}

int is_filter(char *str, char *filter, int i)
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
        if (str[i] == filter[0] && is_filter(str, filter, i))
        {
            j = 0;
            while (filter[j])
            {
                str[i] = '*';
                i++;
                j++;
            }
        }
        else
            i++;
    }
    printf("%s", str);
}

int read_print(int fd, char *filter)
{
    ssize_t bytes_read = 0;
    char *buffer;
    char *temp;
    char *buffer_print;

    buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buffer)
    {
        perror("Error");
        return (1);
    }
    buffer_print = ft_strdup("");
    if (!buffer_print)
    {
        free(buffer);
        perror("Error");
        return (1);
    }
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        buffer[bytes_read] = '\0';
        temp = ft_strjoin(buffer_print, buffer);
        if (!temp)
        {
            free(buffer);
            free(buffer_print);
            perror("Error");
            return (1);
        }
        free(buffer_print);
        buffer_print = ft_strdup(temp);
        if (!buffer_print)
        {
            free(buffer);
            free(temp);
            perror("Error");
            return (1);
        }
        free(temp);
    }
    if (bytes_read == -1)
    {
        free(buffer);
        free(buffer_print);
        perror("Error");
        return (1);
    }
    print_buffer(buffer_print, filter);
    free(buffer);
    free(buffer_print);
    return (0);
}

int main(int argc, char **argv)
{
    if (argc != 2 || argv[1][0] == '\0')
        return (1);
    if (read_print(STDIN_FILENO, argv[1]) == 1)
        return (1);
    return (0);
}