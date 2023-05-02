/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:09:35 by eflaquet          #+#    #+#             */
/*   Updated: 2023/05/02 10:04:45 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_object	*new_elem_cy(char **vector, char **coord,
						char **rgb, char **array_tmp)
{
	t_object	*new;

	new = malloc(sizeof(t_object));
	if (!new)
		return (NULL);
	new->center = new_vector(-ft_atof(coord[0]),
			ft_atof(coord[1]), ft_atof(coord[2]));
	new->axis = new_vector(ft_atof(vector[0]),
			ft_atof(vector[1]), ft_atof(vector[2]));
	new->axis = normalize(new->axis);
	new->diameter = ft_atof(array_tmp[3]);
	new->height = ft_atof(array_tmp[4]);
	new->rgb = new_rgb(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	new->info = CY;
	new->next = NULL;
	return (new);
}

static void	recup_cy(char ***coord, char ***vector,
			char ***rgb, char **array_tmp)
{
	*coord = ft_split(array_tmp[1], ',');
	*vector = ft_split(array_tmp[2], ',');
	*rgb = ft_split(array_tmp[5], ',');
}

static t_object	*init_cy(char **array_tmp)
{
	char		**rgb;
	char		**coord;
	char		**vector;
	t_object	*tmp;

	recup_cy(&coord, &vector, &rgb, array_tmp);
	if (!coord || !rgb || !vector)
		return (ft_free2(coord), ft_free2(rgb), ft_free2(vector), NULL);
	tmp = new_elem_cy(vector, coord, rgb, array_tmp);
	return (ft_free2(coord), ft_free2(rgb), ft_free2(vector), tmp);
}

t_object	*check_cy(char *line, int start)
{
	char		**array_line;
	t_object	*tmp;

	if (!line)
		return (FAIL);
	array_line = ft_split(line, 32);
	if (!array_line)
		return (FAIL);
	if (!check_value(array_line, &start) || start != 6)
		return (ft_free2(array_line), NULL);
	if (!check_coord(array_line[1])
		|| !check_vector(array_line[2])
		|| !check_int_max_min(array_line[3])
		|| !check_int_max_min(array_line[4])
		|| !check_rgb(array_line[5]))
		return (ft_free2(array_line), NULL);
	tmp = init_cy(array_line);
	return (ft_free2(array_line), tmp);
}
