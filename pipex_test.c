/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 19:03:43 by dghonyan          #+#    #+#             */
/*   Updated: 2022/04/24 16:51:17 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "pipex.h"

char	*read_from_pipe(int pipe)
{
	char	*s;
	char	c;
	int		a;
	int		i;

	i = 0;
	s = NULL;
	while (1)
	{
		a = read(pipe, &c, 1);
		free_error(NULL, s, a == -1, "read() failed at read_from_pipe()");
		if (a == 0)
			break ;
		s = ft_strjoin_for_read(s, c);
		free_error(NULL, NULL, !s, "malloc failed at read_from_pipe");
		i++;
	}
	return (s);
}

char	*read_from_pipe_path(int pipe)
{
	char	*s;
	char	c;
	int		a;
	int		i;

	i = 0;
	s = NULL;
	while (1)
	{
		a = read(pipe, &c, 1);
		free_error(NULL, s, a == -1, "read() failed at read_from_pipe()");
		if (a == 0 || c == '\n' || c == ':')
			break ;
		s = ft_strjoin_for_read(s, c);
		free_error(NULL, NULL, !s, "malloc failed at read_from_pipe");
		i++;
	}
	return (s);
}

int	child1(char *path, char **args, int *pipes, char *file)
{
	int	fd;

	free_error(pipes, path, !args, "malloc failed at ft_split | child1");
	if (close(pipes[0]) < 0)
		return (free_error_args(pipes, path, args, "close failed at child1"));
	fd = open(file, O_RDONLY | O_CLOEXEC);
	if (fd < 0)
		return (free_error_args(pipes, path, args, "open failed at child1"));
	if (dup2(pipes[1], STDOUT_FILENO) < 0)
		return (free_error_args(pipes, path, args, "dup2 failed at child1"));
	if (dup2(fd, STDIN_FILENO) < 0)
		return (free_error_args(pipes, path, args, "dup2 failed at child1"));
	if (close(pipes[1]) < 0)
		return (free_error_args(pipes, path, args,
				"close failed at child1 again"));
	execve(path, args, NULL);
	return (free_error_args(pipes, path, args, "Execve failed at child1"));
}

int	child2(char *path, char **args, int *pipes, char *file)
{
	int	fd;

	free_error(pipes, path, !args, "malloc failed at ft_split | child2");
	if (close(pipes[1]) < 0)
		return (free_error_args(pipes, path, args, "close failed at child2"));
	fd = open(file, O_WRONLY | O_CLOEXEC | O_TRUNC);
	if (fd < 0)
		return (free_error_args(pipes, path, args, "open failed at child2"));
	if (dup2(pipes[0], STDIN_FILENO) < 0)
		return (free_error_args(pipes, path, args, "dup2 failed at child2"));
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (free_error_args(pipes, path, args, "dup2 failed at child2"));
	if (close(pipes[0]) < 0)
		return (free_error_args(pipes, path, args,
				"close failed at child2 again"));
	execve(path, args, NULL);
	return (free_error_args(pipes, path, args, "Execve failed at child2"));
}

int	main(int argc, char **argv, char **envp)
{
	int		status;
	int		*pipes;
	int		*pipes_for_path;
	int		j;
	char	*path;
	pid_t	*pids;
	pid_t	pid;

	j = 0;
	check_args(argv[1], argv[argc - 1], argc);
	
	pids = (pid_t *)malloc(sizeof (*pids) * (argc - 3));

	pipes = create_pipes(pipes, 0);
	pids[0] = fork();
	free_error(pipes, NULL, pids[0] < 0, "Can't fork process");
	if (pids[0] == 0)
		child_fork_first(pipes, envp, argv);
	else if (pids[0] > 0)
	{
		waitpid(pids[0], &status, 0);
		printf("first process exited with status %d", WEXITSTATUS(status));
		printf("\n%d\n", argc - 5);
		for (j = 0; j < argc - 5; j++)
		{

			pids[j + 1] = fork();
			if (pids[j + 1] == 0)
			{
				pipes_for_path = create_pipes(pipes_for_path, 0);
				pid = fork();
				if (pid == 0)
					whereis(pipes_for_path, argv[j + 3], envp);
				waitpid(pid, &status, 0);
				close(pipes_for_path[1]);
				if (dup2(pipes[0], STDIN_FILENO) < 0)
					;//ERROR
				if (dup2(pipes[1], STDOUT_FILENO) < 0)
					;//ERROR
				printf("%s\n", path = read_from_pipe_path(pipes_for_path[0]));
				execve(path,
						ft_split(argv[j + 3], ' '), envp);
				//ERROR
				exit(EXIT_FAILURE);
			}
			else
				waitpid(pids[j + 1], &status, 0);
		}
		pids[argc - 2] = fork();
		if (pids[argc - 2] == 0)
		{
			pipes_for_path = create_pipes(pipes_for_path, 0);
			pid = fork();
			if (pid == 0)
				whereis(pipes_for_path, argv[argc - 2], envp);
			waitpid(pid, &status, 0);
			close(pipes_for_path[1]);
			if (child2(read_from_pipe_path(pipes_for_path[0]),
					ft_split(argv[argc - 2], ' '), pipes, argv[argc - 1]) < 0)
			{
				close(pipes_for_path[0]);
				free(pipes_for_path);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			close(pipes[0]);
			waitpid(pids[1], &status, 0);
			printf("back to parent\n");
		}
	}
}
