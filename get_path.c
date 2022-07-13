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
static char	*ft_strjoin(char *s1, char *s2);

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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while ((*s1 && *s2) && (*s1 == *s2) && --n)
	{
		s1++;
		s2++;
	}
	return (*((unsigned char *)s1) - *((unsigned char *)s2));
}

static char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*res;

	i = 0;
	j = 0;
	res = (char *)malloc(sizeof (*res)
			* (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		res[i] = s1[i];
		i++;
	}
	while (j < ft_strlen(s2))
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}