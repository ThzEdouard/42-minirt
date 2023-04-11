/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:20:16 by eflaquet          #+#    #+#             */
/*   Updated: 2023/04/11 16:50:45 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_pl	*new_elem_pl(char **vector, char **coord, char **rgb)
{
	t_pl	*new;

	new = malloc(sizeof(t_pl));
	if (!new)
		return (NULL);
	new->pf.x = ft_atof(coord[0]);
	new->pf.y = ft_atof(coord[1]);
	new->pf.z = ft_atof(coord[2]);
	new->vod.x = ft_atof(vector[0]);
	new->vod.y = ft_atof(vector[1]);
	new->vod.z = ft_atof(vector[2]);
	new->rgb.r = ft_atof(rgb[0]);
	new->rgb.g = ft_atof(rgb[1]);
	new->rgb.b = ft_atof(rgb[2]);
	return (new);
}

static int	init_sp(t_pl **tmp_pl, char **array_tmp)
{
	char	**rgb;
	char	**coord;
	char	**vector;

	coord = ft_split(array_tmp[1], ',');
	vector = ft_split(array_tmp[2], ',');
	rgb = ft_split(array_tmp[3], ',');
	if (!coord || !rgb || !vector)
		return (ft_free2(coord), ft_free2(rgb), ft_free2(vector), FAIL);
	if (!*tmp_pl)
	{
		*tmp_pl = new_elem_pl(vector, coord, rgb);
		if (!tmp_pl)
			return (ft_free2(coord), ft_free2(rgb), ft_free2(vector), FAIL);
	}
	else
	{
		while (*tmp_pl)
			*tmp_pl = (*tmp_pl)->next;
		if (!(*tmp_pl)->next)
		{
			(*tmp_pl)->next = new_elem_pl(vector, coord, rgb);
			if (!(*tmp_pl)->next)
				return (ft_free2(coord), ft_free2(rgb), ft_free2(vector), FAIL);
		}
	}
	return (ft_free2(coord), ft_free2(rgb), ft_free2(vector), SUCCESS);
}

int	check_pl(char *line, int start, t_pl **tmp_pl)
{
	char	**array_line;

	if (!line)
		return (FAIL);
	array_line = ft_split(line, 32);
	if (!array_line)
		return (FAIL);
	if (!check_value(array_line, &start) || start != 4)
		return (ft_free2(array_line), FAIL);
	if (!check_coord(array_line[1])
		|| !check_vector(array_line[2])
		|| !check_rgb(array_line[3]))
		return (ft_free2(array_line), FAIL);
	if (!init_sp(tmp_pl, array_line))
		return (ft_free2(array_line), FAIL);
	return (ft_free2(array_line), SUCCESS);
}
