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
		perror("malloc failed at create_pipes");
		exit (EXIT_FAILURE);
	}
	if (pipe(pipes) < 0)
	{
		free(pipes);
		perror("pipe failed at create_pipes");
		exit (EXIT_FAILURE);
	}
	return (pipes);
}
