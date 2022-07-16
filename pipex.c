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
	if (dup2(args->pipes[1], STDOUT_FILENO) < 0)
		return (perror_ret("dup2 failed at child1"));
	if (dup2(args->fd1, STDIN_FILENO) < 0)
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
	if (!ft_strcmp(args->argv[1], "here_doc"))
		fd = open(args->file, O_WRONLY | O_CLOEXEC
				| O_CREAT | O_APPEND, 0644);
	else
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

void	cleanup(int *pipes, pid_t *pids, int *s)
{
	close(pipes[0]);
	close(pipes[1]);
	waitpid(pids[0], s, 0);
	unlink(TMPFILE);
	waitpid(pids[1], s, 0);
}

void	call_forks(int argc, char **argv, pid_t pids, char **envp)
{
	int	i;
	int	j;

	i = 1 + !(ft_strcmp(argv[1], "here_doc"));
	j = argc - 2;// + !(ft_strcmp(argv[1], "here_doc"));
	while (i < argc - 2)
	{
		if (i == 1 + !(ft_strcmp(argv[1], "here_doc")))
		{
			pids[0] = fork();
			free_error(pipes, NULL, pids[0] < 0, "Can't fork process");
			if (pids[0] == 0)
				child_fork_first(pipes, envp, argv, here_fd);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		s;
	t_args	args;
	int		here_fd;
	int		pipes[2];
	pid_t	pids[2];

	args.argv = argv;
	args.argc = argc;
	args.envp = envp;
	unlink(TMPFILE);
	check_args(argv, argc, envp);
	if (!ft_strcmp(argv[1], "here_doc"))
		here_fd = get_next_line_new(argv[2]);
	else
		here_fd = open(argv[1], O_RDONLY | O_CLOEXEC);
	s = pipe(pipes);
	perror_exit(s < 0, "pipe() failed");
	pids[0] = fork();
	free_error(pipes, NULL, pids[0] < 0, "Can't fork process");
	if (pids[0] == 0)
		child_fork_first(pipes, envp, argv, here_fd);
	pids[1] = fork();
	if (pids[1] == 0)
		child_fork_last(pipes, envp, argv, argc);
	cleanup(pipes, pids, &s);
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
