/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 20:40:45 by dghonyan          #+#    #+#             */
/*   Updated: 2022/04/03 20:40:50 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr(int n, int *count)
{
	if (n == -2147483648)
	{
		ft_putstr("-2", count);
		n = 147483648;
	}
	else if (n < 0)
	{
		ft_putchar('-', count);
		n *= -1;
	}
	if (n > 9)
		ft_putnbr(n / 10, count);
	ft_putchar((n % 10) + 48, count);
}
