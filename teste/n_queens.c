#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int is_digit(char *str)
{
    int i = 0;

    while (str[i])
    {
        if (str[i] >= '0' && str[i] <= '9')
            i++;
        else
            return (0);
    }
    return (1);
}

void print_matriz(int *matriz, int num)
{
    int i = 0;

    while (i < (num - 1))
    {
        printf("%d ", matriz[i]);
        i++;
    }
    printf("%d\n", matriz[i]);
}

int position_ok(int *matriz, int collum, int line)
{
    int i = 0;

    while (i < collum)
    {
        if (matriz[i] == line)
            return (0);
        i++;
    }
    i = 1;
    while (i <= collum)
    {
        if (matriz[collum - i] == line - i || matriz[collum - i] == line + i)
            return (0);
        i++;
    }
    return (1);
}

void loop_collum(int *matriz, int collum, int num)
{
    int line = 0;

    if (collum == num)
    {
        print_matriz(matriz, num);
        return ;
    }
    while (line < num)
    {
        matriz[collum] = line;
        if (position_ok(matriz, collum, line))
            loop_collum(matriz, collum + 1, num);
        line++;
    }
}

int *init_matriz(int num)
{
    int i = 0;
    int *matriz;

    matriz = malloc(sizeof(int) * num);
    if (!matriz)
        return (NULL);
    while (i < num)
    {
        matriz[i] = -1;
        i++;
    }
    return (matriz);
}

int main(int argc, char **argv)
{
    int *matriz;
    int num;

    if (argc != 2 || argv[1][0] == '\0' || !is_digit(argv[1]))
        return (0);
    num = atoi(argv[1]);
    if (num < 4)
        return (0);
    matriz = init_matriz(num);
    if (!matriz)
        return (1);
    loop_collum(matriz, 0, num);
    free(matriz);
    return (0);
}