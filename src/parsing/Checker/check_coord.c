/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_coord.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:57:55 by eflaquet          #+#    #+#             */
/*   Updated: 2023/05/05 09:32:47 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_line_range(char *line)
{
	int	y;

	y = 0;
	while (*line)
	{
		if (!ft_isdigit(*line) && *line != ',')
			return (FAIL);
		if (*line == '.')
			y++;
		line++;
	}
	if (y > 1)
		return (FAIL);
	return (SUCCESS);
}

static int	check_line_coord(char *line)
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

int	check_coord(char *line)
{
	char	**tmp;
	int		i;

	if (!check_line_coord(line))
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
			|| !check_line_range(tmp[i]))
			return (ft_free2(tmp), FAIL);
		i++;
	}
	return (ft_free2(tmp), SUCCESS);
}
