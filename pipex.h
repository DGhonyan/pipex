#ifndef PIPEX_H

# define PIPEX_H

void	to_hex_lower(unsigned int n, int is_upper, int *count);
void	ft_putnbr(int n, int *count);
void	ft_putstr(char const *s, int *count);
void	to_hex_upper(unsigned int n, int *count);
void	ft_putnbr_u(unsigned int n, int *count);
void	print_ptr(void *p, int *count);
void	ft_putchar(char c, int *count);
int		ft_printf(const char *s, ...);
int		ptr_arr_len(char **arr);
void	free_ptr_arr(void **arr, int size, int type);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strjoin_for_read(char *s1, char c);
char	**ft_split(char const *s, char c);
char	**ft_kinda_split(char **s, char *new);

#endif
