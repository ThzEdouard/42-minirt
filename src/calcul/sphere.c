/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:20:39 by eflaquet          #+#    #+#             */
/*   Updated: 2023/04/12 21:26:08 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	intersection_sphere(t_ray *ray, t_sp *sphere, double *distance)
{
	t_coord oc = op_moins(ray->origin, sphere->ps);
	double a, b, c;

	a = dot(ray->diection, ray->diection);
	b = 2 * dot(oc, ray->diection);
	c = dot(oc,oc) - (sphere->dia / 2 * sphere->dia / 2);

	double discrimimant = b*b - 4 *a*c;

	if (discrimimant < 0)
		return (false);
	double t0, t1;
	t0 = (-b + sqrt(discrimimant)) / (2*a);
	t1 = (-b - sqrt(discrimimant)) / (2*a);
	if (t0 < 0 && t1 < 0)
		return (false);
	if (t0 < t1)
		*distance = t0;
	else
		*distance = t1;
	return (true);
}

// void	ray_sphere()
// {

// }
