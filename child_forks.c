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

typedef struct s_args {
	int		*pipes;
	char	**args;
}	t_args;

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
	pid_t	pid;
	t_args	*args;

	args = allocate_struct(argv[2]);
	pid = fork();
	free_pipes_error(pipes, args->pipes, pid < 0,
			"fork failed at child_fork_first");
	if (pid == 0)
		whereis(args->pipes, argv[2], envp);
	else
	{
		close(args->pipes[1]);
		waitpid(pid, &status, 0);
		child1(read_from_pipe_path(args->pipes[0]),
				args->args, pipes, argv[1]);
		close(args->pipes[0]);
		free_ptr_arr(args->args);
		free(args->pipes);
		exit(EXIT_FAILURE);
	}
	//exit(EXIT_FAILURE);
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
