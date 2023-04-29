/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylindre.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:44:44 by eflaquet          #+#    #+#             */
/*   Updated: 2023/04/29 13:49:07 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	intersection_cylindre(t_ray *ray, t_object *cylinde, double *distance)
{
	t_vector oc = subtract_vector(ray->origin, cylinde->center);
	oc = normalize(oc);
	double a, b, c;
	t_vector v,u;

	*distance = INFINITY;
	v = vector_multiply(cylinde->axis, dot(ray->direction, cylinde->axis));
	v = subtract_vector(ray->direction, v);
	u = vector_multiply(cylinde->axis, dot(subtract_vector(ray->origin, cylinde->center), cylinde->axis));
	u = subtract_vector(subtract_vector(ray->origin, cylinde->center), u);
	a = dot(v,v);
	b = 2 * dot(v,u);
	c = dot(u,u) - pow(cylinde->diameter / 2, 2);double discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (false);
    double t1 = (-b - sqrt(discriminant)) / (2.0 * a);
    double t2 = (-b + sqrt(discriminant)) / (2.0 * a);

	if (t1 < 0 && t2 < 0)
		return (false);
	double dist1 = dot(cylinde->axis, subtract_vector(vector_multiply(ray->direction, t1), subtract_vector(cylinde->center, ray->origin)));
	double dist2 = dot(cylinde->axis, subtract_vector(vector_multiply(ray->direction, t2), subtract_vector(cylinde->center, ray->origin)));
	if (!((dist1 >= 0 && dist1 <= cylinde->height && t1 > EPSILON) || (dist2 >= 0 && dist2 <= cylinde->height && t1 > EPSILON)))
		return (false);
	double    dist;
    double    x;
    if ((dist1 >= 0 && dist1 <= cylinde->height && t1 > EPSILON) && (dist2 >= 0 && dist2 <= cylinde->height && t2 > EPSILON))
    {
        dist = t1 < t2 ? dist1 : dist2;
        *distance = t1 < t2 ? t1 : t2;
		return (true);
    }
    else if (dist1 >= 0 && dist1 <= cylinde->height && t1 > EPSILON)
    {
        dist = dist1;
        *distance = t1;
		return (true);
    }
    else
    {
        dist = dist2;
        *distance = t2;
		return (true);
    }
    *distance = x;
	return (false);
}