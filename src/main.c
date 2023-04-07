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
    unsigned char img[WIDTH * HEIGHT * 3];

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
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int y = 0; y < WIDTH; y++)
        {
            img[(i*WIDTH+y) * 3 + 0] = 255;
            img[(i*WIDTH+y) * 3 + 1] = 0;
            img[(i*WIDTH+y) * 3 + 2] = 0;
        }
    }
    save_bmp("ll.bmp",&img[0], 1024,1024);
	return (SUCCESS);
}
