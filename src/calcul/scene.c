/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:39:20 by eflaquet          #+#    #+#             */
/*   Updated: 2023/04/28 18:54:37 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ray_scene(t_ray *ray, t_object *object, t_impact *impact, t_value *v)
{
	(void)v;

	t_object	*tmp;
	double	d1 = INFINITY;
	double	d2 = INFINITY;
	double	d3 = INFINITY;
	impact->distance = INFINITY;
	impact->rgb = new_rgb(0,0,0);
	impact->info = NOT;
	tmp = object;
	while (tmp)
	{
		if (tmp->info == SP && intersection_sphere(ray, tmp, &d1))
		{
			if (d1 < impact->distance)
			{
				impact->p_inter = new_vector(ray->origin.x + ray->diection.x * d1,
						ray->origin.y + ray->diection.y * d1,
						ray->origin.z + ray->diection.z * d1);
				impact->normal = new_vector(impact->p_inter.x - tmp->center.x,impact->p_inter.y - tmp->center.y,impact->p_inter.z - tmp->center.z);
				impact->normal = normalize(impact->normal);
				impact->rgb = tmp->rgb;
				impact->info = SP;
				impact->distance = d1;
				d1 = INFINITY;
			}
		}

		if (tmp->info == PL && intersection_plan(tmp, ray, &d2))
		{
			if (d2 < impact->distance)
			{
				impact->p_inter = new_vector(ray->origin.x + ray->diection.x * d2,
						ray->origin.y + ray->diection.y * d2,
						ray->origin.z + ray->diection.z * d2);
				impact->normal = new_vector(impact->p_inter.x - tmp->center.x,impact->p_inter.y - tmp->center.y,impact->p_inter.z - tmp->center.z);
				impact->normal = normalize(impact->normal);
				impact->rgb = tmp->rgb;
				impact->info = PL;
				impact->distance = d2;
				d2 = INFINITY;
			}
		}
		if (tmp->info == CY && intersection_cylindre(ray, tmp, &d3))
		{
			if (d3 < impact->distance)
			{
				impact->p_inter = new_vector(ray->origin.x + ray->diection.x * d3,
						ray->origin.y + ray->diection.y * d3,
						ray->origin.z + ray->diection.z * d3);
				impact->normal = new_vector(impact->p_inter.x - tmp->center.x,impact->p_inter.y - tmp->center.y,impact->p_inter.z - tmp->center.z);
				impact->normal = normalize(impact->normal);
				impact->rgb = tmp->rgb;
				impact->info = CY;
				impact->distance = d3;
				d3 = INFINITY;
			}
		}
		tmp = tmp->next;
	}

}
