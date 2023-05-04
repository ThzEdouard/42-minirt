/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 10:34:05 by eflaquet          #+#    #+#             */
/*   Updated: 2023/05/04 13:59:20 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include "struct.h"
# define CHAR_INT_MAX "2147483647"
# define CHAR_INT_MIN "-2147483648"

//Error code ligne;
# define ERROR_AMB "\033[1;31mError\nAmbient light problem {identifier, ambient lighting ratio in range [0.0,1.0], R,G,B colors in range [0-255]}\n\033[0m"
# define ERROR_LIGHT "\033[1;31mError\nLight problem {identifier, x,y,z coordinates of the light point, the light brightness ratio in range [0.0,1.0]}\n\033[0m"
# define ERROR_CAM "\033[1;31mError\nCamera problem {identifier, x,y,z coordinates of the view point, 3d normalized orientation vector. In range [-1,1] for each x,y,z axis, FOV : Horizontal field of view in degrees in range [0,180]}\033[0m\n"
# define ERROR_SPHERE "\033[1;31mError\nSphere problem {identifier, x,y,z coordinates of the sphere center, the sphere diameter, R,G,B colors in range [0-255]}\033[0m\n"
# define ERROR_PLAN "\033[1;31mError\nPlan problem {identifier, x,y,z coordinates of a point in the plane, 3d normalized normal vector. In range [-1,1] for each x,y,z axis, R,G,B colors in range [0-255]}\033[0m\n"
# define ERROR_CYLINDRE "\033[1;31mError\nCylindre problem {identifier}\033[0m\n"
//faire les msg ERROR malloc
# define ERROR_M_AMB "\033[1;31mError\nMalloc Ambient light problem\n\033[0m"
# define ERROR_M_LIGHT "\033[1;31mError\nMalloc Light problem\n\033[0m"
# define ERROR_M_CAM "\033[1;31mError\nMalloc Camera problem\033[0m\n"
# define ERROR_M_SPHERE "\033[1;31mError\nMalloc Sphere problem\033[0m\n"
# define ERROR_M_PLAN "\033[1;31mError\nMalloc Plan problem\033[0m\n"
# define ERROR_M_CYLINDRE "\033[1;31mError\nMalloc Cylindre problem\033[0m\n"

t_line		*check_name_norm(char	*file, t_value **value);
int			check_id_maj(t_line *line, t_value **tmp);
int			check_id_min(t_line *line, t_value **tmp);
int			norm_file(t_line *line, t_value **value);
int			check_range_int(int min, int max, int nb);
int			check_range_double(double min, double max, double nb);
int			check_rgb(char *line);
int			check_int_max_min(char *line);
int			check_value(char **array_tmp, int *starts);
int			check_line_range(char *line);
int			check_coord(char *line);
int			check_vector(char *line);
int			check_a(char *tmp, int start, t_la *tmp_la);
int			check_c(char *tmp, int start, t_ca *tmp_cam);
int			check_l(char *tmp, int start, t_l *tmp_lum);
t_object	*check_sp(char *tmp, int start);
t_object	*check_pl(char *tmp, int start);
t_object	*check_cy(char *tmp, int start);
void		clear_line(t_line **l);
#endif