#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "pipex.h"

void	child_fork_first(int *pipes, char **envp, char **argv)
{
	int	*pipes_path;
	int	status;
	pid_t	pid;

	pipes_path = create_pipes(pipes_path, 0);
	pid = fork();
	free_pipes_error(pipes, pipes_path, pid < 0, "fork failed at child_fork_first");
	if (pid == 0)
		whereis(pipes_path, argv[2], envp);
	else
	{
		waitpid(pid, &status, 0);
		close(pipes_path[1]);
		if (child1(read_from_pipe_path(pipes_path[0]),
				ft_split(argv[2], ' '), pipes, argv[1]) < 0)
		{
			close(pipes_path[0]);
			free(pipes_path);
			exit(EXIT_FAILURE);
		}
	}
}

void	child_fork_second(int *pipes, char **envp, char **argv)
{
	int	*pipes_path;
	int	status;
	pid_t	pid;

	pipes_path = create_pipes(pipes_path, 0);
	pid = fork();
	free_pipes_error(pipes, pipes_path, pid < 0, "fork failed at child_fork_first");
	if (pid == 0)
		whereis(pipes_path, argv[ptr_arr_len(argv) - 2], envp);
	else
	{
		waitpid(pid, &status, 0);
		close(pipes_path[1]);
		if (child2(read_from_pipe_path(pipes_path[0]),
				ft_split(argv[ptr_arr_len(argv) - 2], ' '),
				pipes, argv[ptr_arr_len(argv) - 2]) < 0)
		{
			close(pipes_path[0]);
			free(pipes_path);
			exit(EXIT_FAILURE);
		}
	}
}
