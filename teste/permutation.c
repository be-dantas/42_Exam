#include <unistd.h>

void sort_str(char *str, int i)
{
    int j = i + 1;
    char temp;

    while (str[i])
    {
        j = i + 1;
        while (str[j])
        {
            if (str[i] > str[j])
            {
                temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
            j++;
        }
        i++;
    }
}

int ft_strlen(char *str)
{
    int i = 0;

    while (str[i])
        i++;
    return (i);
}

int successor(char *str, int pivo)
{
    int i = ft_strlen(str) - 1;

    while (i > pivo)
    {
        if (str[i] > str[pivo])
            return (i);
        i--;
    }
    return (-1);
}

void if_one_two(char *str)
{
    char temp;

    if (ft_strlen(str) == 1)
    {
        write(1, str, 1);
        write(1, "\n", 1);
    }
    else if (ft_strlen(str) == 2)
    {
        write(1, str, 2);
        write(1, "\n", 1);
        temp = str[0];
        str[0] = str[1];
        str[1] = temp;
        write(1, str, 2);
        write(1, "\n", 1);
    }
}

void permu_print(char *str)
{
    int i = ft_strlen(str) - 2;
    int pivo = 0;
    int suc = 0;
    char temp;

    if (ft_strlen(str) == 1 || ft_strlen(str) == 2)
    {
        if_one_two(str);
        return ;
    }
    write(1, str, ft_strlen(str));
    write(1, "\n", 1);
    while (i >= 0)
    {
        if (str[i + 1] > str[i])
        {
            pivo = i;
            suc = successor(str, pivo);
            temp = str[pivo];
            str[pivo] = str[suc];
            str[suc] = temp;
            sort_str(str, pivo + 1);
            write(1, str, ft_strlen(str));
            write(1, "\n", 1);
            i = ft_strlen(str) - 2;
        }
        else
            i--;
    }
}

int main(int argc, char **argv)
{
    if (argc != 2 || argv[1][0] == '\0')
        return (0);
    sort_str(argv[1], 0);
    permu_print(argv[1]);
    return (0);
}