/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:20:27 by eflaquet          #+#    #+#             */
/*   Updated: 2023/05/08 19:26:39 by julmuntz         ###   ########.fr       */
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
# include <stdbool.h>
# include "checker.h"

# define FAIL 0
# define SUCCESS 1

//intersections object and scene
t_ray		new_ray(t_vector origin, t_vector direction);
t_ray		init_ray(t_ca cam, int x, int y);
bool		ray_scene(t_ray *ray, t_object *obj, t_impact *impact);
bool		intersection_sphere(t_ray *ray, t_object *sphere, double *dist);
bool		intersection_plan(t_ray *ray, t_object *plan, double *dist);
bool		intersection_cylindre(t_ray *ray, t_object *cylindre, double *dist);
t_rgb		color_pixel(t_value *v, t_impact *impact);
void		ft_free_object(t_object *value);

//mlx make img
int			init_window(t_mlx *tmp_mlx, t_data *tmp_img, char *name);
void		mlx_make_img(t_end *end, t_data *img);
int			key_end(int key, t_end *end);
int			click_end(t_end *end);
void		ft_free_mlx(t_mlx *tmp_mlx, t_data *tmp_img);

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
double		magnitude(t_vector a);
double		dot(t_vector a, t_vector b);

int			check_len(t_line *line, enum s_info info);
t_object	*get_check(enum s_info t, t_line *l, t_object *v, t_value **tmps);
int			process_line(t_line *line, t_object **object, t_value **tmps);

#endif
