#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int *init_matriz(int n)
{
	int i = 0;
	int *matriz;

	matriz = malloc(sizeof(int) * n);
	if (!matriz)
		return (NULL);
	while (i < n)
	{
		matriz[i] = -1;
		i++;
	}
	return (matriz);
}

void print_matriz(int *matriz, int n)
{
	int i = 0;

	while (i < (n - 1))
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
}

void loop_collum(int *matriz, int n, int collum)
{
	int line = 0;

	if (collum == n)
	{
		print_matriz(matriz, n);
		return ;
	}
	while (line < n)
	{
		matriz[collum] = line;
		if (position_ok(matriz, collum, line))
			loop_collum(matriz, n, collum + 1);
		line++;
	}
}

int main(int argc, char **argv)
{
	int *matriz;
	int n = atoi(argv[1]);
	
	if (argc != 2 || argv[1][0] == '\0' || n < 4)
		return (0);
	matriz = init_matriz(n);
	if (!matriz)
		return (0);
	loop_collum(matriz, n, 0);
	free(matriz);
	return (0);
}
