/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_whereis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 16:51:38 by dghonyan          #+#    #+#             */
/*   Updated: 2022/04/24 16:51:39 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "pipex.h"

void	whereis(int *pipes, char *command)
{
	char	**args;
	char	*script;

	close(pipes[0]);
	pipes[1] = dup2(pipes[1], STDOUT_FILENO);
	if (pipes[1] == -1)
		free_error(pipes, NULL, pipes[1] == -1, "dup2 failed at whereis()");
	script = ft_strjoin("which ", command);
	args = ft_split(script, ' ');
	free(script);
	execve("/usr/bin/which", args, NULL);
	perror("Execve failed at which_output()");
	free_ptr_arr((void **)args, ptr_arr_len(args), 0);
	exit (EXIT_FAILURE);
}
