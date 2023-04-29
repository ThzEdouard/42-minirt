/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:20:39 by eflaquet          #+#    #+#             */
/*   Updated: 2023/04/29 12:22:18 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static	bool	solver_quot(t_ray *ray, t_object *sphere,
			double *t0, double *t1)
{
	t_vector	oc;
	double		a;
	double		b;
	double		c;

	oc = subtract_vector(ray->origin, sphere->center);
	a = dot(ray->direction, ray->direction);
	b = 2 * dot(oc, ray->direction);
	c = dot(oc, oc) - (sphere->diameter / 2 * sphere->diameter / 2);
	if (b * b - 4 * a * c < 0)
		return (false);
	*t0 = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
	*t1 = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
	return (true);
}

bool	intersection_sphere(t_ray *ray, t_object *sphere, double *distance)
{
	double	t0;
	double	t1;

	*distance = INFINITY;
	if (!solver_quot(ray, sphere, &t0, &t1))
		return (false);
	if (t0 < 0 && t1 < 0)
		return (false);
	if (t0 < t1)
		*distance = t0;
	else
		*distance = t1;
	return (true);
}
