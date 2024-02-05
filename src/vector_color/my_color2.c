/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_color2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:41:44 by eflaquet          #+#    #+#             */
/*   Updated: 2023/04/29 11:50:02 by julmuntz         ###   ########.fr       */
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

t_rgb	rgb_multiply(t_rgb a, double b)
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
