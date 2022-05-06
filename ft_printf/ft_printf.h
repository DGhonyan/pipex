/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:46:43 by dghonyan          #+#    #+#             */
/*   Updated: 2022/03/27 17:47:42 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

void	to_hex_lower(unsigned int n, int is_upper, int *count);
void	ft_putnbr(int n, int *count);
void	ft_putstr(char const *s, int *count);
void	to_hex_upper(unsigned int n, int *count);
void	ft_putnbr_u(unsigned int n, int *count);
void	ft_putchar(char c, int *count);
void	print_ptr(void *p, int *count);
int		ft_printf(const char *s, ...);

#endif
