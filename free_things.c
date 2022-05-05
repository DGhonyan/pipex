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

void	free_error(int *pipes, char *path, int condition, char *errmsg)
{
	if (condition)
	{
		free(pipes);
		free(path);
		perror(errmsg);
		exit(EXIT_FAILURE);
	}
}

void	free_pipes_error(int *pipes1, int *pipes2, int condition, char *errmsg)
{
	if (condition)
	{
		free(pipes1);
		free(pipes2);
		perror(errmsg);
		exit(EXIT_FAILURE);
	}
}

void	free_not_error(int *pipes, char *path)
{
	free(pipes);
	free(path);
}

int	free_error_args(int *pipes, char *path, char **args, char *errmsg)
{
	free(pipes);
	free(path);
	free_ptr_arr(args);
	perror(errmsg);
	return (-1);
}

void	free_ptr_arr(char **ptr)
{
	int	i;

	i = 0;
	while (i < ptr_arr_len(ptr))
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}
