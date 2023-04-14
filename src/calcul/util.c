/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:17:29 by eflaquet          #+#    #+#             */
/*   Updated: 2023/04/14 10:52:06 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	normalize(t_vector a)
{
	t_vector	result;

	result.x = a.x / sqrt(magnitude(a));
	result.y = a.y / sqrt(magnitude(a));
	result.z = a.z / sqrt(magnitude(a));
	return (result);
}

t_vector	cross(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = a.y * b.z - a.z + b.y;
	result.y = a.z * b.x - a.x + b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

double	magnitude(t_vector a)
{
	return (a.x * a.x + a.y * a.y + a.z * a.z);
}

double	dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
