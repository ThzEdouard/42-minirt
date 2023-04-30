/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:39:20 by eflaquet          #+#    #+#             */
/*   Updated: 2023/04/30 11:02:35 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


static int	rays(t_ray *ray, t_object *tmp, t_impact *impact, double *d)
{
	if ((*d) < impact->distance)
	{
		impact->p_inter = new_vector(ray->origin.x + ray->direction.x * (*d),
				ray->origin.y + ray->direction.y * (*d),
				ray->origin.z + ray->direction.z * (*d));
		impact->normal = new_vector(impact->p_inter.x - tmp->center.x,
				impact->p_inter.y - tmp->center.y, impact->p_inter.z
				- tmp->center.z);
		impact->normal = normalize(impact->normal);
		impact->rgb = tmp->rgb;
		impact->distance = (*d);
		(*d) = INFINITY;
		return (SUCCESS);
	}
	return (FAIL);
}

void	ray_scene(t_ray *ray, t_object *object, t_impact *impact, t_value *v)
{
	t_object	*tmp;
	double		d1;
	double		d2;
	double		d3;
	(void)v;

	impact->distance = INFINITY;
	impact->rgb = new_rgb(0, 0, 0);
	impact->info = NOT;
	tmp = object;
	while (tmp)
	{
		if (tmp->info == SP && intersection_sphere(ray, tmp, &d1))
			rays(ray, tmp, impact, &d1);
		if (tmp->info == PL && intersection_plan(tmp, ray, &d2))
			rays(ray, tmp, impact, &d2);
		if (tmp->info == CY && intersection_cylindre(ray, tmp, &d3))
			rays(ray, tmp, impact, &d3);
		tmp = tmp->next;
	}
}
