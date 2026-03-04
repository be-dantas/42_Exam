#include <unistd.h>
#include <stdio.h>
#include <ctype.h>

static char *str;

int add();
int multi();
int paren();

int print_error(char c)
{
	if (c == '\0')
		printf("Unexpected end of input\n");
	else
		printf("Unexpected token '%c'\n", c);
	return (-1);
}

int paren()
{
	int res;

	if (*str == '(')
	{
		str++;
		if (!isdigit((unsigned char)*str) && *str != '(')
			return (print_error(*str));
		res = add();
		if (res == -1)
			return (-1);
		if (*str == ')')
		{
			str++;
			return (res);
		}
		else
			return (print_error(*str));
	}
	if (isdigit((unsigned char)*str))
		return (*str++ - '0');
	else
		return (print_error(*str));
}

int multi()
{
	int res = paren();
	int temp;

	if (res == -1)
		return (-1);
	while (*str == '*')
	{
		str++;
		temp = paren();
		if (temp == -1)
			return (-1);
		res = res * temp;
	}
	return (res);
}

int add()
{
	int res = multi();
	int temp;

	if (res == -1)
		return (-1);
	while (*str == '+')
	{
		str++;
		temp = multi();
		if (temp == -1)
			return (-1);
		res = res + temp;
	}
	return (res);
}

int main(int argc, char **argv)
{
	int result;

	if (argc != 2)
		return (1);
	str = argv[1];
	result = add();
	if (result == -1 || *str != '\0')
	{
		if (result != -1)
			print_error(*str);
		return (1);
	}
	printf("%d\n", result);
	return (0);
}