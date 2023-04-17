/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:36:23 by eflaquet          #+#    #+#             */
/*   Updated: 2023/04/17 17:35:22 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	intersection_plan(t_object *plan, t_ray *ray, double *distance)
{
	double		demon;
	t_vector	b2;

	demon = dot(plan->axis, ray->diection);
	if (demon > EPSILON)
	{
		b2 = subtract_vector(plan->center, ray->origin);
		if ((double)(dot(b2, plan->axis) / demon) >= 0.0)
		{
			*distance = dot(b2, plan->axis) / demon;
			return (true);
		}
	}
	return (false);
}
