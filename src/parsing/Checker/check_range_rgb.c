/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_range_rgb.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 10:33:32 by eflaquet          #+#    #+#             */
/*   Updated: 2023/05/05 13:05:33 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_line_rgb(char *line)
{
	int	y;

	y = 0;
	while (*line)
	{
		if (!ft_isdigit(*line) && *line == 46)
			return (FAIL);
		if (*line == 44)
			y++;
		if (*line == 44 && *(line + 1) && !ft_isdigit(*(line + 1)))
			return (FAIL);
		line++;
	}
	if (y > 2)
		return (FAIL);
	return (SUCCESS);
}

int	check_int_max_min(char *line)
{
	if (*line == '-')
	{
		if (ft_strlen(line) > ft_strlen(CHAR_INT_MIN)
			|| ft_atoi(line) < ft_atoi(CHAR_INT_MIN))
			return (FAIL);
	}
	else
	{
		if (ft_strlen(line) > ft_strlen(CHAR_INT_MAX)
			|| ft_atoi(line) > ft_atoi(CHAR_INT_MAX))
			return (FAIL);
	}
	return (SUCCESS);
}

int	check_range_double(double min, double max, double nb)
{
	if (nb < min || nb > max)
		return (FAIL);
	return (SUCCESS);
}

int	check_range_int(int min, int max, int nb)
{
	if (nb < min || nb > max)
		return (FAIL);
	return (SUCCESS);
}

int	check_rgb(char *line)
{
	char	**tmp;
	int		i;

	if (!check_line_rgb(line))
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
			|| !check_range_int(0, 255, ft_atoi(tmp[i])))
			return (ft_free2(tmp), FAIL);
		i++;
	}
	return (ft_free2(tmp), SUCCESS);
}