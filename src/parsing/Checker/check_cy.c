/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:09:35 by eflaquet          #+#    #+#             */
/*   Updated: 2023/04/06 17:27:46 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_cy	*new_elem_pl(char **vector, char **coord, char **rgb, char **array_tmp)
{
	t_cy	*new;

	new = malloc(sizeof(t_cy));
	if (!new)
		return (NULL);
	return (new);
}

static t_cy	*init_cy(t_cy **tmp_cy, char **array_tmp)
{
	char	**rgb;
	char	**coord;
	char	**vector;

	coord = ft_split(array_tmp[1], ',');
	vector = ft_split(array_tmp[2], ',');
	rgb = ft_split(array_tmp[3], ',');
	if (!coord || !rgb || !vector)
		return (ft_free2(coord), ft_free2(rgb), ft_free2(vector), FAIL);
	if (!*tmp_cy)
	{
		*tmp_cy = new_elem_pl(vector, coord, rgb);
		if (!tmp_cy)
			return (ft_free2(coord), ft_free2(rgb), ft_free2(vector), FAIL);
	}
	else
	{
		while (*tmp_cy)
			*tmp_cy = (*tmp_cy)->next;
		if (!(*tmp_cy)->next)
		{
			(*tmp_cy)->next = new_elem_pl(vector, coord, rgb);
			if (!(*tmp_cy)->next)
				return (ft_free2(coord), ft_free2(rgb), ft_free2(vector), FAIL);
		}
	}
	return (ft_free2(coord), ft_free2(rgb), ft_free2(vector), SUCCESS);
}


int	check_cy(char *line, int start, t_cy **tmp_cy)
{
	char	**array_line;

	if (!line)
		return (FAIL);
	array_line = ft_split(line, 32);
	if (!array_line)
		return (FAIL);
	if (!check_value(array_line, &start) || start != 6)
		return (ft_free2(array_line), FAIL);
	if (!check_coord(array_line[1])
		|| !check_vector(array_line[2])
		|| !check_int_max_min(array_line[3])
		|| !check_int_max_min(array_line[4])
		|| !check_rgb(array_line[5]))
		return (ft_free2(array_line), FAIL);
	if (!init_cy(tmp_cy, array_line))
		return (ft_free2(array_line), FAIL);
	return (ft_free2(array_line), SUCCESS);
}