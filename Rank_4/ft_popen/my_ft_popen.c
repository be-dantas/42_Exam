#include <unistd.h> // execvp
#include <stdlib.h> //exit
#include <sys/wait.h>

int ft_popen(const char *file, char *const argv[], char type)
{
	pid_t pid;
	int pipefd[2];

	if (!file || !argv || (type != 'r' && type != 'w'))
		return (-1);

	if (pipe(pipefd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (-1);
	}
	else if (pid == 0)
	{
		if (type == 'r')
		{
			close(pipefd[0]);
			if (dup2(pipefd[1], 1) == -1)
				exit(1);
			close(pipefd[1]);
		}
		else if (type == 'w')
		{
			close(pipefd[1]);
			if (dup2(pipefd[0], 0) == -1)
				exit(1);
			close(pipefd[0]);
		}
		execvp(file, argv);
		exit(1);
	}
	if (type == 'r')
	{
		close(pipefd[1]);
		return (pipefd[0]);
	}
	else if (type == 'w')
	{
		close(pipefd[0]);
		return (pipefd[1]);
	}
}

int main()
{
	char *argv[] = {"cat", NULL};
	int fd = ft_popen(argv[0], argv, 'w');
	if (fd == -1)
		return 1;
	write(fd, "Hello from parent!\n", 19);
	close(fd);
	return 0;
}