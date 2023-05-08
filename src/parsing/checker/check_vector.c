/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_vector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:34:17 by eflaquet          #+#    #+#             */
/*   Updated: 2023/05/08 18:56:08 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

static int	check_line_vector(char *line)
{
	int	y;

	y = 0;
	while (*line)
	{
		if (*line == 44)
			y++;
		if (*line == 44 && *(line + 1) && !ft_isdigit(*(line + 1))
			&& *(line + 1) != '-' )
			return (FAIL);
		line++;
	}
	if (y > 3)
		return (FAIL);
	return (SUCCESS);
}

int	check_vector(char *line)
{
	char	**tmp;
	int		i;

	if (!check_line_vector(line))
		return (FAIL);
	tmp = ft_split(line, 44);
	if (!tmp)
		return (FAIL);
	i = 0;
	while (tmp[i])
		i++;
	if (i != 3)
		return (ft_free2(tmp), FAIL);
	i = 0;
	while (tmp[i])
	{
		if (!check_int_max_min(tmp[i])
			|| !check_line_range(tmp[i])
			|| !check_int_max_min(tmp[i])
			|| !check_range_double(-1, 1, ft_atof(tmp[i])))
			return (ft_free2(tmp), FAIL);
		i++;
	}
	return (ft_free2(tmp), SUCCESS);
}
