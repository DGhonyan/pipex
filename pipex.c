/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 19:03:43 by dghonyan          #+#    #+#             */
/*   Updated: 2022/04/18 19:03:44 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "pipex.h"
/// TODO delete this the fuck out
#include <string.h>

int	check_args(char *s1, char *s2, int argc)
{
	int	a;

	a = access(s1, R_OK);
	if (argc != 5)
	{
		printf("Error: Too few arguments\n");
		exit(-1);
	}
	if (a == -1)
	{
		perror("Cannot read from a file");
		exit(-1);
	}
	a = access(s2, W_OK);
	if (a == -1)
	{
		perror("Cannot write to a file");
		exit(-1);
	}
	return (0);
}

void	child1(char *s, char **args, int pipe_write, char *f)
{
	int	fd;

	fd = open(f, O_RDONLY | O_CLOEXEC);
	fd = dup2(fd, STDIN_FILENO);
	printf("%s %s %s    ", s, args[1], f);
	pipe_write = dup2(pipe_write, STDOUT_FILENO);
	execve(s, args, NULL);
	perror("Execve failed at child1()");
	exit (-1);
}

void	child2(char *s, char **args, int pipe_read, char *f)
{
	int	fd;

	fd = open(f, O_WRONLY | O_CLOEXEC | O_TRUNC);
	fd = dup2(fd, STDOUT_FILENO);
	pipe_read = dup2(pipe_read, STDIN_FILENO);
	execve(s, args, NULL);
	perror("Execve failed at child2()");
	exit (-1);
}

int	*create_pipes(void)
{
	int	*pipes;

	pipes = malloc(2 * sizeof (*pipes));
	if (!pipes)
	{
		perror("Failed to allocate memory at create_pipes()");
		exit(-1);
	}
	if (pipe(pipes) == -1)
	{
		perror("Failed to create pipes at create_pipes()");
		exit(-1);
	}
	return (pipes);
}

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
		if (a == -1)
		{
			free(s);
			perror("Cant read from a pipe");
			exit(EXIT_FAILURE);
		}
		if (a == 0)
			break ;
		s = ft_strjoin_for_read(s, c);
		if (!s)
		{	
			perror("Can't allocate memory");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (s);
}

ssize_t	filesize(int fd)
{
	ssize_t	size;
	ssize_t	status;
	char	c;

	size = 0;
	if (fd < 0)
		return (0);
	while (1)
	{
		status = read(fd, &c, 1);
		if (status == -1)
		{
			perror("Error reading from fd");
			return (0);
		}
		if (status == 0)
			return (size);
		size++;
	}
	return (0);
}

void	which_output(int *pipes, char *command)
{
	char	**args;
	char	*script;
	int		i;

	i = 0;
	close(pipes[0]);
	pipes[1] = dup2(pipes[1], STDOUT_FILENO);
	printf("%d\n", pipes[1]);
	if (pipes[1] == -1)
		perror("TF");
	script = ft_strjoin("whereis ", command);
	args = ft_split(script, ' ');
	free(script);
	execve("/usr/bin/whereis", args, NULL);
	perror("Execve failed at which_output()");
	free_ptr_arr((void **)args, ptr_arr_len(args), 0);
	exit (EXIT_FAILURE);
}

int	**create_pipe_arr(int size)
{
	int	**pipes;
	int	i;

	pipes = (int **)malloc(size * sizeof (*pipes));
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < size)
	{
		pipes[i] = (int *)malloc(2 * sizeof (**pipes));
		if (!pipes[i])
		{
			free_ptr_arr((void **)pipes, i, 1);
			perror("Failed to allocate pipe");
			return (NULL);
		}
		if (!pipe(pipes[i]))
		{
			free_ptr_arr((void **)pipes, i, 1);
			perror("Failed to create pipe");
			return (NULL);
		}
		i++;
	}
	pipes[i] = NULL;
	return (pipes);
}

int	main(int argc, char **argv)
{
	int		fd;
	int		fd2;
	int		status;
	int		*pipes;
	int		**all_pipes;
	int		*pipes_for_path;
	char	*path;
	char	*full_command;
	char	**command_arr;
	char	**args;
	pid_t	pid;


	check_args(argv[1], argv[argc - 1], argc);
	//printf("%s\n", argv[2]);
	pipes = create_pipes();
	pid = fork();
	if (pid < 0)
	{
		perror("Failed to start child process");
		exit (EXIT_FAILURE);
	}
	else if (!pid)
	{
		which_output(pipes, argv[2]);
	}
	wait(&status);
	close(pipes[1]);
	path = read_from_pipe(pipes[0]);
	if (path[strlen(path) - 1] == '\n')
		path[strlen(path) - 1] = '\0';
	pid = fork();
	if (pid < 0)
	{
		free(pipes);
		free(path);
		perror("Can't fork process");
		exit(EXIT_FAILURE);
	}
	if (!pid)
	{
		fd = open(argv[1], O_RDONLY | O_CLOEXEC);
		//fd2 = open(argv[1], O_RDONLY | O_CLOEXEC);
		fd = dup2(fd, STDIN_FILENO);
		args = ft_split(argv[2], ' ');
		// if (!args)
		// {
		// 	free(path);
		// 	free(pipes);
		// 	perror("Memory is fucked up");
		// 	exit(EXIT_FAILURE);
		// }
		args = ft_kinda_split(args, path);
		// if (!args)
		// {
		// 	free(path);
		// 	free(pipes);
		// 	perror("Memory is fucked up even more");
		// 	exit(EXIT_FAILURE);
		// }
		execve(path, args, NULL);
		// free(path);
		// free(pipes);
		// perror("How the fuck this keeps happening");
		// exit(EXIT_FAILURE);
	}
	else
	{
		wait(&status);

	}	
	//close(pipes_for_path[1]);
	pid = fork();
	if (!pid)
	{
		close(pipes[0]);
		child1(args1[0], args1, pipes[1], argv[1]);
		return (0);
	}
	wait(&status);
	close(pipes[1]);
	child2(args2[0], args2, pipes[0], argv[argc -1]);
}
