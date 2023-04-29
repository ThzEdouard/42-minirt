/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 10:11:51 by eflaquet          #+#    #+#             */
/*   Updated: 2023/04/29 15:08:23 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray init_ray(t_ca cam, int x, int y)
{
    t_ray    	result;
    double   	fov_adjustment;
    double   	aspect_ratio;
	t_vector	rot_rad;

	aspect_ratio = (WIDTH) / (HEIGHT);
    fov_adjustment = tan((cam.fov * (M_PI / 180)) / 2.0);
    result.origin = cam.pv;
    result.direction.x = ((((x + 0.5) / WIDTH) * 2.0 - 1.0)
            * aspect_ratio) * fov_adjustment;
    result.direction.y = (1.0 - ((y + 0.5) / HEIGHT) * 2.0) * fov_adjustment;
    result.direction.z = -1.0;
    result.direction = normalize(result.direction);
	rot_rad.x = cam.axe.y;
	rot_rad.y = cam.axe.x;
	rot_rad.z = cam.axe.z;
	result.direction = rotate(result.direction, rot_rad);
	return (result);
}

