/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_vector2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:41:48 by eflaquet          #+#    #+#             */
/*   Updated: 2023/04/29 11:50:02 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	vector_subtract(t_vector a, double b)
{
	return (new_vector(a.x - b, a.y - b, a.z - b));
}

t_vector	vector_addition(t_vector a, double b)
{
	return (new_vector(a.x + b, a.y + b, a.z + b));
}

t_vector	vector_multiply(t_vector a, double b)
{
	return (new_vector(a.x * b, a.y * b, a.z * b));
}

t_vector	vector_division(t_vector a, double b)
{
	return (new_vector(a.x / b, a.y / b, a.z / b));
}
