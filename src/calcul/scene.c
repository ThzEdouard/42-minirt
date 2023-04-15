/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:39:20 by eflaquet          #+#    #+#             */
/*   Updated: 2023/04/15 13:13:02 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ray_scene(t_ray *ray, t_object *object, t_impact *impact)
{
	t_object	*tmp;
	double	d1 = INFINITY;
	double	d2 = INFINITY;
	double	d3 = INFINITY;
	impact->distance = INFINITY;
	impact->rgb = new_rgb(0,0,0);
	tmp = object;
	while (tmp)
	{
		if (tmp->info == SP && intersection_sphere(ray, tmp, &d1))
		{
			if (d1 < impact->distance)
			{
				impact->rgb = tmp->rgb;
				impact->distance = d1;
				d1 = INFINITY;
			}
		}

		if (tmp->info == PL && intersection_plan(tmp, ray, &d2))
		{
			if (d2 < impact->distance)
			{
				impact->rgb = tmp->rgb;
				impact->distance = d2;
				d2 = INFINITY;
			}
		}
		if (tmp->info == CY && intersection_cylindre(ray, tmp, &d3))
		{
			if (d3 < impact->distance)
			{
				impact->rgb = tmp->rgb;
				impact->distance = d3;
				d3 = INFINITY;
			}
		}
		tmp = tmp->next;
	}
}