/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:39:20 by eflaquet          #+#    #+#             */
/*   Updated: 2023/05/03 16:03:12 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	get_color(t_value *v, t_impact *impact)
{
	t_vector	lightVector;
	t_vector	lightDir;
	double		lightIntensity;
	t_rgb		f_color;
	float		coeff;
	t_rgb		ambient;
	t_rgb		diffuse;
	t_ray		ray_light;
	bool		is_shadowing;
	double		distance;
	t_object	*tmp;
	float		shadow_factor;

	lightVector = subtract_vector(impact->p_hit, v->lum.pl);
	lightDir = normalize(lightVector);
	lightIntensity = v->lum.ratio;
	coeff = dot(lightDir, impact->normal);
	if (coeff < 0.0f)
		coeff = 0.0f;
	// Ambient component
	ambient = rgb_multiply(impact->rgb, v->lum_am.ratio);
	diffuse = new_rgb(0, 0, 0);
	// Shadowing
	is_shadowing = false;
	ray_light.origin = addition_vector(impact->p_hit,
			vector_multiply(impact->normal, EPSILON));
	ray_light.direction = normalize(subtract_vector(v->lum.pl,
				impact->p_hit));
	distance = INFINITY;
	tmp = v->object;
	while (tmp)
	{
		if (tmp->info == SP && intersection_sphere(&ray_light, tmp, &distance)
			&& pow(distance + 1,
				2.0) < magnitude(subtract_vector(addition_vector(impact->p_hit,
						vector_multiply(ray_light.direction, distance)),
					v->lum.pl)))
		{
			is_shadowing = true;
			break ;
		}
		if (tmp->info == PL && intersection_plan(&ray_light, tmp, &distance)
			&& pow(distance + 1,
				2.0) < magnitude(subtract_vector(addition_vector(impact->p_hit,
						vector_multiply(ray_light.direction, distance)),
					v->lum.pl)))
		{
			is_shadowing = false;
		}
		if (tmp->info == CY && intersection_cylindre(&ray_light, tmp, &distance)
			&& pow(distance + 1,
				2.0) < magnitude(subtract_vector(addition_vector(impact->p_hit,
						vector_multiply(ray_light.direction, distance)),
					v->lum.pl)))
		{
			is_shadowing = true;
			break ;
		}
		tmp = tmp->next;
	}
	diffuse = rgb_multiply(impact->rgb, coeff * lightIntensity);
	if (is_shadowing)
	{
		shadow_factor = 0.5f;
	}
	else
	{
		shadow_factor = 1.0f;
	}
	diffuse = rgb_multiply(diffuse, shadow_factor);
	f_color = addition_rgb(ambient, diffuse);

	// Clamp RGB values between 0 and 255
	f_color.r = fminf(fmaxf(f_color.r, 0.0f), 255.0f);
	f_color.g = fminf(fmaxf(f_color.g, 0.0f), 255.0f);
	f_color.b = fminf(fmaxf(f_color.b, 0.0f), 255.0f);
	return (f_color);
}

static int	rays(t_ray *ray, t_object *tmp, t_impact *impact, double *d)
{
	if ((*d) < impact->distance)
	{
		impact->p_hit = new_vector(ray->origin.x + ray->direction.x * (*d),
										ray->origin.y + ray->direction.y * (*d),
										ray->origin.z + ray->direction.z
											* (*d));
		impact->normal = new_vector(impact->p_hit.x - tmp->center.x,
									impact->p_hit.y - tmp->center.y,
									impact->p_hit.z - tmp->center.z);
		impact->normal = normalize(impact->normal);
		if (tmp->info == PL)
			impact->normal = tmp->axis;
		impact->rgb = tmp->rgb;
		impact->distance = (*d);
		(*d) = INFINITY;
		return (SUCCESS);
	}
	return (FAIL);
}

// static int	rays(t_ray *ray, t_object *tmp, t_impact *impact, double *d)
// {
// 	if ((*d) < impact->distance)
// 	{
// 		impact->p_hit = addition_vector(ray->origin, vector_multiply(ray->direction, (*d)));
// 		impact->normal = subtract_vector(impact->p_hit, tmp->center);
// 		impact->normal = normalize(impact->normal);
// 		if (tmp->info == PL)
// 			impact->normal = tmp->axis;
// 		impact->rgb = tmp->rgb;
// 		impact->distance = (*d);
// 		(*d) = INFINITY;
// 		return (SUCCESS);
// 	}
// 	return (FAIL);
// }

// bool	ray_scene(t_ray *ray, t_object *object, t_impact *impact,
// 		t_impact *tmp_impact, t_value *v)
// {
// 	t_object	*tmp;
// 	double		d1;
// 	double		d2;
// 	double		d3;
// 	bool		j;

// 	(void)v;
// 	j = false;
// 	impact->distance = INFINITY;
// 	impact->rgb = new_rgb(0, 0, 0);
// 	tmp = object;
// 	(void)tmp_impact;
// 	while (tmp)
// 	{
// 		if (tmp->info == SP && intersection_sphere(ray, tmp, &d1))
// 		{
// 			if (rays(ray, tmp, impact, &d1))
// 			{
// 				j = true;
// 			}
// 		}
// 		if (tmp->info == PL && intersection_plan(tmp, ray, &d2))
// 		{
// 			if (rays(ray, tmp, impact, &d2))
// 			{
// 				impact->normal = tmp->axis;
// 				j = true;
// 			}
// 		}
// 		if (tmp->info == CY && intersection_cylindre(ray, tmp, &d3))
// 		{
// 			if (rays(ray, tmp, impact, &d3))
// 			{
// 				j = true;
// 			}
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (j);
// }

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
		if (tmp->info == SP && intersection_sphere(ray, tmp, &distance))
		{
			if (rays(ray, tmp, impact, &distance))
				scene = true;
		}
		if (tmp->info == PL && intersection_plan(ray, tmp, &distance))
		{
			if (rays(ray, tmp, impact, &distance))
				scene = true;
		}
		if (tmp->info == CY && intersection_cylindre(ray, tmp, &distance))
		{
			if (rays(ray, tmp, impact, &distance))
				scene = true;
		}
		tmp = tmp->next;
	}
	return (scene);
}