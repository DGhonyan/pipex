/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 16:51:48 by dghonyan          #+#    #+#             */
/*   Updated: 2022/05/14 19:29:30 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "colors.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ptr_arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	perror_ret(char *errmsg)
{
	perror(errmsg);
	return (-1);
}

void	check_args(char **argv, int argc, char **envp)
{
	char	*path;

	if (argc < 5)
	{
		ft_printf(RED "Error: Not enough arguments\n" COLOR_RESET);
		exit(EXIT_FAILURE);
	}
	else if (argc > 5)
	{
		ft_printf(RED "Error: Too many arguments\n" COLOR_RESET);
		exit(EXIT_FAILURE);
	}
	path = whereis(argv[2], envp);
	if (!path)
	{
		ft_printf(RED "pipex: " "%s: Command not found\n"
			COLOR_RESET, argv[2]);
		exit(EXIT_FAILURE);
	}
	free(path);
	path = whereis(argv[argc - 2], envp);
	if (!path)
	{
		ft_printf(RED "pipex: " "%s: Command not found\n"
			COLOR_RESET, argv[argc - 2]);
		exit(EXIT_FAILURE);
	}
	free(path);
}

int	*create_pipes(int *pipes, int condition)
{
	int	a;

	if (condition)
		free(pipes);
	pipes = malloc(2 * sizeof (*pipes));
	perror_exit(!pipes, "malloc failed at create_pipes");
	a = pipe(pipes);
	free_error(pipes, NULL, a == -1, "pipe failed at create_pipes");
	return (pipes);
}
