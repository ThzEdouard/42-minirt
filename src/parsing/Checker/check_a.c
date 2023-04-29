/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_a.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:31:13 by eflaquet          #+#    #+#             */
/*   Updated: 2023/04/29 17:30:35 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	inti_la(t_la *tmp_la, char **array_tmp)
{
	char	**rgb;

	rgb = ft_split(array_tmp[2], ',');
	if (!rgb)
		return (FAIL);
	tmp_la->ratio = ft_atof(array_tmp[1]);
	tmp_la->rgb.r = ft_atoi(rgb[0]);
	tmp_la->rgb.g = ft_atoi(rgb[1]);
	tmp_la->rgb.b = ft_atoi(rgb[2]);
	return (ft_free2(rgb), SUCCESS);
}

int	check_a(char *line, int start, t_la *tmp_la)
{
	char	**array_line;

	if (!line)
		return (FAIL);
	array_line = ft_split(line, 32);
	if (!array_line)
		return (FAIL);
	if (!check_value(array_line, &start) || start != 3)
		return (ft_free2(array_line), FAIL);
	if (!check_line_range(array_line[1])
		|| !check_int_max_min(array_line[1])
		|| !check_range_double(0.0, 1.0, ft_atof(array_line[1]))
		|| !check_rgb(array_line[2]))
		return (ft_free2(array_line), FAIL);
	if (!inti_la(tmp_la, array_line))
		return (ft_free2(array_line), FAIL);
	return (ft_free2(array_line), SUCCESS);
}
