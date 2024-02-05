/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 09:10:45 by eflaquet          #+#    #+#             */
/*   Updated: 2023/05/03 14:44:40 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	init_window(t_mlx *tmp_mlx, t_data *tmp_img, char *name)
{
	tmp_mlx->mlx = mlx_init();
	if (!tmp_mlx->mlx)
		return (FAIL);
	tmp_mlx->mlx_win = mlx_new_window(tmp_mlx->mlx, WIDTH, HEIGHT, name);
	if (!tmp_mlx->mlx_win)
		return (mlx_destroy_display(tmp_mlx->mlx), free(tmp_mlx->mlx), FAIL);
	tmp_img->img = mlx_new_image(tmp_mlx->mlx, WIDTH, HEIGHT);
	if (!tmp_img->img)
		return (mlx_destroy_window(tmp_mlx->mlx, tmp_mlx->mlx_win),
			mlx_destroy_display(tmp_mlx->mlx), free(tmp_mlx->mlx), FAIL);
	tmp_img->addr = mlx_get_data_addr(tmp_img->img,
			&tmp_img->bits_per_pixel, &tmp_img->line_length,
			&tmp_img->endian);
	if (!tmp_img->addr)
		return (mlx_destroy_image(tmp_mlx->mlx, tmp_img->img),
			mlx_destroy_window(tmp_mlx->mlx, tmp_mlx->mlx_win),
			mlx_destroy_display(tmp_mlx->mlx), free(tmp_mlx->mlx), FAIL);
	return (SUCCESS);
}

void	ft_free_mlx(t_mlx *tmp_mlx, t_data *tmp_img)
{
	mlx_destroy_image(tmp_mlx->mlx, tmp_img->img);
	mlx_destroy_window(tmp_mlx->mlx, tmp_mlx->mlx_win);
	mlx_destroy_display(tmp_mlx->mlx);
	free(tmp_mlx->mlx);
}
