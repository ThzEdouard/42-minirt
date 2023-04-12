/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:17:29 by eflaquet          #+#    #+#             */
/*   Updated: 2023/04/12 10:46:49 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coord	op_plus(t_coord a, t_coord b)
{
	t_coord	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

t_coord	op_moins(t_coord a, t_coord b)
{
	t_coord	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

t_coord	op_mult(t_coord a, t_coord b)
{
	t_coord	result;

	result.x = a.x * b.x;
	result.y = a.y * b.y;
	result.z = a.z * b.z;
	return (result);
}

t_coord	op_div(t_coord a, t_coord b)
{
	t_coord	result;

	result.x = a.x / b.x;
	result.y = a.y / b.y;
	result.z = a.z / b.z;
	return (result);
}

t_coord	normalize(t_coord a)
{
	t_coord	result;

	result.x = a.x / sqrt(magnitude(a));
	result.y = a.y / sqrt(magnitude(a));
	result.z = a.z / sqrt(magnitude(a));
	return (result);
}

t_coord	cross(t_coord a, t_coord b)
{
	t_coord	result;

	result.x = a.y * b.z - a.z + b.y;
	result.y = a.z * b.x - a.x + b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

double	magnitude(t_coord a)
{
	return (a.x * a.x + a.y * a.y + a.z * a.z);
}

double	dot(t_coord a, t_coord b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_coord	add_vector(float x, float y, float z)
{
	t_coord	result;

	result.x = x;
	result.y = y;
	result.z = z;
	return (result);
}