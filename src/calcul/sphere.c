/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:20:39 by eflaquet          #+#    #+#             */
/*   Updated: 2023/04/11 19:33:57 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	intersect_sphere(t_sp *sphere, t_ray *ray, double t1, double t2)
{
	float	a;
	float	b;
	float	c;
	t_coord	b2;

	b2 = op_moins(ray->origin, sphere->ps);
	a = dot(ray->diection, ray->diection);
	b = 2 * dot(ray->diection, b2);
	c = dot(b2, b2) - 1;
	if (b * b - 4 * a * c < 0)
		return (false);
	t1 = (-b - sqrt(b * b - 4 * a * c )) / (2 * a);
	t2 = (-b + sqrt(b * b - 4 * a * c )) / (2 * a);
	if (t2 < 0)
		return (false);
	return (true);
}