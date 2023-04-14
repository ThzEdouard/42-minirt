/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:20:16 by eflaquet          #+#    #+#             */
/*   Updated: 2023/04/14 12:28:02 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_object	*new_elem_pl(char **vector, char **coord, char **rgb)
{
	t_object	*new;

	new = malloc(sizeof(t_object));
	if (!new)
		return (NULL);
	new->center = new_vector(ft_atof(coord[0]),
			ft_atof(coord[1]), ft_atof(coord[2]));
	new->axis = new_vector(ft_atof(vector[0]),
			ft_atof(vector[1]), ft_atof(vector[2]));
	new->rgb = new_rgb(ft_atof(rgb[0]), ft_atof(rgb[1]), ft_atof(rgb[2]));
	new->info = PL;
	new->next = NULL;
	return (new);
}

static void	recup_pl(char ***coord, char ***vector,
			char ***rgb, char **array_tmp)
{
	*coord = ft_split(array_tmp[1], ',');
	*vector = ft_split(array_tmp[2], ',');
	*rgb = ft_split(array_tmp[3], ',');
}

static int	init_sp(t_object **tmp_pl, char **array_tmp)
{
	char	**rgb;
	char	**coord;
	char	**vector;

	recup_pl(&coord, &vector, &rgb, array_tmp);
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
		if (!(*tmp_pl)->next)
		{
			(*tmp_pl)->next = new_elem_pl(vector, coord, rgb);
			if (!(*tmp_pl)->next)
				return (ft_free2(coord), ft_free2(rgb), ft_free2(vector), FAIL);
		}
	}
	return (ft_free2(coord), ft_free2(rgb), ft_free2(vector), SUCCESS);
}

int	check_pl(char *line, int start, t_object **tmp_pl)
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
