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
#include "colors.h"

char	*read_from_pipe(int pipe)
{
	char	*s;
	char	c;
	int		a;

	s = NULL;
	while (1)
	{
		a = read(pipe, &c, 1);
		free_error(NULL, s, a == -1, "read() failed at read_from_pipe()");
		if (a == 0)
			break ;
		s = ft_strjoin_for_read(s, c);
		free_error(NULL, NULL, !s, "malloc failed at read_from_pipe");
	}
	return (s);
}

char	*read_from_pipe_path(int pipe)
{
	char	*s;
	char	c;
	int		a;

	s = NULL;
	while (1)
	{
		a = read(pipe, &c, 1);
		free_error(NULL, s, a == -1, "read() failed at read_from_pipe_path()");
		if (a == 0 || c == '\n')
			break ;
		s = ft_strjoin_for_read(s, c);
		free_error(NULL, NULL, !s, "malloc failed at read_from_pipe_path");
	}
	return (s);
}

int	child1(char *path, char **args, int *pipes, char *file)
{
	int	fd;

	if (close(pipes[0]) < 0)
		return (perror_ret("close failed at child1"));
	fd = open(file, O_RDONLY | O_CLOEXEC);
	if (fd < 0)
		return (perror_ret("open failed at child1"));
	if (dup2(pipes[1], STDOUT_FILENO) < 0)
		return (perror_ret("dup2 failed at child1"));
	if (dup2(fd, STDIN_FILENO) < 0)
		return (perror_ret("dup2 failed at child1"));
	if (close(pipes[1]) < 0)
		return (perror_ret("close failed at child1 again"));
	execve(path, args, NULL);
	return (perror_ret("Execve failed at child1"));
}

int	child2(char *path, char **args, int *pipes, char *file)
{
	int	fd;

	if (close(pipes[1]) < 0)
		return (perror_ret("close failed at child2"));
	fd = open(file, O_WRONLY | O_CLOEXEC | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		return (perror_ret("open failed at child2"));
	if (dup2(pipes[0], STDIN_FILENO) < 0)
		return (perror_ret("dup2 failed at child2"));
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (perror_ret("dup2 failed at child2"));
	if (close(pipes[0]) < 0)
		return (perror_ret("close failed at child2 again"));
	execve(path, args, NULL);
	return (perror_ret("Execve failed at child2"));
}

int	main(int argc, char **argv, char **envp)
{
	int		s;
	int		pipes[2];
	pid_t	pids[2];

	check_args(argv[1], argc);
	if (pipe(pipes) < 0)
		exit(EXIT_FAILURE);
	pids[0] = fork();
	free_error(pipes, NULL, pids[0] < 0, "Can't fork process");
	if (pids[0] == 0)
		child_fork_first(pipes, envp, argv);
	close(pipes[1]);
	pids[1] = fork();
	if (pids[1] == 0)
		child_fork_last(pipes, envp, argv);
	close(pipes[0]);
	waitpid(pids[0], &s, 0);
	waitpid(pids[1], &s, 0);
	ft_printf(GREEN "looks like success to me\n" COLOR_RESET);
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
