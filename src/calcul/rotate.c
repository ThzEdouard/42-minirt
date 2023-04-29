/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 14:18:25 by julmuntz          #+#    #+#             */
/*   Updated: 2023/04/29 14:21:03 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	rotate_x(t_vector vector, float angle)
{
	t_vector	result;

	result.x = vector.x;
	result.y = vector.y * cos(angle) - vector.z * sin(angle);
	result.z = vector.y * sin(angle) + vector.z * cos(angle);
	return (result);
}

t_vector	rotate_y(t_vector vector, float angle)
{
	t_vector	result;

	result.x = vector.x * cos(angle) + vector.z * sin(angle);
	result.y = vector.y;
	result.z = -vector.x * sin(angle) + vector.z * cos(angle);
	return (result);
}

t_vector	rotate_z(t_vector vector, float angle)
{
	t_vector	result;

	result.x = vector.x * cos(angle) - vector.y * sin(angle);
	result.y = vector.x * sin(angle) + vector.y * cos(angle);
	result.z = vector.z;
	return (result);
}

t_vector	rotate(t_vector vector, t_vector angle)
{
	vector = rotate_x(vector, angle.x);
	vector = rotate_y(vector, angle.y);
	vector = rotate_z(vector, angle.z);
	return (vector);
}
