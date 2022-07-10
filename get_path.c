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

static char	*hello(char **arr, char *s1, char *s2, char *ret);

char	*whereis(char *command, char **envp)
{
	int		i;
	char	*slash;
	char	*exec;
	char	**path;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	path = ft_split(envp[i] + 5, ':');
	i = 0;
	while (path[i])
	{
		slash = ft_strjoin(path[i], "/");
		if (!slash)
			return (hello(path, NULL, NULL, NULL));
		exec = ft_strjoin(slash, command);
		if (!exec)
			return (hello(path, slash, NULL, NULL));
		if (!access(exec, X_OK))
			return (hello(path, slash, NULL, exec));
		hello(NULL, slash, exec, NULL);
		i++;
	}
	return (hello(path, NULL, NULL, NULL));
}

static char	*hello(char **arr, char *s1, char *s2, char *ret)
{
	if (arr)
		free_ptr_arr(arr);
	free(s1);
	free(s2);
	return (ret);
}
