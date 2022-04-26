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

# include <stdlib.h>

int		ft_printf(const char *s, ...);
int		ptr_arr_len(char **arr);
int		check_args(char *s1, char *s2, int argc);
int		free_error_args(int *pipes, char *path, char **args, char *errmsg);
int		*create_pipes(int *pipes, int condition);
char	*new_path(char *path);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strjoin_for_read(char *s1, char c);
char	**ft_split(char const *s, char c);
char	**ft_kinda_split(char **s, char *new);
void	whereis(int *pipes, char *command, char **envp);
void	perror_exit(int condition, char *errmsg);
void	free_ptr_arr(void **arr, int size, int type);
void	free_error(int *pipes, char *path, int condition, char *errmsg);
void	free_not_error(int *pipes, char *path);
void	free_pipes_error(int *pipes1, int *pipes2, int condition, char *errmsg);
size_t	ft_strlen(char *s);

#endif
