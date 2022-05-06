/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:45:09 by dghonyan          #+#    #+#             */
/*   Updated: 2022/03/27 17:46:32 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"

static int	v(char c)
{
	int			i;
	const char	*cases;

	cases = "cspdiuxX%";
	i = 0;
	while (cases[i])
	{
		if (cases[i] == c)
			return (i + 1);
		i++;
	}
	return (0);
}

static int	print_cases(const char *s, int *i, int *count, va_list args)
{
	if (s[*i] == '%' && s[*i + 1] && v(s[*i + 1]))
	{
		if (v(s[*i + 1]) == 1)
			ft_putchar(va_arg(args, int), count);
		else if (v(s[*i + 1]) == 2)
			ft_putstr(va_arg(args, char *), count);
		else if (v(s[*i + 1]) == 3)
			print_ptr(va_arg(args, void *), count);
		else if (v(s[*i + 1]) == 4 || v(s[*i + 1]) == 5)
			ft_putnbr(va_arg(args, int), count);
		else if (v(s[*i + 1]) == 6 || v(s[*i + 1]) == 7 || v(s[*i + 1]) == 8)
			to_hex_lower(va_arg(args, unsigned int), v(s[*i + 1]), count);
		else if (v(s[*i + 1]) == 9)
		{
			ft_putchar('%', count);
			*i += 1;
			return (9);
		}
		*i += 1;
		return (v(s[*i]));
	}
	ft_putchar(s[*i], count);
	return (0);
}

int	ft_printf(char const *s, ...)
{
	va_list	args;
	va_list	copy;
	int		i;
	int		a;
	int		c;

	i = 0;
	c = 0;
	va_start(args, s);
	while (s[i])
	{
		va_copy(copy, args);
		a = print_cases(s, &i, &c, copy);
		if (a == 1 || a == 4 || a == 5)
			va_arg(args, int);
		else if (a == 6 || a == 7 || a == 8)
			va_arg(args, unsigned int);
		else if (a == 2)
			va_arg(args, char *);
		else if (a == 3)
			va_arg(args, void *);
		i++;
	}
	va_end(args);
	return (c);
}
