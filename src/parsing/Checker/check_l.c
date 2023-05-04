/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_l.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:07:18 by eflaquet          #+#    #+#             */
/*   Updated: 2023/05/04 14:52:51 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	init_lum(t_l *tmp_lum, char **array_tmp)
{
	char	**coord;

	coord = ft_split(array_tmp[1], ',');
	if (!coord)
		return (ft_free2(coord), FAIL);
	tmp_lum->pl.x = ft_atof(coord[0]);
	tmp_lum->pl.y = ft_atof(coord[1]);
	tmp_lum->pl.z = ft_atof(coord[2]);
	tmp_lum->ratio = ft_atof(array_tmp[2]);
	return (ft_free2(coord), SUCCESS);
}

int	check_l(char *line, int start, t_l *tmp_lum)
{
	char	**array_line;

	if (!line)
		return (FAIL);
	array_line = ft_split(line, 32);
	if (!array_line)
		return (FAIL);
	if (!check_value(array_line, &start) || start != 3)
		return (ft_free2(array_line), ft_putstr_fd(ERROR_LIGHT, 0), FAIL);
	if (!check_coord(array_line[1])
		|| !check_int_max_min(array_line[2])
		|| !check_range_double(0.0, 1.0, ft_atof(array_line[2])))
		return (ft_free2(array_line), ft_putstr_fd(ERROR_LIGHT, 0), FAIL);
	if (!init_lum(tmp_lum, array_line))
		return (ft_free2(array_line), ft_putstr_fd(ERROR_M_LIGHT, 0), FAIL);
	return (ft_free2(array_line), SUCCESS);
}
