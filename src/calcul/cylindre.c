/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylindre.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:44:44 by eflaquet          #+#    #+#             */
/*   Updated: 2023/04/29 12:22:18 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//  Vector3 oc = subtract(ray_origin, cylinder_center);

//     // Compute the coefficients of the quadratic equation
//     float a = dot(ray_direction, ray_direction) - dot(ray_direction, cylinder_axis) * dot(ray_direction, cylinder_axis);
//     float b = 2.0 * (dot(ray_direction, oc) - dot(ray_direction, cylinder_axis) * dot(oc, cylinder_axis));
//     float c = dot(oc, oc) - cylinder_radius * cylinder_radius - dot(oc, cylinder_axis) * dot(oc, cylinder_axis);

//     // Compute the discriminant
//     float discriminant = b * b - 4 * a * c;

//     // If the discriminant is negative, there is no intersection
//     if (discriminant < 0.0) {
//         return -1.0;
//     }

//     // Compute the intersection distance using the quadratic formula
//     float sqrt_discriminant = sqrt(discriminant);
//     float t1 = (-b - sqrt_discriminant) / (2.0 * a);
//     float t2 = (-b + sqrt_discriminant) / (2.0 * a);

//     // Check if either intersection distance is within the height of the cylinder
//     float t = -1.0;
//     if (t1 > 0.0 && t1 < cylinder_height) {
//         t = t1;
//     } else if (t2 > 0.0 && t2 < cylinder_height) {
//         t = t2;
//     }

// t_coord v,u;

// 	v = op_m(cylinde->vod, dot(ray->direction, cylinde->vod));
// 	v = op_moins(ray->direction, v);
// 	u = op_m(cylinde->vod, dot(op_moins(ray->origin, cylinde->pf), cylinde->vod));
// 	u = op_moins(op_moins(ray->origin, cylinde->pf), u);
// 	a = dot(v,v);
// 	b = 2 * dot(v,u);
// 	c = dot(u,u) - pow(cylinde->dia_cy / 2, 2);

//dir =axe
// v = multi_vect(cylinder.dir, dot_product(ray.dir, cylinder.dir));
//     v = sub_vect(ray.dir, v);
//     u = multi_vect(cylinder.dir, dot_product(sub_vect(ray.pos, cylinder.pos), cylinder.dir));
//     u = sub_vect(sub_vect(ray.pos, cylinder.pos), u);
//     a = dot_product(v, v);
//     b = 2 * dot_product(v, u);
//     c = dot_product(u, u) - pow(cylinder.radius2, 2);
//     x[0] = (-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
//     x[1] = (-b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
/*float intersectCylinder(Vector3 ray_origin, Vector3 ray_direction, Vector3 cylinder_center, Vector3 cylinder_axis, float cylinder_radius, float cylinder_height) {
    // Compute the vector from the ray origin to the cylinder center
    Vector3 oc = subtract(ray_origin, cylinder_center);

    // Compute the coefficients of the quadratic equation
    float a = dot(ray_direction, ray_direction) - dot(ray_direction, cylinder_axis) * dot(ray_direction, cylinder_axis);
    float b = 2.0 * (dot(ray_direction, oc) - dot(ray_direction, cylinder_axis) * dot(oc, cylinder_axis));
    float c = dot(oc, oc) - cylinder_radius * cylinder_radius - dot(oc, cylinder_axis) * dot(oc, cylinder_axis);

    // Compute the discriminant
    float discriminant = b * b - 4 * a * c;

    // If the discriminant is negative, there is no intersection
    if (discriminant < 0.0) {
        return -1.0;
    }

    // Compute the intersection distance using the quadratic formula
    float sqrt_discriminant = sqrt(discriminant);
    float t1 = (-b - sqrt_discriminant) / (2.0 * a);
    float t2 = (-b + sqrt_discriminant) / (2.0 * a);

    // Check if either intersection distance is within the height of the cylinder
    float t = -1.0;
    if (t1 > 0.0 && t1 < cylinder_height) {
        t = t1;
    } else if (t2 > 0.0 && t2 < cylinder_height) {
        t = t2;
    }

    return t;
}
*/
bool	intersection_cylindre(t_ray *ray, t_object *cylinde, double *distance)
{
	t_vector oc = subtract_vector(ray->origin, cylinde->center);
	oc = normalize(oc);
	double a, b, c;
	t_vector v,u;

	*distance = INFINITY;
	v = vector_multiply(cylinde->axis, dot(ray->direction, cylinde->axis));
	v = subtract_vector(ray->direction, v);
	u = vector_multiply(cylinde->axis, dot(subtract_vector(ray->origin, cylinde->center), cylinde->axis));
	u = subtract_vector(subtract_vector(ray->origin, cylinde->center), u);
	a = dot(v,v);
	b = 2 * dot(v,u);
	c = dot(u,u) - pow(cylinde->diameter / 2, 2);double discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (false);
    double t1 = (-b - sqrt(discriminant)) / (2.0 * a);
    double t2 = (-b + sqrt(discriminant)) / (2.0 * a);

	if (t1 < 0 && t2 < 0)
		return (false);
	double dist1 = dot(cylinde->axis, subtract_vector(vector_multiply(ray->direction, t1), subtract_vector(cylinde->center, ray->origin)));
	double dist2 = dot(cylinde->axis, subtract_vector(vector_multiply(ray->direction, t2), subtract_vector(cylinde->center, ray->origin)));
	if (!((dist1 >= 0 && dist1 <= cylinde->height && t1 > EPSILON) || (dist2 >= 0 && dist2 <= cylinde->height && t1 > EPSILON)))
		return (false);
	double    dist;
    double    x;
    if ((dist1 >= 0 && dist1 <= cylinde->height && t1 > EPSILON) && (dist2 >= 0 && dist2 <= cylinde->height && t2 > EPSILON))
    {
        dist = t1 < t2 ? dist1 : dist2;
        *distance = t1 < t2 ? t1 : t2;
		return (true);
    }
    else if (dist1 >= 0 && dist1 <= cylinde->height && t1 > EPSILON)
    {
        dist = dist1;
        *distance = t1;
		return (true);
    }
    else
    {
        dist = dist2;
        *distance = t2;
		return (true);
    }
    *distance = x;
	return (false);
}