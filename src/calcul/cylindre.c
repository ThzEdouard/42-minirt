/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylindre.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:44:44 by eflaquet          #+#    #+#             */
/*   Updated: 2023/05/08 19:06:02 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	calculate_origin_direction(t_ray *ray, t_object *cylindre,
		t_vector *ray_origin_projected, t_vector *ray_direction_projected)
{
	t_vector	oc;

	oc = subtract_vector(ray->origin, cylindre->center);
	*ray_origin_projected = subtract_vector(ray->direction,
			vector_multiply(cylindre->axis,
				dot(ray->direction,
					cylindre->axis)));
	*ray_direction_projected = subtract_vector(oc,
			vector_multiply(cylindre->axis,
				dot(oc,
					cylindre->axis)));
}

static void	calculate_intersection_distances(double t_values[2], t_ray *ray,
		t_object *cylindre, double dist[2])
{
	t_vector	oc;

	oc = subtract_vector(ray->origin, cylindre->center);
	dist[0] = dot(cylindre->axis,
			subtract_vector(vector_multiply(ray->direction,
					t_values[0]), oc));
	dist[1] = dot(cylindre->axis,
			subtract_vector(vector_multiply(ray->direction,
					t_values[1]), oc));
}

static bool	check_valid_intersection(double t_values[2], t_ray *ray,
		t_object *cylindre, double *distance)
{
	double	dist[2];
	bool	is_valid[2];

	calculate_intersection_distances(t_values, ray, cylindre, dist);
	is_valid[0] = (dist[0] >= 0 && dist[0] <= cylindre->height
			&& t_values[0] > EPSILON);
	is_valid[1] = (dist[1] >= 0 && dist[1] <= cylindre->height
			&& t_values[1] > EPSILON);
	if (!is_valid[0] && !is_valid[1])
		return (false);
	if (is_valid[0] && is_valid[1])
	{
		if (t_values[0] < t_values[1])
			*distance = t_values[0];
		else
			*distance = t_values[1];
	}
	else
	{
		if (is_valid[0])
			*distance = t_values[0];
		else
			*distance = t_values[1];
	}
	return (true);
}

static bool	solve_quadratic(double coeffs[3], double t_values[2])
{
	double	discriminant;

	discriminant = coeffs[1] * coeffs[1] - 4 * coeffs[0] * coeffs[2];
	if (discriminant < 0)
		return (false);
	t_values[0] = (-coeffs[1] - sqrt(discriminant)) / (2.0 * coeffs[0]);
	t_values[1] = (-coeffs[1] + sqrt(discriminant)) / (2.0 * coeffs[0]);
	return (true);
}

bool	intersection_cylindre(t_ray *ray, t_object *cylindre, double *distance)
{
	double		coeffs[3];
	double		t_values[2];
	t_vector	ray_origin_projected;
	t_vector	ray_direction_projected;

	calculate_origin_direction(ray, cylindre, &ray_origin_projected,
		&ray_direction_projected);
	coeffs[0] = dot(ray_origin_projected, ray_origin_projected);
	coeffs[1] = 2 * dot(ray_origin_projected, ray_direction_projected);
	coeffs[2] = dot(ray_direction_projected, ray_direction_projected)
		- pow(cylindre->diameter / 2, 2);
	if (!solve_quadratic(coeffs, t_values))
		return (false);
	return (check_valid_intersection(t_values, ray, cylindre, distance));
}
