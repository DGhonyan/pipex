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

void	free_error(int *pipes, char *path, int condition, char *errmsg)
{
	if (condition)
	{
		free(pipes);
		free(path);
		if (errmsg)
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

void	free_struct(t_args *args)
{
	free_ptr_arr(args->args);
	free(args->pipes);
	free(args);
}

void	*free_ptr_arr(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	return (NULL);
}
