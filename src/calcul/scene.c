/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:39:20 by eflaquet          #+#    #+#             */
/*   Updated: 2023/04/17 19:07:39 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


bool calisShadowed(t_object *object, t_impact *impact, t_value *v)
{
	t_object	*tmp;
	t_ray	ray;
	double d;
	ray.origin = addition_vector(vector_multipli(impact->normal, ALBEDO), impact->p_inter);
	ray.diection = normalize(subtract_vector(v->lum.pl, impact->p_inter));
	//double dis = magnitude(subtract_vector( v->lum.pl, impact->p_inter));
	tmp = object;
	while (tmp)
	{
		if (tmp->info == SP && intersection_sphere(&ray, tmp, &d))
		{
				return (true);
		}
		if (tmp->info == PL && intersection_plan(tmp, &ray, &d))
		{
				return (true);
		}
		if (tmp->info == CY && intersection_cylindre(&ray, tmp, &d))
		{
				return (true);
		}
		tmp = tmp->next;
	}

	return (false);
}

t_rgb	calculAmbient(t_value *v)
{
	return (rgb_multipli(v->lum_am.rgb, v->lum_am.ratio));
}

t_rgb	calculdiffuselight(t_impact *impact, t_value *v)
{
	t_vector light_direction = normalize(v->lum.pl);
	double	diffusefactuer = dot(impact->normal, light_direction);
	diffusefactuer = fmax(0.0, diffusefactuer);
	t_rgb diffuse = new_rgb((int)impact->rgb.r * v->lum.ratio * diffusefactuer,
		 (int)impact->rgb.g * v->lum.ratio *diffusefactuer,
		 (int)impact->rgb.b * v->lum.ratio *diffusefactuer);
	diffuse.r  = fmin(fmax(diffuse.r, 0), 255);
	diffuse.g = fmin(fmax(diffuse.g, 0), 255);
	diffuse.b = fmin(fmax(diffuse.b, 0), 255);
	return (diffuse);
}

t_rgb	calculateShadowedLight(t_impact *impact, t_value *value, t_object *obj)
{
	t_rgb	result;

	bool	isShadowed;

	isShadowed = calisShadowed(obj, impact, value);
result = addition_rgb (calculAmbient(value), calculdiffuselight(impact, value));
		result.r  = fmin(fmax(result.r, 0), 255);
		result.g = fmin(fmax(result.g, 0), 255);
		result.b = fmin(fmax(result.b, 0), 255);
		(void)isShadowed;
	// if (isShadowed)
	// {
	// 	result = calculAmbient(value);
	// 	result.r  = fmin(fmax(result.r, 0), 255);
	// 	result.g = fmin(fmax(result.g, 0), 255);
	// 	result.b = fmin(fmax(result.b, 0), 255);
	// }
	// else
	// {

	// }
	return (result);
}

t_rgb	get_color(t_object *tmp, t_impact *impact, t_value *v)
{
	t_rgb	result;
	// t_vector	light_dir = subtract_vector(v->lum.pl, impact->p_inter);
	// light_dir = normalize(light_dir);
	// float nDotl = dot(impact->normal, light_dir);
	t_rgb ambiant = new_rgb(v->lum_am.ratio * v->lum_am.rgb.r,v->lum_am.ratio * v->lum_am.rgb.g,v->lum_am.ratio * v->lum_am.rgb.b);
	// t_vector	diffuse = new_vector(fmaxf(nDotl, 0) * v->lum.ratio * v->lum.rgb.r,
	// 		fmaxf(nDotl, 0) * v->lum.ratio * v->lum.rgb.g,
	// 		fmaxf(nDotl, 0) * v->lum.ratio * v->lum.rgb.b);
	// result = new_rgb(fminf(ambiant.x + diffuse.x + impact->rgb.r, 255),
	// 	fminf(ambiant.y + diffuse.y + impact->rgb.g, 255),
	// 	fminf(ambiant.z + diffuse.z + impact->rgb.b, 255));
	(void)tmp;

	result = new_rgb(impact->rgb.r + (ambiant.r - impact->rgb.r)* fmax(0, dot(normalize(subtract_vector(v->lum.pl, impact->p_inter)), impact->normal) ),
			impact->rgb.g + (ambiant.g - impact->rgb.g) * fmax(0, dot(normalize(subtract_vector(v->lum.pl, impact->p_inter)), impact->normal)),
			impact->rgb.b + (ambiant.b - impact->rgb.b) * fmax(0, dot(normalize(subtract_vector(v->lum.pl, impact->p_inter)), impact->normal)));
	return (result);
}

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
				impact->rgb = calculateShadowedLight(impact, v, object);

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
				impact->rgb = calculateShadowedLight(impact, v, object);

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
				impact->rgb = calculateShadowedLight(impact, v, object);

				d3 = INFINITY;
			}
		}
		tmp = tmp->next;
	}

}

	// printf("avant : %d %d %d\n", impact->rgb.r,impact->rgb.g,impact->rgb.b);
	// t_vector	ambiant = new_vector(v->lum_am.rgb.r * impact->rgb.r * v->lum_am.ratio,
	// 	v->lum_am.rgb.g * impact->rgb.g * v->lum_am.ratio,
	// 	v->lum_am.rgb.b * impact->rgb.b * v->lum_am.ratio);
	// t_vector	lightdir = normalize(subtract_vector(v->lum.pl, impact->p_inter));
	// float	diffusefactor = dot(impact->normal, lightdir);
	// diffusefactor = fmax(diffusefactor, 0.0);
	// t_vector	deiffuse = new_vector(0 * impact->rgb.r * v->lum.rgb.r * v->lum.ratio * diffusefactor,
	// 	0 * impact->rgb.g * v->lum.rgb.g * v->lum.ratio * diffusefactor,
	// 	0 * impact->rgb.b * v->lum.rgb.b * v->lum.ratio * diffusefactor);
	// t_vector color = new_vector(ambiant.x + deiffuse.x,ambiant.y + deiffuse.y,ambiant.z + deiffuse.z);
	// t_rgb	result = new_rgb(fmin(255, fmax(0, color.x)), fmin(255, fmax(0, color.y)), fmin(255, fmax(0, color.z)));
	// printf("apres : %d %d %d\n", result.r,result.g,result.b);