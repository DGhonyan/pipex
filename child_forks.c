/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_things.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 16:50:56 by dghonyan          #+#    #+#             */
/*   Updated: 2022/04/24 16:51:00 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "pipex.h"

t_args	*allocate_struct(char *split_str)
{
	t_args	*args;

	args = (t_args *)malloc(sizeof (*args));
	(args)->args = ft_split(split_str, ' ');
	(args)->pipes = NULL;
	(args)->pipes = create_pipes((args)->pipes, 0);
	return (args);
}

void	child_fork_first(int *pipes, char **envp, char **argv)
{
	int		status;
	char	*path;
	pid_t	pid;
	t_args	*args;

	args = allocate_struct(argv[2]);
	pid = fork();
	if (pid < 0)
	{
		free_struct(args);
		free_pipes_error(pipes, NULL, 1,
			"fork failed at child_fork_first");
	}
	if (pid == 0)
		whereis(args->pipes, argv[2], envp);
	else
	{
		close(args->pipes[1]);
		waitpid(pid, &status, 0);
		path = read_from_pipe_path(args->pipes[0]);
		child1(path, args->args, pipes, argv[1]);
		perror("Call to child1 failed");
		call_free_and_exit(path, args, pipes);
	}
}

void	child_fork_last(int *pipes, char **envp, char **argv)
{
	int		status;
	char	*path;
	pid_t	pid;
	t_args	*args;

	args = allocate_struct(argv[ptr_arr_len(argv) - 2]);
	pid = fork();
	if (pid < 0)
	{
		free_struct(args);
		free_pipes_error(pipes, NULL, pid < 0,
			"fork failed at child_fork_last");
	}
	if (pid == 0)
		whereis(args->pipes, argv[ptr_arr_len(argv) - 2], envp);
	else
	{
		close(args->pipes[1]);
		waitpid(pid, &status, 0);
		path = read_from_pipe_path(args->pipes[0]);
		child2(path, args->args, pipes, argv[ptr_arr_len(argv) - 1]);
		call_free_and_exit(path, args, pipes);
	}
}

//void	child_fork_loop(int *pipes, char **envp, char **argv, int j)
//{
//	int		*pipes_path;
//	int		status;
//	char	**command;
//	pid_t	pid;
//
//	pipes_path = NULL;
//	command = ft_split(argv[j + 3], ' ');
//	pipes_path = create_pipes(pipes_path, 0);
//	pid = fork();
//	free_pipes_error(pipes, pipes_path,
//       		pid < 0, "fork failed at child_fork_loop");
//	if (pid == 0)
//		whereis(pipes_path, argv[j + 3], envp);
//	else
//	{
//		waitpid(pid, &status, 0);
//		close(pipes_path[1]);
//		if (dup2(pipes[0], STDIN_FILENO) < 0)
//			;//perror_exit();
//		if (dup2(pipes[1], STDOUT_FILENO) < 0)
//			;
//		execve(read_from_pipe_path(pipes_path[0]),
//				command, envp);
//		exit(EXIT_FAILURE);
//	}
//}
