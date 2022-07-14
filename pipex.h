/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 16:51:20 by dghonyan          #+#    #+#             */
/*   Updated: 2022/05/14 19:29:42 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>

# include "colors.h"

# define TMPFILE "J98hAOSDKs%$#ASDKH"

typedef struct s_args {
	int		fd1;
	char	*file;
	int		*pipes;
	char	*path;
	char	**args;
	char	**argv;
	char	**envp;
}	t_args;

int		ft_printf(const char *s, ...);
int		perror_ret(char *errmsg);
int		child1(t_args *args);
int		child2(t_args *args);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(char *s1, char *s2);
int		get_next_line_new(char *limiter);
char	*ft_strjoin(char *s1, char *s2);
char	*whereis(char *command, char **envp);
char	**ft_split(char const *s, char c);
void	printf_exit(char *msg, int condition, char *s, char **command);
void	check_args(char **argv, int argc, char **envp);
void	child_fork_first(int *pipes, char **envp, char **argv, int fd1);
void	child_fork_last(int *pipes, char **envp, char **argv, int argc);
void	perror_exit(int condition, char *errmsg);
void	free_error(int *pipes, char *path, int condition, char *errmsg);
void	child_fork_loop(int *pipes, char **envp, char **argv, int j);
void	*free_ptr_arr(char **arr);
size_t	ft_strlen(char *s);

#endif
