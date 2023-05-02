/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:39:20 by eflaquet          #+#    #+#             */
/*   Updated: 2023/05/02 16:59:44 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb get_color(t_value *v, t_impact *impact)
{
    t_vector lightVector = subtract_vector(impact->p_inter, v->lum.pl);
    t_vector lightDir = normalize(lightVector);
    // double lightDistance = 1.0 / sqrt(magnitude(lightVector));
    double lightIntensity = v->lum.ratio;
    t_rgb final_color;
	float coeff = dot(lightDir, impact->normal);
	printf("%f\n", coeff);
        if (coeff < 0.0f) coeff = 0.0f;
    // Ambient component

    t_rgb ambient = rgb_multiply(impact->rgb, v->lum_am.ratio);
	t_rgb diffuse = new_rgb(0,0,0);

	//shadowing
	t_ray	ray_light;
	bool is_shadowing = true;
	ray_light.origin = addition_vector(impact->p_inter, vector_multiply(impact->normal, EPSILON));
	ray_light.direction = normalize(subtract_vector(v->lum.pl, impact->p_inter));
	double	distance = INFINITY;
	t_object *tmp = v->object;
	while (tmp)
	{
		if (tmp->info == SP && intersection_sphere(&ray_light, tmp, &distance)
			&& pow(distance + 1, 2.0) < magnitude(subtract_vector(addition_vector(impact->p_inter, vector_multiply(ray_light.direction, distance)), v->lum.pl)))
		{
			is_shadowing = false;
			break;
		}
		if (tmp->info == PL && intersection_plan(tmp, &ray_light, &distance)
			&& pow(distance + 1, 2.0) < magnitude(subtract_vector(addition_vector(impact->p_inter, vector_multiply(ray_light.direction, distance)), v->lum.pl)))
		{
			is_shadowing = false;
			break;
		}
		if (tmp->info == CY && intersection_cylindre(&ray_light, tmp, &distance)
			&& pow(distance + 1, 2.0) < magnitude(subtract_vector(addition_vector(impact->p_inter, vector_multiply(ray_light.direction, distance)), v->lum.pl)))
		{
			is_shadowing = false;
			break;
		}
		tmp = tmp->next;
	}


	if (is_shadowing)
	{
		diffuse = rgb_multiply(impact->rgb, coeff * lightIntensity);
	}
	// diffuse = rgb_multiply(impact->rgb, coeff * lightIntensity);
	final_color = addition_rgb(ambient, diffuse);
    // Clamp RGB values between 0 and 255
    final_color.r = fminf(fmaxf(final_color.r, 0.0f), 255.0f);
    final_color.g = fminf(fmaxf(final_color.g, 0.0f), 255.0f);
    final_color.b = fminf(fmaxf(final_color.b, 0.0f), 255.0f);

    return final_color;
}


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


bool	ray_scene(t_ray *ray, t_object *object, t_impact *impact,t_impact *tmp_impact, t_value *v)
{
	t_object	*tmp;
	double		d1;
	double		d2;
	double		d3;
	(void)v;
	bool j = false;
	impact->distance = INFINITY;
	impact->rgb = new_rgb(0, 0, 0);
	impact->info = NOT;
	tmp = object;
	(void)tmp_impact;

	while (tmp)
	{
		if (!v && tmp_impact->obj == tmp && tmp_impact->info == tmp->info)
		{
			tmp = tmp->next;
			continue;
		}
		if (tmp->info == SP && intersection_sphere(ray, tmp, &d1))
		{
			if (rays(ray, tmp, impact, &d1))
			{
				impact->obj = tmp;
				impact->info = SP;
				j = true;
			}
		}
		if (tmp->info == PL && intersection_plan(tmp, ray, &d2))
		{
			if (rays(ray, tmp, impact, &d2))
			{
				impact->normal = tmp->axis;
				impact->obj = tmp;
				impact->info = PL;
				j = true;
			}

		}
		if (tmp->info == CY && intersection_cylindre(ray, tmp, &d3))
		{
			if (rays(ray, tmp, impact, &d3))
			{
				impact->obj = tmp;
				impact->info = CY;
				j = true;
			}

		}
		tmp = tmp->next;
	}
	return j;
}
