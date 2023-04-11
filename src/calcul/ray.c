/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 10:11:51 by eflaquet          #+#    #+#             */
/*   Updated: 2023/04/11 20:06:57 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	init_ray(t_coord origin, int x, int y)
{
	t_ray	result;

	result.origin = origin;
	result.diection.x = y - WIDTH / 2;
	result.diection.y = x - HEIGHT / 2;
	result.diection.z = -WIDTH / 2 * (2 * tan((70 * M_PI / 180) / 2));
	result.diection = normalize(op_moins(result.diection, origin));
	return (result);
}

double position(t_ray *ray, double t)
{
	t_coord	result;

	result = op_plus(ray->diection, ray->origin);
	return (result.x + result.y + result.z *t);
}
