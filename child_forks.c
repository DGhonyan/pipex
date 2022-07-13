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

#include "pipex.h"

void	child_fork_first(int *pipes, char **envp, char **argv)
{
	t_args	args;
	int		here;

	here = !ft_strcmp(argv[1], here_doc);
	args.file = argv[1];
	if (here)
		args.fd1 = here_doc(argv[2]);
	else
		args.fd1 = open(argv[1], O_RDONLY | O_CLOEXEC);
	if (args.fd1 < 0)
	{
		perror ("Open failed at child1");
		exit (EXIT_FAILURE);
	}
	args.args = ft_split(argv[2 + here], ' ');
	args.path = whereis(args.args[0], envp);
	args.envp = envp;
	args.pipes = pipes;
	child1(&args);
	free(args.path);
	free_ptr_arr(args.args);
	exit(EXIT_FAILURE);
}

void	child_fork_last(int *pipes, char **envp, char **argv, int argc)
{
	t_args	args;

	args.args = ft_split(argv[argc - 2], ' ');
	args.path = whereis(args.args[0], envp);
	args.file = argv[argc - 1];
	args.pipes = pipes;
	args.envp = envp;
	child2(&args);
	free_ptr_arr(args.args);
	free(args.path);
	free_ptr_arr(args.args);
	exit(EXIT_FAILURE);
}

int	here_doc(char *limiter)
{

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
