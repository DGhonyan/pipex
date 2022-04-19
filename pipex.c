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
#include "pipex.h"

int	check_commands(char *s1, char *s2)
{
	int	a;

	a = system(s1);
	if (a == 0)
	{
		perror("Error first command");
		return (-1);
	}
	a = system(s2);
	if (a == 0)
	{
		perror("Error second command");
		return (-1);
	}
	return (0);
}

int	check_args(char *s1, char *s2, int argc)
{
	int	a;

	a = access(s1, R_OK);
	if (argc != 5)
	{
		ft_printf("Error: Too few arguments\n");
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

int	call_system(char *s)
{
	if (system(s) == -1)
	{
		perror("Error");
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
			perror("Error");
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
	if (!_read || read(fd, _read, size) == -1)
	{
		perror("Error");
		return (NULL);
	}
	_read[size] = '\0';
	return (_read);
}

int	main(int argc, char **argv)
{
	int	fd1;
	int	fd2;
	int fd3;
	int pipes[2];
	char	*_read;

	if (check_args(argv[1], argv[4], argc))
		exit(-1);
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[1], O_RDONLY);
	fd3 = open(argv[5], O_WRONLY);
	_read = alloc_read(filesize(dup(fd1)), fd2);
	if (!_read)
		exit(-1);
		
}