/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:30:15 by eflaquet          #+#    #+#             */
/*   Updated: 2023/05/03 13:57:32 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static t_rgb	color_ambient(t_value *v, t_impact *impact)
{
	return (rgb_multiply(impact->rgb, v->lum_am.ratio));
}

static t_rgb	color_diffuse(t_value *v, t_impact *impact, bool is_shadowing)
{
	double	diffuse_coeff;
	double	diffuce_shadowing;
	t_rgb	result;

	diffuse_coeff = dot(normalize(subtract_vector(impact->p_inter, v->lum.pl)),
			impact->normal);
	if (diffuse_coeff < 0.0f)
		diffuse_coeff = 0.0f;
	diffuce_shadowing = v->lum.ratio - v->lum_am.ratio;
	if (diffuce_shadowing < 0.0f)
		diffuce_shadowing = 0.0f;
	result = rgb_multiply(impact->rgb, coeff * v->lum.pl);
	if (is_shadowing)
		result = rgb_multiply(diffuse, diffuce_shadowing);
	return (result);
}

static double	light(t_ray *ray, t_impact *impact, double distance)
{
	double	light_distance;

	light_distance = magnitude(subtract_vector(addition_vector(impact->p_inter,
					vector_multiply(ray->direction, distance)), v->lum.pl));
	return (light_distance);
}

static bool	is_shadowing(t_value *v, t_impact *impact)
{
	t_object	*tmp;
	double		distance;
	t_ray		ray_light;

	ray_light = new_ray(addition_vector(impact->p_inter,
				vector_multiply(impact->normal, EPSILON)),
			normalize(subtract_vector(v->lum.pl, impact->p_inter)));
	while (tmp)
	{
		distance = INFINITY;
		if (tmp->info == SP && intersection_sphere(&ray_light, tmp, &distance)
			&& pow(distance + 1, 2.0) < light(&ray_light, impact, distance))
			return (true);
		if (tmp->info == PL && intersection_plan(tmp, &ray_light, &distance)
			&& pow(distance + 1, 2.0) < light(&ray_light, impact, distance))
			return (false);
		if (tmp->info == CY && intersection_cylindre(&ray_light, tmp, &distance)
			&& pow(distance + 1, 2.0) < light(&ray_light, impact, distance))
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

t_rgb	color_pixel(t_value *v, t_impact *impact)
{
	t_rgb	final_color;

	final_color = color_ambient(v, impact);
	final_color = color_diffuse(c, impact, is_shadowing(v, impact));
	return (final_color);
}
