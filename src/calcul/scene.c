/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:39:20 by eflaquet          #+#    #+#             */
/*   Updated: 2023/05/09 16:28:41 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	rays(t_ray *ray, t_object *tmp, t_impact *impact, double *d)
{
	if ((*d) < impact->distance)
	{
		impact->p_hit = addition_vector(ray->origin,
				vector_multiply(ray->direction, (*d)));
		impact->normal = subtract_vector(impact->p_hit, tmp->center);
		impact->normal = normalize(impact->normal);
		if (tmp->info == PL)
		{
			if (dot(ray->direction, tmp->axis) > 0.0)
				impact->normal = vector_multiply(tmp->axis, -1.0);
			else
				impact->normal = tmp->axis;
		}
		impact->rgb = tmp->rgb;
		impact->distance = (*d);
		(*d) = INFINITY;
		return (SUCCESS);
	}
	return (FAIL);
}

bool	ray_scene(t_ray *ray, t_object *obj, t_impact *impact)
{
	t_object	*tmp;
	double		distance;
	bool		scene;

	tmp = obj;
	impact->distance = INFINITY;
	impact->rgb = new_rgb(0, 0, 0);
	scene = false;
	while (tmp)
	{
		distance = INFINITY;
		if (tmp->info == SP && intersection_sphere(ray, tmp, &distance))
			if (rays(ray, tmp, impact, &distance))
				scene = true;
		if (tmp->info == PL && intersection_plan(ray, tmp, &distance))
			if (rays(ray, tmp, impact, &distance))
				scene = true;
		if (tmp->info == CY && intersection_cylindre(ray, tmp, &distance))
			if (rays(ray, tmp, impact, &distance))
				scene = true;
		tmp = tmp->next;
	}
	return (scene);
}
