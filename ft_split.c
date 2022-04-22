/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 20:11:34 by dghonyan          #+#    #+#             */
/*   Updated: 2022/03/16 20:53:45 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "pipex.h"

static size_t	count(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		if (s[i] && s[i] != c)
		{
			while (s[i] && s[i] != c)
				i++;
			count++;
		}
		if (!s[i])
			break ;
		i++;
	}
	return (count);
}

static size_t	ft_strlen(char const *s, char c, size_t i)
{
	size_t	len;

	len = 0;
	while (s[i] && s[i] != c)
	{
		i++;
		len++;
	}
	return (len);
}

static char	*ft_strdup(const char *s, char c, size_t len, size_t *i)
{
	char	*res;
	size_t	j;
	char	*tmp;

	j = *i;
	res = malloc(len * sizeof (*res));
	tmp = res;
	if (!res)
		return (NULL);
	while (s[j] && s[j] != c)
	{
		*res = s[j];
		res++;
		*i += 1;
		j++;
	}
	*res = '\0';
	return (tmp);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	i;

	i = 0;
	res = (char **)malloc((count(s, c) + 1) * sizeof (*res));
	if (!res)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c)
		{
			*res = ft_strdup(s, c, ft_strlen(s, c, i) + 1, &i);
			if (!(*res))
				return (NULL);
			res++;
		}
		if (!s[i])
			break ;
		i++;
	}
	*res = NULL;
	return (res - count(s, c));
}

char	*ft_strdup_normal(char *s)
{
	char	*res;
	size_t	i;

	i = 0;
	res = (char *)malloc((ft_strlen(s, 0, '\0') + 1) * sizeof (*res));
	if (!res)
		return (NULL);
	while (s[i])
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	**ft_kinda_split(char **s, char *new)
{
	char	**res;
	size_t	i;

	i = 1;
	res = (char **)malloc((ptr_arr_len(s) + 1) * sizeof (*res));
	if (!res)
	{
		free_ptr_arr((void **)s, ptr_arr_len(s), 0);
		return (NULL);

	}
	res[0] = ft_strdup_normal(new);
	if (!res[0])
	{
		free_ptr_arr((void **)s, ptr_arr_len(s), 0);
		return (NULL);
	}
	while (s[i])
	{
		res[i] = ft_strdup_normal(s[i]);
		if (!res[i])
		{
			free_ptr_arr((void **)res, i, 0);
			free_ptr_arr((void **)s, ptr_arr_len(s), 0);
			return (NULL);
		}
		i++;
	}
	free_ptr_arr((void **)s, ptr_arr_len(s), 0);
	res[i] = NULL;
	return (res);
}
