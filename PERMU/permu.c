#include <stdlib.h>
#include <unistd.h>

int ft_strlen(char *str)
{
    int i = 0;

    while (str[i])
        i++;
    return (i);
}

void sort_str(char *sort , int i)
{
    int j = 0;;
    char temp;

    while (sort[i])
    {
        j = i + 1;
        while (sort[j])
        {
            if (sort[i] > sort[j])
            {
                temp = sort[i];
                sort[i] = sort[j];
                sort[j] = temp;
            }
            j++;
        }
        i++;
    }
}

int successor(int pivo, char *permu)
{
    int i = ft_strlen(permu) - 1;

    while (i > pivo)
    {
        if (permu[i] > permu[pivo])
            return (i);
        i--;
    }
    return (-1);
}

void permu_print(char *permu)
{
    int     i = ft_strlen(permu) - 2;
    int     pivo;
    int     successor_pivo;
    char    temp;

    write(1, permu, ft_strlen(permu));
    write(1, "\n", 1);
    while (i >= 0)
    {
        if (permu[i] < permu[i + 1])
        {
            pivo = i;
            successor_pivo = successor(pivo, permu);
            temp = permu[pivo];
            permu[pivo] = permu[successor_pivo];
            permu[successor_pivo] = temp;
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
