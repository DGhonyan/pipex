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

void	free_error(int *pipes, char *path, int condition, char *errmsg)
{
	if (condition)
	{
		free(path);
		if (errmsg)
			perror(errmsg);
		exit(EXIT_FAILURE);
	}
}

void	*free_ptr_arr(char **ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return (NULL);
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	return (NULL);
}

void	perror_exit(int condition, char *errmsg)
{
	if (condition)
	{
		perror(errmsg);
		exit(EXIT_FAILURE);
	}
}

void	printf_exit(char *msg, int condition, char *s, char **command)
{
	if (condition)
	{
		if (s)
			ft_printf(RED "Command not found: %s\n" RESET, s);
		else
			ft_printf(RED "%s\n" RESET, msg);
		free_ptr_arr(command);
		exit (EXIT_FAILURE);
	}
}
