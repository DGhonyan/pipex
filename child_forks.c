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

void	child_fork_first(int *pipes, char **envp, char **argv)
{
	int		*pipes_path;
	int		status;
	pid_t	pid;

	pipes_path = NULL;
	pipes_path = create_pipes(pipes_path, 0);
	pid = fork();
	free_pipes_error(pipes, pipes_path, pid < 0,
		"fork failed at child_fork_first");
	if (pid == 0)
		whereis(pipes_path, argv[2], envp);
	else
	{
		close(pipes_path[1]);
		waitpid(pid, &status, 0);
		if (child1(read_from_pipe_path(pipes_path[0]),
				ft_split(argv[2], ' '), pipes, argv[1]) < 0)
		{
			close(pipes_path[0]);
			free(pipes_path);
			exit(EXIT_FAILURE);
		}
	}
}

void	child_fork_last(int *pipes, char **envp, char **argv)
{
	int		*pipes_path;
	int		status;
	pid_t	pid;

	pipes_path = NULL;
	pipes_path = create_pipes(pipes_path, 0);
	pid = fork();
	free_pipes_error(pipes, pipes_path, pid < 0,
		"fork failed at child_fork_last");
	if (pid == 0)
		whereis(pipes_path, argv[ptr_arr_len(argv) - 2], envp);
	else
	{
		close(pipes_path[1]);
		waitpid(pid, &status, 0);
		if (child2(read_from_pipe_path(pipes_path[0]),
				ft_split(argv[ptr_arr_len(argv) - 2], ' '),
				pipes, argv[ptr_arr_len(argv) - 1]) < 0)
		{
			close(pipes_path[0]);
			free(pipes_path);
			exit(EXIT_FAILURE);
		}
	}
}

// void	child_fork_loop(int *pipes, char **envp, char **argv, int j)
// {
// 	int		*pipes_path;
// 	int		status;
// 	pid_t	pid;
// 	char	**command;

// 	pipes_path = NULL;
// 	command = ft_split(argv[j + 3], ' ');
// 	pipes_path = create_pipes(pipes_path, 0);
// 	pid = fork();
// 	free_pipes_error(pipes, pipes_path,
//			pid < 0, "fork failed at child_fork_loop");
// 	if (pid == 0)
// 		whereis(pipes_path, argv[j + 3], envp);
// 	else
// 	{
// 		waitpid(pid, &status, 0);
// 		close(pipes_path[1]);
// 		if (dup2(pipes[0], STDIN_FILENO) < 0)
// 			;//perror_exit();
// 		if (dup2(pipes[1], STDOUT_FILENO) < 0)
// 			;
// 		execve(read_from_pipe_path(pipes_path[0]),
// 				command, envp);
// 		exit(EXIT_FAILURE);
// 	}
// }
