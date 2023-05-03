/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 10:34:05 by eflaquet          #+#    #+#             */
/*   Updated: 2023/05/03 16:34:03 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include "struct.h"
# define CHAR_INT_MAX "2147483647"
# define CHAR_INT_MIN "-2147483648"


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

#endif