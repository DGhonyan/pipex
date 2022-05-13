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

#include "pipex.h"

static void	_free(int *pipes, char *script, char **args, char *errmsg)
{
	free(pipes);
	free(script);
	free_ptr_arr(args);
	perror(errmsg);
	exit(EXIT_FAILURE);
}

void	whereis(int *pipes, char *command, char **envp)
{
	char	**args;
	char	*script;

	if (close(pipes[0]) < 0)
		_free(pipes, NULL, NULL, "close failed at whereis()");
	if (dup2(pipes[1], STDOUT_FILENO) < 0)
		_free(pipes, NULL, NULL, "dup2 failed at whereis()");
	args = ft_split(command, ' ');
	if (!args)
		_free(pipes, NULL, NULL, "split failed at whereis()");
	script = ft_strjoin("which ", args[0]);
	if (!script)
		_free(pipes, NULL, args, "strjoin failed at whereis()");
	free_ptr_arr(args);
	args = ft_split(script, ' ');
	if (!args)
		_free(pipes, script, NULL, "split failed at whereis() 2");
	execve("/usr/bin/which", args, envp);
	_free(pipes, script, args, "Execve failed at whereis()");
}
