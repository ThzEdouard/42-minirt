/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_a.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:31:13 by eflaquet          #+#    #+#             */
/*   Updated: 2023/04/05 14:41:11 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*return_line(t_line *tmp, enum s_info info)
{
	char	*line;

	while (tmp)
	{
		if (tmp->info == info)
			line = tmp->line;
		tmp = tmp->next;
	}
	return (line);
}

int	check_value(char **array_tmp, int *starts)
{
	int	x;
	int	start;

	start = *starts;
	while (array_tmp[start])
	{
		x = 0;
		while (array_tmp[start][x])
		{
			if (!ft_isdigit(array_tmp[start][x])
				&& (array_tmp[start][x] != 45
				&& array_tmp[start][x] != 44
				&& array_tmp[start][x] != 46))
				return (FAIL);
			x++;
		}
		start++;
	}
	*starts = start;
	return (SUCCESS);
}

int	check_line_range(char *line)
{
	int	y;

	y = 0;
	while (*line)
	{
		if (!ft_isdigit(*line) && *line == ',')
			return (FAIL);
		if (*line == '.')
			y++;
		line++;
	}
	if (y > 1)
		return (FAIL);
	return (SUCCESS);
}

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

int	check_a(t_line *tmp, int start, t_la *tmp_la)
{
	char	**array_line;
	char	*line;

	line = return_line(tmp, A);
	if (!line)
		return (FAIL);
	array_line = ft_split(line, 32);
	if (!array_line)
		return (FAIL);
	if (!check_value(array_line, &start) || start != 3)
		return (ft_free2(array_line), FAIL);
	if (!check_line_range(array_line[1])
		|| !check_int_max_min(array_line[1])
		|| !check_range_float(0.0, 1.0, ft_atof(array_line[1]))
		|| !check_rgb(array_line[2]))
		return (ft_free2(array_line), FAIL);
	if (!inti_la(tmp_la, array_line))
		return (ft_free2(array_line), FAIL);
	return (ft_free2(array_line), SUCCESS);
}
