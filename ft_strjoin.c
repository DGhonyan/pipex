/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 16:53:56 by dghonyan          #+#    #+#             */
/*   Updated: 2022/04/10 16:54:11 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	len(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

static void	ft_strcpy(char *s1, char *s2, size_t i, int first)
{
	int	j;

	j = 0;
	while (s2[j])
	{
		s1[i] = s2[j];
		j++;
		i++;
	}
	if (first)
		s1[i++] = ' ';
	s1[i] = '\0';
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	char	*res;

	i = 1;
	res = (char *)malloc(sizeof (*res) * (len(s1) + len(s2) + 4));
	if (!res)
		return (NULL);
	res[0] = '<';
	while (s1[i - 1])
	{
		res[i] = s1[i - 1];
		i++;
	}
	res[i] = ' ';
	i++;
	ft_strcpy(res, s2, i, 1);
	return (res);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*res;
	char	mid[3];

	i = 1;
	j = 0;
	mid = " > ";
	res = (char *)malloc(sizeof (*res) * (len(s1) + len(s2) + 6));
	if (!res)
		return (NULL);
	res[0] = '|';
	while (s1[i - 1])
	{
		res[i] = s1[i - 1];
		i++;
	}
	while (j < 3)
	{
		res[i] = mid[j];
		i++;
		j++;
	}
	ft_strcpy(res, s2, i, 0);
	return (res);
}