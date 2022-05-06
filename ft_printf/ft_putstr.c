/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 20:41:09 by dghonyan          #+#    #+#             */
/*   Updated: 2022/04/03 20:41:10 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

void	ft_putstr(char const *s, int *count)
{
	int		i;

	i = 0;
	if (!s)
	{
		write(1, "(null)", 6);
		*count += 6;
		return ;
	}
	while (s[i])
	{
		ft_putchar(s[i], count);
		i++;
	}
}
