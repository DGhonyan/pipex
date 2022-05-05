/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 16:51:48 by dghonyan          #+#    #+#             */
/*   Updated: 2022/04/24 16:51:49 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "pipex.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ptr_arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	check_args(char *s1, char *s2, int argc)
{
	int	a;

	if (argc < 5)
	{
		ft_printf("Error: Too few arguments\n");
		exit(EXIT_FAILURE);
	}
	a = access(s1, R_OK);
	perror_exit(a == -1, "Cannot read from a file");
	a = access(s2, W_OK);
	perror_exit(a == -1, "Cannot write to a file");
	return (0);
}

int	*create_pipes(int *pipes, int condition)
{
	int	a;

	if (condition)
		free(pipes);
	pipes = malloc(2 * sizeof (*pipes));
	perror_exit(!pipes, "malloc failed at create_pipes");
	a = pipe(pipes);
	free_error(pipes, NULL, a == -1, "pipe failed at create_pipes");
	return (pipes);
}
