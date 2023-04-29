/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 10:11:51 by eflaquet          #+#    #+#             */
/*   Updated: 2023/04/29 12:22:18 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// t_ray	generay_ray(t_vector origin, t_vector direction)
// {

// }
t_ray	init_ray(t_ca cam, int x, int y)
{
	t_ray	result;

	double	fov_adjustment;
	double	aspect_ratio;

	aspect_ratio = (WIDTH) / (HEIGHT);
	fov_adjustment = tan((cam.fov * (180 / M_PI))/ 2.0);
	result.origin = cam.pv;
	result.direction.x = ((((x + 0.5) / WIDTH) * 2.0 - 1.0)
			* aspect_ratio) * fov_adjustment;
	result.direction.y = (1.0 - ((y + 0.5) / HEIGHT) * 2.0) * fov_adjustment;
	result.direction.z = -1.0;
	result.direction = normalize(result.direction);
	return (result);
}

// double a = y + 0.5 - (WIDTH) * 0.5;
// 	double b = x + 0.5 - (HEIGHT) * 0.5;
// 	double c = WIDTH / (2 * tan(cam.fov * M_PI * 0.5) / 180.0);
// 	result.origin = origin;
// 	result.direction.x = 1 * a + 0 * b + 0 * c;
// 	result.direction.y = 0 * a + 1 * b + 0 * c;
// 	result.direction.z = 0 * a + 0 * b + 1 * c;
// result.direction = normalize(result.direction);
/*result.origin = cam.pv;
	result.direction = new_vector(x - WIDTH / 2, y - HEIGHT / 2, -WIDTH / (2 * tan((cam.fov * M_PI / 180) / 2)));
	result.direction = normalize(result.direction);*/

// double	fov_adjustment;
// 	double	aspect_ratio;

// 	aspect_ratio = (WIDTH) / (HEIGHT);
// 	fov_adjustment = tan((cam.fov * (180 / M_PI) / 2.0));
// 	result.origin = cam.pv;
// 	result.direction.x = ((((x + 0.5) / WIDTH) * 2.0 - 1.0)
// 			* aspect_ratio) * fov_adjustment;
// 	result.direction.y = (1.0 - ((y + 0.5) / HEIGHT) * 2.0) * fov_adjustment;
// 	result.direction.z = -1.0;
// 	result.direction = normalize(result.direction);

// float fovrad = cam.fov *  (M_PI / 180);
// 	t_vector right = new_vector(0,0,0);
// 	t_vector up = cross(cam.axe, right);
// 	up = normalize(up);
// 	right = normalize(right);
// 	float normX = (x + 0.5) / WIDTH * 2 - 1;
// 	float normY = (y + 0.5) / HEIGHT * 2 - 1;
// 	result.direction = new_vector(cam.axe.x + right.x * normX * tan(fovrad / 2) + up.x * normY * tan(fovrad / 2),
// 	cam.axe.y + right.y * normX * tan(fovrad / 2) + up.y * normY * tan(fovrad / 2),
// 	cam.axe.z + right.z * normX * tan(fovrad / 2) + up.z * normY * tan(fovrad / 2));
// 	result.origin = cam.pv;
// 	result.direction = normalize(result.direction);

/*
float fovRad = cam.fov * M_PI / 180.0f;
    float aspectRatio = WIDTH / (float)HEIGHT;
    float screenPosX = ((2.0f * ((float)x + 0.5f) / (float)WIDTH) - 1.0f) * tanf(fovRad * 0.5f) * aspectRatio;
    float screenPosY = (1.0f - 2.0f * ((float)y + 0.5f) / (float)HEIGHT) * tanf(fovRad * 0.5f);
    t_vector screenPos = {screenPosX, screenPosY, -1.0f};
    float cosTheta = cosf(fovRad);
    float sinTheta = sinf(fovRad);
    float rotationMatrix[3][3] = {
        {cosTheta + (1 - cosTheta) * cam.axe.x * cam.axe.x,
         (1 - cosTheta) * cam.axe.x * cam.axe.y - cam.axe.z * sinTheta,
         (1 - cosTheta) * cam.axe.x * cam.axe.z + cam.axe.y * sinTheta},
        {(1 - cosTheta) * cam.axe.x * cam.axe.y + cam.axe.z * sinTheta,
         cosTheta + (1 - cosTheta) * cam.axe.y * cam.axe.y,
         (1 - cosTheta) * cam.axe.y * cam.axe.z - cam.axe.x * sinTheta},
        {(1 - cosTheta) * cam.axe.x * cam.axe.z - cam.axe.y * sinTheta,
         (1 - cosTheta) * cam.axe.y * cam.axe.z + cam.axe.x * sinTheta,
         cosTheta + (1 - cosTheta) * cam.axe.z * cam.axe.z}
    };
    screenPos.x = rotationMatrix[0][0] * screenPos.x + rotationMatrix[0][1] * screenPos.y + rotationMatrix[0][2] * screenPos.z;
    screenPos.y = rotationMatrix[1][0] * screenPos.x + rotationMatrix[1][1] * screenPos.y + rotationMatrix[1][2] * screenPos.z;
    screenPos.z = rotationMatrix[2][0] * screenPos.x + rotationMatrix[2][1] * screenPos.y + rotationMatrix[2][2] * screenPos.z;
    result.direction = new_vector(screenPos.x - cam.pv.x, screenPos.y - cam.pv.y, screenPos.z - cam.pv.z);
    result.direction = normalize(result.direction); // Normalisation de la direction du rayon
    result.origin = cam.pv;
*/