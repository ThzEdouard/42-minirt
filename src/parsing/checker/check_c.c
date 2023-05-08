/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 12:38:12 by eflaquet          #+#    #+#             */
/*   Updated: 2023/05/08 18:53:14 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	init_ca(t_ca *tmp_cam, char **array_tmp)
{
	char	**coord;
	char	**vector;

	coord = ft_split(array_tmp[1], ',');
	vector = ft_split(array_tmp[2], ',');
	if (!coord || !vector)
	{
		if (coord)
			ft_free2(coord);
		if (vector)
			ft_free2(vector);
		return (FAIL);
	}
	tmp_cam->pv = new_vector(ft_atof(coord[0]), ft_atof(coord[1]),
			ft_atof(coord[2]));
	tmp_cam->axe = new_vector(ft_atof(vector[0]), ft_atof(vector[1]),
			ft_atof(vector[2]));
	tmp_cam->fov = ft_atoi(array_tmp[3]);
	ft_free2(coord);
	ft_free2(vector);
	return (SUCCESS);
}

int	check_c(char *line, int start, t_ca *tmp_cam)
{
	char	**array_line;

	if (!line)
		return (FAIL);
	array_line = ft_split(line, 32);
	if (!array_line)
		return (FAIL);
	if (!check_value(array_line, &start) || start != 4)
		return (ft_free2(array_line), ft_putstr_fd(ERROR_CAM, 0), FAIL);
	if (!check_coord(array_line[1]) || !check_vector(array_line[2])
		|| !check_int_max_min(array_line[3]) || !check_range_int(0, 180,
			ft_atoi(array_line[3])))
		return (ft_free2(array_line), ft_putstr_fd(ERROR_CAM, 0), FAIL);
	if (!init_ca(tmp_cam, array_line))
		return (ft_free2(array_line), ft_putstr_fd(ERROR_M_CAM, 0), FAIL);
	return (ft_free2(array_line), SUCCESS);
}
