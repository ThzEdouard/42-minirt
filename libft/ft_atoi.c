/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 13:56:53 by eflaquet          #+#    #+#             */
/*   Updated: 2023/01/10 14:51:53 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *c)
{
	int	x;
	int	nb_sign;

	x = 0;
	nb_sign = 1;
	while ((*c >= 9 && *c <= 13) || *c == 32)
		c++;
	if (*c == 43 || *c == 45)
	{
		if (*c == 45)
			nb_sign *= -1;
		c++;
	}
	while (*c >= 48 && *c <= 57)
		x = x * 10 + *c++ - '0';
	return (nb_sign * x);
}

// double ft_atof(const char *nptr)
// {

// }