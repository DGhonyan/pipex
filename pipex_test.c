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
		return free_error_args(pipes, path, args, "close failed at child1");
	fd = open(file, O_RDONLY | O_CLOEXEC);
	if (fd < 0)
		return free_error_args(pipes, path, args, "open failed at child1");
	if (dup2(pipes[1], STDOUT_FILENO) < 0)
		return free_error_args(pipes, path, args, "dup2 failed at child1");
	if (dup2(fd, STDIN_FILENO) < 0)
		return free_error_args(pipes, path, args, "dup2 failed at child1");
	execve(path, args, NULL);
	return free_error_args(pipes, path, args, "Execve failed at child1");
}

int	child2(char *path, char **args, int *pipes, char *file)
{
	int	fd;

	free_error(pipes, path, !args, "malloc failed at ft_split | child2");
	if (close(pipes[1]) < 0)
		return free_error_args(pipes, path, args, "close failed at child2");
	fd = open(file, O_WRONLY | O_CLOEXEC | O_TRUNC);
	if (fd < 0)
		return free_error_args(pipes, path, args, "open failed at child2");
	if (dup2(pipes[0], STDIN_FILENO) < 0)
		return free_error_args(pipes, path, args, "dup2 failed at child2");
	if (dup2(fd, STDOUT_FILENO) < 0)
		return free_error_args(pipes, path, args, "dup2 failed at child2");
	execve(path, args, NULL);
	return free_error_args(pipes, path, args, "Execve failed at child2");
}

int	main(int argc, char **argv)
{
	int		status;
	int		*pipes;
	int		*pipes_for_path;
	char	*path;
	pid_t	*pids;
	pid_t	pid1;
	pid_t	pid2;
	pid_t	pid;

	check_args(argv[1], argv[argc - 1], argc);
	
	pids = (pid_t *)malloc(sizeof (*pids) * argc - 4);

	pipes = create_pipes(pipes, 0);
	free_error(pipes, NULL, pid < 0, "Can't fork process");	
	pid1 = fork();
	if (pid1 == 0)
	{
		pipes_for_path = create_pipes(pipes_for_path, 0);
		pid = fork();
		free_pipes_error(pipes, pipes_for_path, pid < 0, "fork failed at main");
		if (pid == 0)
			whereis(pipes_for_path, argv[2]);
		else
		{
			close(pipes_for_path[1]);
			waitpid(pid, &status, 0);
			printf("%s\n", path = read_from_pipe(pipes_for_path[0]));
			if (child1(read_from_pipe(pipes_for_path[0]), ft_split(argv[2], ' '), pipes, argv[1]) < 0)
			{
				free(pipes_for_path);
				exit(EXIT_FAILURE);
			}
		}
	}
	else if (pid1 > 0)
	{
		waitpid(pid1, &status, 0);
		close(pipes[1]);
		char *output = read_from_pipe(pipes[0]);
		//printf("%s", output);
	}	
}