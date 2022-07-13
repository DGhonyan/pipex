/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 19:03:43 by dghonyan          #+#    #+#             */
/*   Updated: 2022/05/14 19:29:56 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	child1(t_args *args)
{
	int	fd;

	if (close(args->pipes[0]) < 0)
		return (perror_ret("close failed at child1"));
	fd = open(args->file, O_RDONLY | O_CLOEXEC);
	if (fd < 0)
		return (perror_ret("open failed at child1"));
	if (dup2(args->pipes[1], STDOUT_FILENO) < 0)
		return (perror_ret("dup2 failed at child1"));
	if (dup2(fd, STDIN_FILENO) < 0)
		return (perror_ret("dup2 failed at child1 again"));
	if (close(args->pipes[1]) < 0)
		return (perror_ret("close failed at child1 again"));
	execve(args->path, args->args, args->envp);
	return (perror_ret("Execve failed at child1"));
}

int	child2(t_args *args)
{
	int	fd;

	if (close(args->pipes[1]) < 0)
		return (perror_ret("close failed at child2"));
	fd = open(args->file, O_WRONLY | O_CLOEXEC | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		return (perror_ret("open failed at child2"));
	if (dup2(args->pipes[0], STDIN_FILENO) < 0)
		return (perror_ret("dup2 failed at child2"));
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (perror_ret("dup2 failed at child2 again"));
	if (close(args->pipes[0]) < 0)
		return (perror_ret("close failed at child2 again"));
	execve(args->path, args->args, args->envp);
	return (perror_ret("Execve failed at child2"));
}

int	main(int argc, char **argv, char **envp)
{
	int		s;
	int		pipes[2];
	int		_pipes[2];
	pid_t	pids[2];

	check_args(argv, argc, envp);
	if (pipe(pipes) < 0)
	{
		perror("pipe() failed");
		exit(EXIT_FAILURE);
	}
	pids[0] = fork();
	free_error(pipes, NULL, pids[0] < 0, "Can't fork process");
	if (pids[0] == 0)
		child_fork_first(pipes, envp, argv);
	pids[1] = fork();
	if (pids[1] == 0)
		child_fork_last(pipes, envp, argv, argc);
	close(pipes[0]);
	close(pipes[1]);
	waitpid(pids[0], &s, 0);
	waitpid(pids[1], &s, 0);
	exit(WEXITSTATUS(s));
}

// while (j--)
// {

// 	pids[j + 1] = fork();
// 	if (pids[j + 1] == 0)
// 		child_fork_loop(pipes, envp, argv, j);
// 	else
// 		waitpid(pids[j + 1], &status, 0);
// }
