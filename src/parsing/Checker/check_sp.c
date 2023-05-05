/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:59:01 by eflaquet          #+#    #+#             */
/*   Updated: 2023/05/05 11:12:29 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_object	*new_elem_sp(char **array_tmp, char **coord, char **rgb)
{
	t_object	*new;

	new = malloc(sizeof(t_object));
	if (!new)
		return (NULL);
	new->center = new_vector(ft_atof(coord[0]),
			ft_atof(coord[1]), ft_atof(coord[2]));
	new->diameter = ft_atof(array_tmp[2]);
	new->rgb = new_rgb(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	new->info = SP;
	new->next = NULL;
	return (new);
}

static t_object *init_sp(char **array_tmp)
{
    char **rgb;
    char **coord;
    t_object *tmp;

    coord = ft_split(array_tmp[1], ',');
    rgb = ft_split(array_tmp[3], ',');
    if (!coord || !rgb)
    {
        if (coord) ft_free2(coord);
        if (rgb) ft_free2(rgb);
        return NULL;
    }
    tmp = new_elem_sp(array_tmp, coord, rgb);
    ft_free2(coord);
    ft_free2(rgb);
    return tmp;
}


t_object	*check_sp(char *line, int start)
{
	char		**array_line;
	t_object	*tmp;

	if (!line)
		return (FAIL);
	array_line = ft_split(line, 32);
	if (!array_line)
		return (FAIL);
	if (!check_value(array_line, &start) || start != 4)
		return (ft_free2(array_line), ft_putstr_fd(ERROR_SPHERE, 0), NULL);
	if (!check_coord(array_line[1])
		|| !check_int_max_min(array_line[2])
		|| !check_rgb(array_line[3]))
		return (ft_free2(array_line), ft_putstr_fd(ERROR_SPHERE, 0), NULL);
	tmp = init_sp(array_line);
	if (!tmp)
		return (ft_free2(array_line), ft_putstr_fd(ERROR_M_SPHERE, 0), tmp);
	return (ft_free2(array_line), tmp);
}
