/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 13:56:53 by eflaquet          #+#    #+#             */
/*   Updated: 2023/04/04 17:32:35 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atoi(const char *c)
{
	long	x;
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

double ft_atof(const char *c)
{
    double  entier;
    double  decimal;
    int     sign;
    int     len;

    sign = 1;
    if (*c && *c == '-')
    {
        sign = -1;
        c++;
    }
    entier = (double)ft_atoi(c);
    while (*c && *c != '.')
        c++;
    if(*c == '.')
        c++;
    decimal = (double) ft_atoi(c);
    len = ft_strlen(c);
    while (len--)
        decimal /= 10;
    return (sign * (entier + decimal));
}