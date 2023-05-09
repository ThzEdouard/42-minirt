/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 10:11:51 by eflaquet          #+#    #+#             */
/*   Updated: 2023/05/09 13:39:39 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	new_ray(t_vector origin, t_vector direction)
{
	t_ray	result;

	result.origin = origin;
	result.direction = direction;
	return (result);
}

t_ray	init_ray(t_ca cam, int x, int y)
{
	t_vector		result;
	double			fov_adjustment;
	double			aspect_ratio;
	t_vector		rot_rad;

	aspect_ratio = (double)(WIDTH) / (double)(HEIGHT);
	fov_adjustment = tan((cam.fov * (M_PI / 180)) / 2.0);
	result.x = ((((x + 0.5) / WIDTH) * 2.0 - 1.0)
			* aspect_ratio) * fov_adjustment;
	result.y = (1.0 - ((y + 0.5) / HEIGHT) * 2.0) * fov_adjustment;
	result.z = -1.0;
	result = normalize(result);
	rot_rad.x = cam.axe.y;
	rot_rad.y = cam.axe.x;
	rot_rad.z = cam.axe.z;
	result = rotate(result, rot_rad);
	return (new_ray(cam.pv, result));
}
