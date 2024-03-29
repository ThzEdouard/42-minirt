/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:36:23 by eflaquet          #+#    #+#             */
/*   Updated: 2023/05/09 16:28:29 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	intersection_plan(t_ray *ray, t_object *plan, double *distance)
{
	double		demon;
	t_vector	b2;

	demon = dot(plan->axis, ray->direction);
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
