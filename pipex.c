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
#include "ft_printf.h"

int	check_args(char *s1, char *s2, int argc)
{
	int	a;

	a = access(s1, R_OK);
	if (argc != 5)
	{
		printf("Error: Too few arguments\n");
		return (-1);
	}
	if (a == -1)
	{
		perror("Cannot read from a file");
		return (-1);
	}
	a = access(s2, W_OK);
	if (a == -1)
	{
		perror("Cannot write to a file");
		return (-1);
	}
	return (0);
}

char	*alloc_read(ssize_t size, int fd)
{
	char	*_read;

	if (size == -1)
		return (NULL);
	_read = malloc((size + 1) * sizeof (*_read));
	if (!_read)
	{
		perror("Can't allocate memory");
		return (NULL);
	}
	if (read(fd, _read, size) == -1)
	{
		perror("Can't read from a file");
		return (NULL);
	}
	_read[size] = '\0';
	return (_read);
}

//void	exec1(fd, pipe1, pipe2)

int	main(int argc, char **argv)
{
	int	fd;
	int	status;
	int	 pipes[2];
	char	**args1;
	char	**args2;
	char	*script1;
	char	*script2;
	pid_t	pid;
	char	buf[20];

	args1 = ft_split(argv[2], ' ');
	args2 = ft_split(argv[3], ' ');
	script1 = ft_strjoin("/bin/", args1[0]);
	script2 = ft_strjoin("/bin/", args2[0]);
	if (check_args(argv[1], argv[4], argc))
		exit(-1);
	if (pipe(pipes) == -1)
	{
		perror("Pipe");
		exit(-1);
	}
	pid = fork();
	if (pid == 0)
	{
		fd = open(argv[1], O_RDONLY | O_CLOEXEC);
		fd = dup2(fd, STDIN_FILENO);
		close(pipes[0]);
		pipes[1] = dup2(pipes[1], STDOUT_FILENO); 
		execve(script1, args1, NULL);
		perror("Execve failed child 1");
		exit(-1);
	}
	wait(&status);
	if (!WIFEXITED(status))
	{
		perror("Error running child process");
		exit(-1);
	}
	close(pipes[1]);
	pipes[0] = dup2(pipes[0], STDIN_FILENO);
	fd = open(argv[4], O_WRONLY | O_CLOEXEC | O_TRUNC);
	fd = dup2(fd, STDOUT_FILENO);
	execve(script2, args2, NULL);
	perror("Execve failed");
	exit(-1);
}
