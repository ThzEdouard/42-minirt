/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:39:20 by eflaquet          #+#    #+#             */
/*   Updated: 2023/04/30 20:13:47 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// vec3 getLitColor(in vec3 viewDir, in vec3 surfacePointPosition, in vec3 objectColor, in PointLight pointLight, in vec3 surfaceNormal)
// {
//     vec3 lightVector = surfacePointPosition - pointLight.position;
//     vec3 lightDir = normalize(lightVector);

//    	float lightIntensity = (pow(0.1, 2.) / pow(sqrt(dot(lightVector, lightVector)), 2.)) * pointLight.intensity;

//     float coeff = -dot(lightDir, surfaceNormal);

//     vec3 ambient = material.ambience * objectColor;

//     vec3 diffuse = material.diffuse * max(coeff, 0.) * objectColor * lightIntensity;

//     vec3 color = ambient + diffuse;

//     return color;
// }



t_rgb get_color(t_value *v, t_impact *impact, t_object *obj)
{
    t_vector lighVector = subtract_vector(impact->p_inter, v->lum.pl);
    t_vector lightDir = normalize(lighVector);
    double lightIntensity = v->lum.ratio;
	t_rgb final_color;
    float coeff = dot(lightDir, impact->normal);
    if (coeff < 0.0f) coeff = 0.0f;
	// printf ("%f,     %f\n", coeff, lightIntensity);
    t_rgb ambient = rgb_multiply(addition_rgb(obj->rgb, v->lum_am.rgb), v->lum_am.ratio);
    t_rgb diffuse = rgb_multiply(obj->rgb, coeff * lightIntensity);

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
		{
			if (rays(ray, tmp, impact, &d1))
			{
				impact->obj = tmp;
				impact->info = SP;
				impact->rgb = get_color(v, impact, tmp);
			}
		}
		if (tmp->info == PL && intersection_plan(tmp, ray, &d2))
		{
			if (rays(ray, tmp, impact, &d2))
			{
				impact->normal = tmp->axis;
				impact->obj = tmp;
				impact->info = PL;
				impact->rgb = get_color(v, impact, tmp);
			}

		}
		if (tmp->info == CY && intersection_cylindre(ray, tmp, &d3))
		{
			if (rays(ray, tmp, impact, &d3))
			{
				impact->obj = tmp;
				impact->info = CY;
				impact->rgb = get_color(v, impact, tmp);
			}

		}
		tmp = tmp->next;
	}
}
