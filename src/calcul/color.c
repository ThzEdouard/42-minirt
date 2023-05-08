/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:30:15 by eflaquet          #+#    #+#             */
/*   Updated: 2023/05/08 18:58:30 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_rgb	color_ambient(t_value *v, t_impact *impact)
{
	return (rgb_multiply(addition_rgb(impact->rgb, v->lum_am.rgb),
			v->lum_am.ratio));
}

static t_rgb	color_diffuse(t_value *v, t_impact *impact, bool is_shadowing)
{
	double	diffuse_coeff;
	double	diffuce_shadowing;
	t_rgb	result;

	diffuse_coeff = -dot(normalize(subtract_vector(impact->p_hit, v->lum.pl)),
			impact->normal);
	if (diffuse_coeff < 0.0f)
		diffuse_coeff = 0.0f;
	diffuce_shadowing = fmax(v->lum.ratio - v->lum_am.ratio, 0.0f);
	result = rgb_multiply(impact->rgb, diffuse_coeff * v->lum.ratio);
	if (is_shadowing)
		result = rgb_multiply(result, diffuce_shadowing);
	return (result);
}

static double	light(t_ray *ray, t_impact *impact, t_value *v, double distance)
{
	double	light_distance;

	light_distance = magnitude(subtract_vector(addition_vector(impact->p_hit,
					vector_multiply(ray->direction, distance)),
				v->lum.pl));
	return (light_distance);
}

static bool	is_shadowing(t_value *v, t_impact *impact)
{
	t_object	*tmp;
	double		distance;
	t_ray		ray_light;

	ray_light = new_ray(addition_vector(impact->p_hit,
				vector_multiply(impact->normal, EPSILON)),
			normalize(subtract_vector(v->lum.pl, impact->p_hit)));
	tmp = v->object;
	while (tmp)
	{
		distance = INFINITY;
		if (tmp->info == SP && intersection_sphere(&ray_light, tmp, &distance)
			&& pow(distance + 1, 2.0) < light(&ray_light, impact, v, distance))
			return (true);
		if (tmp->info == PL && intersection_plan(&ray_light, tmp, &distance)
			&& pow(distance + 1, 2.0) < light(&ray_light, impact, v, distance))
			return (true);
		if (tmp->info == CY && intersection_cylindre(&ray_light, tmp, &distance)
			&& pow(distance + 1, 2.0) < light(&ray_light, impact, v, distance))
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

t_rgb	color_pixel(t_value *v, t_impact *impact)
{
	t_rgb	ambient_color;
	t_rgb	diffuse_color;
	t_rgb	final_color;

	ambient_color = color_ambient(v, impact);
	diffuse_color = color_diffuse(v, impact, is_shadowing(v, impact));
	final_color = addition_rgb(ambient_color, diffuse_color);
	return (final_color);
}
