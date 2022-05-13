/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 16:51:20 by dghonyan          #+#    #+#             */
/*   Updated: 2022/04/24 16:51:22 by dghonyan         ###   ########.fr       */
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

typedef struct s_args {
	int		*pipes;
	char	**args;
}	t_args;

int		ft_printf(const char *s, ...);
int		ptr_arr_len(char **arr);
int		check_args(char *s1, char *s2, int argc);
int		perror_ret(char *errmsg);
int		child1(char *path, char **args, int *pipes, char *file);
int		child2(char *path, char **args, int *pipes, char *file);
int		*create_pipes(int *pipes, int condition);
int		*some_unrelated_func(void);
char	*new_path(char *path);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strjoin_for_read(char *s1, char c);
char	*read_from_pipe_path(int pipe);
char	**ft_split(char const *s, char c);
void	free_error_child1(int *pipes, char *path, int condition);
void	free_error_child2(int *pipes, char *path, int condition);
void	child_fork_first(int *pipes, char **envp, char **argv);
void	child_fork_last(int *pipes, char **envp, char **argv);
void	whereis(int *pipes, char *command, char **envp);
void	free_pipes_error(int *pipes1, int *pipes2, int condition, char *errmsg);
void	call_free_and_exit(char *path, t_args *args, int *pipes);
void	perror_exit(int condition, char *errmsg);
void	free_struct(t_args *args);
void	free_error(int *pipes, char *path, int condition, char *errmsg);
void	free_not_error(int *pipes, char *path);
void	child_fork_loop(int *pipes, char **envp, char **argv, int j);
void	*free_ptr_arr(char **arr);
size_t	ft_strlen(char *s);

#endif