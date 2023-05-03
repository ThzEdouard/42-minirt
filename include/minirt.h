/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:20:27 by eflaquet          #+#    #+#             */
/*   Updated: 2023/05/03 10:37:46 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "mlx.h"
# include "mlx_int.h"
# include "libft.h"
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
#include <stdbool.h>
# include "checker.h"

# define FAIL 0
# define SUCCESS 1


//mlx make img
int			init_window(t_mlx *tmp_mlx, t_data *tmp_img, char *name);
int			create_trgb(int t, int r, int g, int b);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);

// bool	intersection_plan(t_ray *ray, t_object *plan, double *distance)




void		clear_line(t_line **l);

void		ft_mlx_free(t_mlx *tmp_mlx, t_data *tmp_img);

//intersection object

bool		intersection_sphere(t_ray *ray, t_object *sphere, double *distance);
bool		intersection_plan(t_object *plan, t_ray *ray, double *distance);
bool		intersection_cylindre(t_ray *ray, t_object *cylindre, double *distance);

t_ray		init_ray(t_ca cam, int x, int y);

bool	ray_scene(t_ray *ray, t_object *object, t_impact *impact,t_impact *tmp_impact, t_value *v);
void		ft_free_object(t_object *value);
t_rgb get_color(t_value *v, t_impact *impact);

//rgb vector calcul
t_rgb		new_rgb(int r, int g, int b);
t_rgb		subtract_rgb(t_rgb a, t_rgb b);
t_rgb		addition_rgb(t_rgb a, t_rgb b);
t_rgb		multiply_rgb(t_rgb a, t_rgb b);
t_rgb		division_rgb(t_rgb a, t_rgb b);
t_rgb		rgb_subtract(t_rgb a, double b);
t_rgb		rgb_addition(t_rgb a, double b);
t_rgb		rgb_multiply(t_rgb a, double b);
t_rgb		rgb_division(t_rgb a, double b);

t_vector	new_vector(double x, double y, double z);
t_vector	subtract_vector(t_vector a, t_vector b);
t_vector	addition_vector(t_vector a, t_vector b);
t_vector	multiply_vector(t_vector a, t_vector b);
t_vector	division_vector(t_vector a, t_vector b);
t_vector	vector_subtract(t_vector a, double b);
t_vector	vector_addition(t_vector a, double b);
t_vector	vector_multiply(t_vector a, double b);
t_vector	vector_division(t_vector a, double b);
t_vector	rotate_x(t_vector vector, double angle);
t_vector	rotate_y(t_vector vector, double angle);
t_vector	rotate_z(t_vector vector, double angle);
t_vector	rotate(t_vector vector, t_vector angle);
t_vector	normalize(t_vector a);
t_vector	cross(t_vector a, t_vector b);
double		magnitude(t_vector a);
double		dot(t_vector a, t_vector b);

void		ft_free_mlx(t_mlx *tmp_mlx, t_data *tmp_img);

#endif