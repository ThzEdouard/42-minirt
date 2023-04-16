/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:26:01 by eflaquet          #+#    #+#             */
/*   Updated: 2023/04/16 13:55:43 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

void	ft_free_object(t_object *value)
{
	t_object *tmp;

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
	// ft_free_object(value->object);
	// free(value);
	if (!init_window(&mlx, &img, argv[1]))
		return (/*ne pas oublier de free*/FAIL);


	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			t_ray ray = init_ray(value->cam, x, y);
			t_impact	impact;
			ray_scene(&ray, value->object,&impact, value);
			my_mlx_pixel_put(&img, x, y, create_trgb(0, impact.rgb.r,impact.rgb.g,impact.rgb.b));
		}
	}
	mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, img.img, 0, 0);
	mlx_loop(mlx.mlx);
	ft_free_object(value->object);
	free(value);
	 clear_line(&file_line);
	return (SUCCESS);
}
