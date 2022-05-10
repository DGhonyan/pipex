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

void	whereis(int *pipes, char *command, char **envp)
{
	char	**args;
	char	*script;

	close(pipes[0]);
	pipes[1] = dup2(pipes[1], STDOUT_FILENO);
	if (pipes[1] == -1)
	{
		return (another_function_for_which(pipes,
				NULL, pipes[1] == -1, "dup2 failed at whereis()"));
	}
	script = ft_strjoin("which ", command);
	args = ft_split(script, ' ');
	free(script);
	execve("/usr/bin/which -s", args, envp);
	perror("Execve failed at whereis()");
	free_ptr_arr(args);
	free(pipes);
	return (-1);
}
