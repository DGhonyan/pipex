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

ssize_t	filesize(int fd)
{
	ssize_t	a;
	ssize_t	size;
	char	b;

	size = 0;
	if (fd == -1)
	{
		perror("Error");
		return (-1);
	}
	while (1)
	{
		a = read(fd, &b, 1);
		if (a == -1)
		{
			perror("Can't read from a file");
			return (-1);
		}
		if (a == 0)
			break ;
		size++;
	}
	return (size);
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

int	main(int argc, char **argv)
{
	int	fd1;
	int	fd2;
	int	fd3;
	pid_t	pid;
	int pipes[2];
	int pipes2[2];
	char	*_read;

	if (check_args(argv[1], argv[4], argc))
		exit(-1);
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[1], O_RDONLY);
	_read = alloc_read(filesize(fd1), fd2);
	if (!_read)
		exit(-1);
	//printf("%s\n", _read);
	if (pipe(pipes) == -1 || fd1 == -1 || fd2 == -1)
	{
		perror("Pipe");
		exit(-1);
	}
//	pid = fork();	if (pid == 0)
//	{
//		close(pipes[0]);
//		write(pipes[1], _read, )
//	}
	//fd1 = fork();
	//wait(&fd2);

	//if (WIFEXITED(fd2))
	//	write(1, "CCCC", 4);
//	if (fd1 == 0)
//	{
//		close(pipes[0]);
//		write(pipes[1], , 4);
//	}
//	else
//		write(1, "BBBB", 4);
	//fd1 = open(argv[1], O_RDONLY);
	//fd2 = open(argv[1], O_RDONLY);
	//fd3 = open(argv[5], O_WRONLY);
	//_read = alloc_read(filesize(dup(fd1)), fd2);
	//if (!_read)
	//	exit(-1);	
}
