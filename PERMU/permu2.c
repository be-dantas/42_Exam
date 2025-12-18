#include <unistd.h>

void sort_str(char *str, int i)
{
    int     j;
    char    temp;

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

int sucessor(char *permu, int pivo)
{
    int i = ft_strlen(permu) - 1;

    while (permu[i])
    {
        if (permu[i] > permu[pivo])
            return (i);
        i--;
    }
    return (-1);
}

void permu_print(char *permu)
{
    int i = ft_strlen(permu) - 2;
    int pivo = 0;
    int suc = 0;
    char temp;

    write(1, permu, ft_strlen(permu));
    write(1, "\n", 1);
    while (i >= 0)
    {
        if (permu[i] < permu[i + 1])
        {
            pivo = i;
            suc = sucessor(permu, pivo);
            temp = permu[pivo];
            permu[pivo] = permu[suc];
            permu[suc] = temp;
            sort_str(permu, pivo + 1);
            write(1, permu, ft_strlen(permu));
            write(1, "\n", 1);
            i = ft_strlen(permu) - 2;
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