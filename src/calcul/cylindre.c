/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylindre.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:44:44 by eflaquet          #+#    #+#             */
/*   Updated: 2023/05/09 14:27:27 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	calcul_dis(t_ray *ray, t_object *cy, t_vector *vec, double *var)
{
	vec[0] = subtract_vector(ray->origin, cy->center);
	vec[0] = normalize(vec[0]);
	vec[1] = vector_multiply(cy->axis, dot(ray->direction, cy->axis));
	vec[1] = subtract_vector(ray->direction, vec[1]);
	vec[2] = vector_multiply(cy->axis, dot(subtract_vector(ray->origin,
					cy->center), cy->axis));
	vec[2] = subtract_vector(subtract_vector(ray->origin, cy->center),
			vec[2]);
	var[0] = dot(vec[1], vec[1]);
	var[1] = 2 * dot(vec[1], vec[2]);
	var[2] = dot(vec[2], vec[2]) - pow(cy->diameter / 2, 2);
	var[7] = var[1] * var[1] - 4 * var[0] * var[2];
	if (var[7] < 0)
		return (false);
	var[3] = (-var[1] - sqrt(var[7])) / (2.0 * var[0]);
	var[4] = (-var[1] + sqrt(var[7])) / (2.0 * var[0]);
	if (var[3] < 0 && var[4] < 0)
		return (false);
	var[5] = dot(cy->axis, subtract_vector(vector_multiply(ray->direction,
					var[3]), subtract_vector(cy->center, ray->origin)));
	var[6] = dot(cy->axis, subtract_vector(vector_multiply(ray->direction,
					var[4]), subtract_vector(cy->center, ray->origin)));
	return (true);
}

bool	intersection_cylindre(t_ray *ray, t_object *cy, double *distance)
{
	t_vector	vec[3];
	double		var[8];

	(void)vec;
	if (!calcul_dis(ray, cy, vec, var))
		return (false);
	if (!((var[5] >= 0 && var[5] <= cy->height && var[3] > EPSILON)
			|| (var[6] >= 0 && var[6] <= cy->height && var[3] > EPSILON)))
		return (false);
	if ((var[5] >= 0 && var[5] <= cy->height && var[3] > EPSILON)
		&& (var[6] >= 0 && var[6] <= cy->height && var[4] > EPSILON))
	{
		if (var[3] < var[4])
			*distance = var[3];
		else
			*distance = var[4];
		return (true);
	}
	else if (var[5] >= 0 && var[5] <= cy->height && var[3] > EPSILON)
		return (*distance = var[3], true);
	else
		return (*distance = var[4], true);
	return (false);
}
