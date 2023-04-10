/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:26:01 by eflaquet          #+#    #+#             */
/*   Updated: 2023/04/06 16:52:21 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_line	*file_line;
	t_value	*value;

	if (argc > 2)
		exit(FAIL);
	file_line = check_name_norm(argv[1], &value);
	if (!file_line)
		return (FAIL);
	printf("sp     %f,%f,%f     %f     %d,%d,%d\n", value->sphere->ps.x, value->sphere->ps.y, value->sphere->ps.z, value->sphere->dia, value->sphere->rgb.r, value->sphere->rgb.g, value->sphere->rgb.b);
	printf("pl     %f,%f,%f     %f,%f,%f     %d,%d,%d\n", value->plan->pf.x, value->plan->pf.y, value->plan->pf.z, value->plan->vod.x, value->plan->vod.y, value->plan->vod.z, value->plan->rgb.r, value->plan->rgb.g, value->plan->rgb.b);
	printf("cy   %f,%f,%f    %f,%f,%f    %f    %f   %d,%d,%d\n", value->cylindre->pf.x, value->cylindre->pf.y, value->cylindre->pf.z, value->cylindre->vod.x,value->cylindre->vod.y,value->cylindre->vod.z,value->cylindre->dia_cy, value->cylindre->h_cy,value->cylindre->rgb.r,value->cylindre->rgb.g,value->cylindre->rgb.b);
	free(value->cylindre);
	free(value->plan);
	free(value->sphere);
	free(value);
	clear_line(&file_line);
    void	*mlx;
    void	*mlx_win;
	(void)mlx_win;
    mlx = mlx_init();
    if (!mlx)
	    return (printf("fail"), FAIL);
    mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
    mlx_loop(mlx);
	return (SUCCESS);
}
