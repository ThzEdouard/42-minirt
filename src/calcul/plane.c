/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:36:23 by eflaquet          #+#    #+#             */
/*   Updated: 2023/04/12 16:10:01 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	intersection_plan(t_pl *plan, t_ray *ray, double *distance)
{
	double demon = dot(plan->vod, ray->diection);
	if (demon > EPSILON)
	{
		t_coord b2 = op_moins(plan->pf, ray->origin);
		if (dot(b2, plan->vod) / demon >= 0)
		{
			*distance = dot(b2, plan->vod) / demon;
			return (true);
		}
	}
	return (false);
}

// void	ray_plane()
// {

// }