/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 20:41:17 by dghonyan          #+#    #+#             */
/*   Updated: 2022/04/03 20:41:18 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "ft_printf.h"

static void	to_hex_lower_p(unsigned long int n, int is_upper, int *count)
{
	char	*hex;

	if (is_upper == 8)
	{
		to_hex_upper(n, count);
		return ;
	}
	else if (is_upper == 6)
	{
		ft_putnbr_u(n, count);
		return ;
	}
	hex = "0123456789abcdef";
	if (n > 15)
		to_hex_lower_p(n / 16, is_upper, count);
	ft_putchar(hex[n % 16], count);
}

void	print_ptr(void *a, int *count)
{
	uintptr_t			a_u;

	a_u = (uintptr_t)a;
	ft_putstr("0x", count);
	to_hex_lower_p((a_u), 0, count);
}
