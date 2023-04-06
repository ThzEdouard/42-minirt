/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 10:34:05 by eflaquet          #+#    #+#             */
/*   Updated: 2023/04/06 17:11:13 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include "struct.h"
# define CHAR_INT_MAX "2147483647"
# define CHAR_INT_MIN "-2147483648"

int		check_range_int(int min, int max, int nb);
int		check_range_float(float min, float max, float nb);
int		check_rgb(char *line);
int		check_int_max_min(char *line);
int		check_value(char **array_tmp, int *starts);
int		check_line_range(char *line);
int		check_coord(char *line);
int		check_vector(char *line);
int		check_a(char *tmp, int start, t_la *tmp_la);
int		check_c(char *tmp, int start, t_ca *tmp_cam);
int		check_l(char *tmp, int start, t_l *tmp_lum);
int		check_sp(char *tmp, int start, t_sp **tmp_sp);
int		check_pl(char *tmp, int start, t_pl **tmp_pl);
int		check_cy(char *tmp, int start, t_cy **tmp_cy);

#endif