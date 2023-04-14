/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:39:20 by eflaquet          #+#    #+#             */
/*   Updated: 2023/04/14 18:28:57 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ray_scene(t_ray *ray, t_object *object, t_impact *impact)
{
	t_object	*tmp;
	double	d1 = INFINITY;
	double	d2 = INFINITY;
	double	d3 = INFINITY;
	impact->rgb = new_rgb(0,0,0);
	tmp = object;
	while (tmp)
	{
		if (tmp->info == SP && intersection_sphere(ray, tmp, &d1))
			impact->rgb = tmp->rgb;
		if (tmp->info == PL && intersection_plan(tmp, ray, &d2))
			impact->rgb = tmp->rgb;
		if (tmp->info == CY && intersection_cylindre(ray, tmp, &d3))
			impact->rgb = tmp->rgb;
		tmp = tmp->next;
	}
}