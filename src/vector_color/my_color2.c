/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_color2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:41:44 by eflaquet          #+#    #+#             */
/*   Updated: 2023/04/28 19:03:28 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	rgb_subtract(t_rgb a, double b)
{
	return (new_rgb((int)fmin(255, fmax(0, a.r - b)),
			(int)fmin(255, fmax(0, a.g - b)),
			(int)fmin(255, fmax(0, a.b - b))));
}

t_rgb	rgb_addition(t_rgb a, double b)
{
	return (new_rgb((int)fmin(255, fmax(0, a.r + b)),
			(int)fmin(255, fmax(0, a.g + b)),
			(int)fmin(255, fmax(0, a.b + b))));
}

t_rgb	rgb_multipli(t_rgb a, double b)
{
	return (new_rgb((int)fmin(255, fmax(0, a.r * b)),
			(int)fmin(255, fmax(0, a.g * b)),
			(int)fmin(255, fmax(0, a.b * b))));
}

t_rgb	rgb_division(t_rgb a, double b)
{
	return (new_rgb((int)fmin(255, fmax(0, a.r / b)),
			(int)fmin(255, fmax(0, a.g / b)),
			(int)fmin(255, fmax(0, a.b / b))));
}
