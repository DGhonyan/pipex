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

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
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
	int		here;
	char	*path;
	char	**command;

	if (!ft_strcmp(TMPFILE, argv[argc - 1]))
		printf_exit("Please change the filename", 1, NULL, NULL);
	here = !ft_strcmp(argv[1], "here_doc");
	printf_exit("Not enough arguments", argc < 5 + here, NULL, NULL);
	printf_exit("Too many arguments", argc > 5 + here, NULL, NULL);
	command = ft_split(argv[2 + here], ' ');
	path = whereis(command[0], envp);
	printf_exit("", !path, argv[2 + here], command);
	free(path);
	free_ptr_arr(command);
	command = ft_split(argv[argc - 2], ' ');
	path = whereis(command[0], envp);
	printf_exit("", !path, argv[argc - 2], command);
	free(path);
	free_ptr_arr(command);
}
