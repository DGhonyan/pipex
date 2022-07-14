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

#include "pipex.h"

static void	perror_exit_cond(char *errmsg, int cond)
{
	if (cond)
	{
		perror(errmsg);
		exit (EXIT_FAILURE);
	}
}

static char	*ft_strjoin_for_read(char *s1, char *s2)
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
	free(s1);
	while (j < ft_strlen(s2))
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
}

static void	free_stuff_and_exit(char **arr, char *s, char *errmsg)
{
	if (errmsg)
		perror (errmsg);
	if (arr)
		free_ptr_arr(arr);
	free(s);
	exit (EXIT_FAILURE);
}

int	get_next_line_new(char *limiter)
{
	char	*s;
	char	*limit;
	char	c[1000000];
	int		a;
	int		fd;

	s = NULL;
	limit = ft_strjoin(limiter, "\n");
	if (!limit)
		return (-1);
	fd = open(TMPFILE, O_RDWR | O_CLOEXEC | O_TRUNC | O_CREAT, 0644);
	perror_exit(fd < 0, "Can't open temp");
	while (1)
	{
		a = read(STDIN_FILENO, c, 1000000);
		c[a] = '\0';
		if (!ft_strcmp(c, limit))
			break ;
		s = ft_strjoin_for_read(s, c);
	}
	write(fd, s, ft_strlen(s) - 1);
	free(s);
	free(limit);
	close (fd);
	return (open (TMPFILE, O_RDWR));
}
