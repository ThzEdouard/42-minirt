/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:26:01 by eflaquet          #+#    #+#             */
/*   Updated: 2023/04/13 10:45:43 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

// t_coord	t_coord_moin(t_coord a, t_coord b)
// {
// 	t_coord	result;

// 	result.x = a.x - b.x;
// 	result.y = a.y - b.y;
// 	result.z = a.z - b.z;
// 	return (result);
// }

void	ft_free_sphere(t_sp *value)
{
	t_sp *tmp;

	while (value)
	{
		tmp = value;
		value = value->next;
		free(tmp);
	}
}
void	ft_free_plane(t_pl *value)
{
	t_pl *tmp;

	while (value)
	{
		tmp = value;
		value = value->next;
		free(tmp);
	}
}
void	ft_free_cy(t_cy *value)
{
	t_cy *tmp;

	while (value)
	{
		tmp = value;
		value = value->next;
		free(tmp);
	}
}
int	main(int argc, char **argv)
{
	t_line	*file_line;
	t_value	*value = NULL;
	t_mlx	mlx;
	t_data	img;

	if (argc > 2)
		exit(FAIL);
	file_line = check_name_norm(argv[1], &value);
	if (!file_line)
		return (FAIL);
	printf("A     %f      %d,%d,%d\n", value->lum_am.ratio, value->lum_am.rgb.r, value->lum_am.rgb.g, value->lum_am.rgb.b);
	printf("C     %f,%f,%f     %f,%f,%f     %d\n", value->cam.pv.x, value->cam.pv.y, value->cam.pv.z, value->cam.axe.x, value->cam.axe.y, value->cam.axe.z, value->cam.fov);
	printf("L     %f,%f,%f     %f     %d,%d,%d\n", value->lum.pl.x, value->lum.pl.y, value->lum.pl.z, value->lum.ratio, value->lum.rgb.r, value->lum.rgb.g, value->lum.rgb.b);
	printf("sp     %f,%f,%f     %f     %d,%d,%d\n", value->sphere->ps.x, value->sphere->ps.y, value->sphere->ps.z, value->sphere->dia, value->sphere->rgb.r, value->sphere->rgb.g, value->sphere->rgb.b);
	printf("pl     %f,%f,%f     %f,%f,%f     %d,%d,%d\n", value->plan->pf.x, value->plan->pf.y, value->plan->pf.z, value->plan->vod.x, value->plan->vod.y, value->plan->vod.z, value->plan->rgb.r, value->plan->rgb.g, value->plan->rgb.b);
	printf("cy   %f,%f,%f    %f,%f,%f    %f    %f   %d,%d,%d\n", value->cylindre->pf.x, value->cylindre->pf.y, value->cylindre->pf.z, value->cylindre->vod.x,value->cylindre->vod.y,value->cylindre->vod.z,value->cylindre->dia_cy, value->cylindre->h_cy,value->cylindre->rgb.r,value->cylindre->rgb.g,value->cylindre->rgb.b);

	if (!init_window(&mlx, &img, argv[1]))
		return (/*ne pas oublier de free*/FAIL);
	for (int x = 0; x < HEIGHT; x++)
	{
		for (int y = 0; y < WIDTH; y++)
		{
			t_ray ray = init_ray(value->cam.pv, value->cam, x, y);
	double t1 = INFINITY,t2 =  INFINITY;
			intersection_sphere(&ray, value->sphere, &t1);
			intersection_cylindre(&ray, value->cylindre, &t2);
			if (intersection_cylindre(&ray, value->cylindre, &t2))
				my_mlx_pixel_put(&img, x, y, create_trgb(0, 0,255,0));
			else if (intersection_sphere(&ray, value->sphere, &t1))
			 	my_mlx_pixel_put(&img, x, y, create_trgb(0, 255,255,255));
			else if (intersection_plan(value->plan, &ray, &t2))
				my_mlx_pixel_put(&img, x, y, create_trgb(0, 0,0,255));
		}
	}

	mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, img.img, 0, 0);
	mlx_loop(mlx.mlx);
	free(value->cylindre);
	free(value->plan);
	free(value->sphere);
	free(value);
	clear_line(&file_line);
	return (SUCCESS);
}
