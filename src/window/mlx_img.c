/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_img.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:45:08 by eflaquet          #+#    #+#             */
/*   Updated: 2023/05/10 14:11:21 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	mlx_make_img(t_end *end, t_data *img)
{
	int			y;
	int			x;
	t_ray		ray;
	t_impact	impact;

	y = -1;
	while (++y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = init_ray(end->value->cam, x, y);
			end->f_color = new_rgb(0, 0, 0);
			if (ray_scene(&ray, end->value->object, &impact))
				end->f_color = color_pixel(end->value, &impact);
			my_mlx_pixel_put(img, x, y,
				create_trgb(0, end->f_color.r, end->f_color.g, end->f_color.b));
			x++;
		}
	}
	mlx_hook(end->mlx.mlx_win, KeyPress, KeyPressMask, &key_end, end);
	mlx_hook(end->mlx.mlx_win, ClientMessage, 0, &click_end, end);
	mlx_put_image_to_window(end->mlx.mlx, end->mlx.mlx_win,
		end->data.img, 0, 0);
	mlx_loop(end->mlx.mlx);
}
