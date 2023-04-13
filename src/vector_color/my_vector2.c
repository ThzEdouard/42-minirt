/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_vector2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:41:48 by eflaquet          #+#    #+#             */
/*   Updated: 2023/04/13 16:48:40 by eflaquet         ###   ########.fr       */
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

t_vector	vector_multipli(t_vector a, double b)
{
	return (new_vector(a.x * b, a.y * b, a.z * b));
}

t_vector	vector_division(t_vector a, double b)
{
	return (new_vector(a.x / b, a.y / b, a.z / b));
}