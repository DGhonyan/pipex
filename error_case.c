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

int	another_function_for_which(int *pipes, char *path, int c, char *errmsg)
{
	if (c)
	{
		free(pipes);
		free(path);
		perror(errmsg);
		return (-1);
	}
	return (0);
}

void	call_free_and_exit(char *path, t_args *args, int *pipes)
{
	free(pipes);
	free(path);
	free_struct(args);
	exit(EXIT_FAILURE);
}

int	*some_unrelated_func(void)
{
	int	*pipes;

	pipes = (int *)malloc(2 * sizeof (*pipes));
	if (!pipes)
	{
		perror("malloc failed at some_unrelated_func");
		exit (EXIT_FAILURE);
	}
	if (pipe(pipes) < 0)
	{
		free(pipes);
		perror("pipe failed at some_unrelated_func");
		exit (EXIT_FAILURE);
	}
	return (pipes);
}
