/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:20:27 by eflaquet          #+#    #+#             */
/*   Updated: 2023/04/14 11:40:35 by eflaquet         ###   ########.fr       */
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

t_line	*check_name_norm(char	*file, t_value **value);
int		check_id_maj(t_line *line, t_value **tmp);
int		check_id_min(t_line *line, t_value **tmp);
int		norm_file(t_line *line, t_value **value);
void	clear_line(t_line **l);

int		create_trgb(int t, int r, int g, int b);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		init_window(t_mlx *tmp_mlx, t_data *tmp_img, char *name);
void	ft_mlx_free(t_mlx *tmp_mlx, t_data *tmp_img);

t_vector	normalize(t_vector a);
t_vector	cross(t_vector a, t_vector b);

double	magnitude(t_vector a);
double	dot(t_vector a, t_vector b);

t_ray	init_ray(t_vector origin, t_ca cam, int x, int y);
bool	intersection_sphere(t_ray *ray, t_object *sphere, double *distance);
bool	intersection_plan(t_object *plan, t_ray *ray, double *distance);
bool	intersection_cylindre(t_ray *ray, t_object *cylinde, double *distance);

void	ft_free_object(t_object *value);


t_rgb	new_rgb(int r, int g, int b);
t_rgb	subtract_rgb(t_rgb a, t_rgb b);
t_rgb	addition_rgb(t_rgb a, t_rgb b);
t_rgb	multipli_rgb(t_rgb a, t_rgb b);
t_rgb	division_rgb(t_rgb a, t_rgb b);
t_rgb	rgb_subtract(t_rgb a, double b);
t_rgb	rgb_addition(t_rgb a, double b);
t_rgb	rgb_multipli(t_rgb a, double b);
t_rgb	rgb_division(t_rgb a, double b);

t_vector	new_vector(float x, float y, float z);
t_vector	subtract_vector(t_vector a, t_vector b);
t_vector	addition_vector(t_vector a, t_vector b);
t_vector	multipli_vector(t_vector a, t_vector b);
t_vector	division_vector(t_vector a, t_vector b);
t_vector	vector_subtract(t_vector a, double b);
t_vector	vector_addition(t_vector a, double b);
t_vector	vector_multipli(t_vector a, double b);
t_vector	vector_division(t_vector a, double b);

#endif