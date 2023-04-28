/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:00:15 by eflaquet          #+#    #+#             */
/*   Updated: 2023/04/28 19:01:35 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	new_rgb(int r, int g, int b)
{
	t_rgb	result;

	result.r = r;
	result.g = g;
	result.b = b;
	return (result);
}

t_rgb	subtract_rgb(t_rgb a, t_rgb b)
{
	return (new_rgb((int)fmin(255, fmax(0, a.r - b.r)),
			(int)fmin(255, fmax(0, a.g - b.g)),
			(int)fmin(255, fmax(0, a.b - b.b))));
}

t_rgb	addition_rgb(t_rgb a, t_rgb b)
{
	return (new_rgb((int)fmin(255, fmax(0, a.r + b.r)),
			(int)fmin(255, fmax(0, a.g + b.g)),
			(int)fmin(255, fmax(0, a.b + b.b))));
}

t_rgb	multipli_rgb(t_rgb a, t_rgb b)
{
	return (new_rgb((int)fmin(255, fmax(0, a.r * b.r)),
			(int)fmin(255, fmax(0, a.g * b.g)),
			(int)fmin(255, fmax(0, a.b * b.b))));
}

t_rgb	division_rgb(t_rgb a, t_rgb b)
{
	return (new_rgb((int)fmin(255, fmax(0, a.r / b.r)),
			(int)fmin(255, fmax(0, a.g / b.g)),
			(int)fmin(255, fmax(0, a.b / b.b))));
}
