#include <unistd.h> //execvp
#include <stdlib.h> // exit
#include <sys/wait.h>

int picoshell(char **cmds[])
{
	int i = 0;
	pid_t pid;
	int pipefd[2];
	int prev_fd = -1;
	int status;
	int exit_status = 0;
	int children = 0;

	while (cmds[i])
	{
		if (cmds[i + 1])
		{
			if (pipe(pipefd) == -1)
			{
				if (prev_fd != -1)
					close(prev_fd);
				return (1);
			}
		}
		pid = fork();
		if (pid == -1)
		{
			if (cmds[i + 1])
			{
				close(pipefd[0]);
				close(pipefd[1]);
			}
			if (prev_fd != -1)
				close(prev_fd);
			return (1);
		}
		else if (pid == 0)
		{
			if (prev_fd != -1)
			{
				if (dup2(prev_fd, STDIN_FILENO) == -1)
					exit(1);
				close(prev_fd);
			}
			if (cmds[i + 1])
			{
				close(pipefd[0]);
				if (dup2(pipefd[1], STDOUT_FILENO) == -1)
					exit(1);
				close(pipefd[1]);
			}
			execvp(cmds[i][0], cmds[i]);
			exit(1);
		}
		children++;
		if (prev_fd != -1)
			close(prev_fd);
		if (cmds[i + 1])
		{
			close(pipefd[1]);
			prev_fd = pipefd[0];
		}
		i++;
	}
    /*while (children > 0)
    {
        if (wait(&status) == -1)
            break;
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
            exit_status = 1;
        children--;
    }
    return (exit_status);*/
	while (wait(&status) != -1)
	{
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			exit_status = 1;
	}
	return (exit_status);
}

/*
int main ()
{
	//char *cmd1[] = {"ls", NULL};
	//char *cmd2[] = {"wc", "-l", NULL};
	char *cmd1[] = {"echo", "lalala", NULL};
	char *cmd2[] = {"sed", "s/a/o/g", NULL};
	char **final[] = {cmd1, cmd2, NULL};
	picoshell(final);
	return (0);
}
*/