/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_vector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:41:23 by eflaquet          #+#    #+#             */
/*   Updated: 2023/04/29 11:50:02 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	new_vector(float x, float y, float z)
{
	t_vector	result;

	result.x = x;
	result.y = y;
	result.z = z;
	return (result);
}

t_vector	subtract_vector(t_vector a, t_vector b)
{
	return (new_vector(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_vector	addition_vector(t_vector a, t_vector b)
{
	return (new_vector(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vector	multiply_vector(t_vector a, t_vector b)
{
	return (new_vector(a.x * b.x, a.y * b.y, a.z * b.z));
}

t_vector	division_vector(t_vector a, t_vector b)
{
	return (new_vector(a.x / b.x, a.y / b.y, a.z / b.z));
}
