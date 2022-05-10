/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perror_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 16:51:09 by dghonyan          #+#    #+#             */
/*   Updated: 2022/04/24 16:51:10 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "colors.h"

void	perror_exit(int condition, char *errmsg)
{
	if (condition)
	{
		perror(errmsg);
		exit(EXIT_FAILURE);
	}
}
