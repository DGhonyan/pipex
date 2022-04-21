#ifndef PIPEX

# define PIPEX

char	*ft_strjoin(char *s1, char *s2);
void	to_hex_lower(unsigned int n, int is_upper, int *count);
void	ft_putnbr(int n, int *count);
void	ft_putstr(char const *s, int *count);
void	to_hex_upper(unsigned int n, int *count);
void	ft_putnbr_u(unsigned int n, int *count);
void	ft_putchar(char c, int *count);
void	print_ptr(void *p, int *count);
char	**ft_split(char *s, char c);
int		ft_printf(const char *s, ...);

#endif
