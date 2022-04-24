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

void	free_not_error(int *pipes, char *path)
{
	free(pipes);
	free(path);
}

void	free_error_args(int *pipes, char *path, char **args, char *errmsg)
{
	free(pipes);
	free(path);
	free_ptr_arr((void **)args, ptr_arr_len(args), 0);
	perror(errmsg);
	exit(EXIT_FAILURE);
}

void	free_ptr_arr(void **ptr, int size, int type)
{
	int	i;

	i = 0;
	if (type == 0)
	{
		while (i < size)
		{
			free(((char **)ptr)[i]);
			i++;
		}
	}
	else if (type == 1)
	{
		while (i < size)
		{
			free(((int **)ptr)[i]);
			i++;
		}
	}
	free(ptr);
}
