#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int if_filter(char *str, char *filter, int i)
{
    int j = 0;

    while (filter[j] != '\0')
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

void func_print_result(char *str, char *filter)
{
    char *result;
    int  i = 0;
    int  x = 0;
    int  r = 0;
    int  len_s = 0;
    int  len_f = 0;

    while (str[len_s] != '\0')
        len_s++;
    while (filter[len_f] != '\0')
        len_f++;
    result = malloc(sizeof(char) * (len_s + 1));
    while (str[i])
    {
        if (str[i] == filter[0] && if_filter(str, filter, i))
        {
            x = 0;
            while (x < len_f)
            {
                result[r] = '*';
                x++;
                r++;
            }
            i = i + len_f;
        }
        else
        {
            result[r] = str[i];
            r++;
            i++;
        }
    }
    result[r] = '\0';
    printf("%s", result);
    free(result);
}

char *str_join(char *dest, char *str)
{
    int  i = 0;
    int  len1 = 0;
    int  len2 = 0;
    char *new_str;

    while (dest[len1] != '\0')
        len1++;
    while (str[len2] != '\0')
        len2++;
    new_str = malloc(sizeof(char) * (len1 + len2 + 1));
    while (dest[i] != '\0')
    {
        new_str[i] = dest[i];
        i++;
    }
    i = 0;
    while (str[i] != '\0')
    {
        new_str[len1 + i] = str[i];
        i++;
    }
    new_str[len1 + i] = '\0';
    return (new_str);
}

char *ft_substr(char *string, int start, int len)
{
    char *str;
    int j = 0;

    str = malloc(sizeof(char) * (len + 1));
    while (j < len)
    {
        str[j] = string[start + j];
        j++;
    }
    str[j] = '\0';
    return (str);
}

int func_read(int fd, char *filter)
{
    char     buffer[1024];
    ssize_t  bytes_read;
    char    *buffer_print;
    char    *temp_buffer;
    char    *temp;
    char    *rest;
    int      len_f = 0;

    temp_buffer = NULL;
    rest = malloc(1);
    rest[0] = '\0';
    while (filter[len_f] != '\0')
        len_f++;
    while ((bytes_read = read(fd, buffer, 1023)) > 0)
    {
        buffer[bytes_read] = '\0';

        if (bytes_read < len_f - 1)
        {
            temp = str_join(rest, buffer);
            free(rest);
            rest = temp;
        }
        else
        {
            temp_buffer = ft_substr(buffer, 0, bytes_read - (len_f - 1));
            buffer_print = str_join(rest, temp_buffer);
            func_print_result(buffer_print, filter);
    
            free(temp_buffer);
            free(buffer_print);
            free(rest);
            
            rest = ft_substr(buffer, bytes_read - (len_f - 1), (len_f - 1));
        }
    }
    if (bytes_read == 0 && rest != NULL)
        func_print_result(rest, filter);
    else if (bytes_read == -1)
    {
        free(rest);
        perror("Read error");
        return (-1);
    }
    free(rest);
    return (0);
}

int main (int argc, char **argv)
{
    int string;

    if (argc != 2 || argv[1][0] == '\0')
        return (1);
    string = func_read(STDIN_FILENO, argv[1]);
    if (string == -1)
        return (1);
    return (0);
}   