/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:17:29 by eflaquet          #+#    #+#             */
/*   Updated: 2023/05/08 19:20:16 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	normalize(t_vector a)
{
	double		magnitude;
	t_vector	result;

	magnitude = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	result.x = a.x / magnitude;
	result.y = a.y / magnitude;
	result.z = a.z / magnitude;
	return (result);
}

double	magnitude(t_vector a)
{
	return (a.x * a.x + a.y * a.y + a.z * a.z);
}

double	dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
