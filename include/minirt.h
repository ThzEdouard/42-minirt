/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:20:27 by eflaquet          #+#    #+#             */
/*   Updated: 2023/04/13 10:46:06 by eflaquet         ###   ########.fr       */
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

t_coord	op_plus(t_coord a, t_coord b);
t_coord	op_moins(t_coord a, t_coord b);
t_coord	op_mult(t_coord a, t_coord b);
t_coord	add_vector(float x, float y, float z);
t_coord	op_div(t_coord a, t_coord b);
t_coord	normalize(t_coord a);

t_coord	cross(t_coord a, t_coord b);

double	magnitude(t_coord a);
double	dot(t_coord a, t_coord b);

t_ray	init_ray(t_coord origin, t_ca cam, int x, int y);
bool	intersection_sphere(t_ray *ray, t_sp *sphere, double *distance);
bool	intersection_plan(t_pl *plan, t_ray *ray, double *distance);
bool	intersection_cylindre(t_ray *ray, t_cy *cylinde, double *distance);

void	ft_free_sphere(t_sp *value);
void	ft_free_plane(t_pl *value);
void	ft_free_cy(t_cy *value);
#endif