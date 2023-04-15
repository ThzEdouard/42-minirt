/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 10:11:51 by eflaquet          #+#    #+#             */
/*   Updated: 2023/04/15 13:25:26 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	init_ray(t_ca cam, int x, int y)
{
	t_ray	result;

double	fov_adjustment;
	double	aspect_ratio;

	aspect_ratio = (WIDTH) / (HEIGHT);
	fov_adjustment = tan((cam.fov * (180 / M_PI) / 2.0));
	result.origin = cam.pv;
	result.diection.x = ((((x + 0.5) / WIDTH) * 2.0 - 1.0)
			* aspect_ratio) * fov_adjustment;
	result.diection.y = (1.0 - ((y + 0.5) / HEIGHT) * 2.0) * fov_adjustment;
	result.diection.z = -1.0;
	result.diection = normalize(result.diection);
	return (result);
}

// double a = y + 0.5 - (WIDTH) * 0.5;
// 	double b = x + 0.5 - (HEIGHT) * 0.5;
// 	double c = WIDTH / (2 * tan(cam.fov * M_PI * 0.5) / 180.0);
// 	result.origin = origin;
// 	result.diection.x = 1 * a + 0 * b + 0 * c;
// 	result.diection.y = 0 * a + 1 * b + 0 * c;
// 	result.diection.z = 0 * a + 0 * b + 1 * c;
// result.diection = normalize(result.diection);


// double	fov_adjustment;
// 	double	aspect_ratio;

// 	aspect_ratio = (WIDTH) / (HEIGHT);
// 	fov_adjustment = tan((cam.fov * (180 / M_PI) / 2.0));
// 	result.origin = cam.pv;
// 	result.diection.x = ((((x + 0.5) / WIDTH) * 2.0 - 1.0)
// 			* aspect_ratio) * fov_adjustment;
// 	result.diection.y = (1.0 - ((y + 0.5) / HEIGHT) * 2.0) * fov_adjustment;
// 	result.diection.z = -1.0;
// 	result.diection = normalize(result.diection);

// float fovrad = cam.fov *  (M_PI / 180);
// 	t_vector right = new_vector(0,0,0);
// 	t_vector up = cross(cam.axe, right);
// 	up = normalize(up);
// 	right = normalize(right);
// 	float normX = (x + 0.5) / WIDTH * 2 - 1;
// 	float normY = (y + 0.5) / HEIGHT * 2 - 1;
// 	result.diection = new_vector(cam.axe.x + right.x * normX * tan(fovrad / 2) + up.x * normY * tan(fovrad / 2),
// 	cam.axe.y + right.y * normX * tan(fovrad / 2) + up.y * normY * tan(fovrad / 2),
// 	cam.axe.z + right.z * normX * tan(fovrad / 2) + up.z * normY * tan(fovrad / 2));
// 	result.origin = cam.pv;
// 	result.diection = normalize(result.diection);

