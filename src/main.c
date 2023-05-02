/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:26:01 by eflaquet          #+#    #+#             */
/*   Updated: 2023/05/02 15:56:57 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

void	ft_free_object(t_object *value)
{
	t_object	*tmp;

	while (value)
	{
		tmp = value;
		value = value->next;
		free(tmp);
	}
}

int	key_end(int key, t_end *end)
{
	if (key == XK_Escape)
	{
		ft_free_mlx(&(end->mlx), &(end->data));
		ft_free_object(end->value->object);
		free(end->value);
		exit(0);
	}
	return (0);
}

int	click_end(t_end *end)
{
	ft_free_mlx(&(end->mlx), &(end->data));
	ft_free_object(end->value->object);
	free(end->value);
	exit(0);
	return (0);
}

bool is_shadowing(t_value *v, t_impact *impact)
{
	t_ray ray;

	ray.origin = impact->p_inter;
	t_vector light_direction = subtract_vector(v->lum.pl, ray.origin);
	double light_distance = magnitude(light_direction);
	ray.direction = vector_division(light_direction, light_distance);
	t_object *tmp = v->object;
	double	distance = INFINITY;
	while (tmp)
	{
		distance = INFINITY;
		if (tmp->info == SP && intersection_sphere(&ray, tmp, &distance) && distance < light_distance)
			return (true);
		if (tmp->info == PL && intersection_plan(tmp, &ray, &distance) && distance < light_distance)
			return (true);
		if (tmp->info == CY && intersection_cylindre(&ray, tmp, &distance) && distance < light_distance)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

void	make_img(t_end *end, t_data *img, t_value *value)
{
	int			y;
	int			x;
	t_ray		ray;
	t_impact	impact;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = init_ray(value->cam, x, y);
			ray_scene(&ray, value->object, &impact, NULL, value);
			if (impact.info != NOT)
			{
				impact.rgb = get_color(value, &impact);
				
			}
			my_mlx_pixel_put(img, x, y,
				create_trgb(0, impact.rgb.r, impact.rgb.g, impact.rgb.b));
			x++;
		}
		y++;
	}
	mlx_hook(end->mlx.mlx_win, KeyPress, KeyPressMask, &key_end, end);
	mlx_hook(end->mlx.mlx_win, ClientMessage, 0, &click_end, end);
	mlx_put_image_to_window(end->mlx.mlx, end->mlx.mlx_win,
		end->data.img, 0, 0);
	mlx_loop(end->mlx.mlx);
}

int	main(int argc, char **argv)
{
	t_line	*file_line;
	t_end	end;

	end.value = NULL;
	if (argc > 2)
		exit(FAIL);
	file_line = check_name_norm(argv[1], &(end.value));
	if (!file_line)
		return (FAIL);
	clear_line(&file_line);
	if (!init_window(&(end.mlx), &(end.data), argv[1]))
		return (ft_free_object(end.value->object), free(end.value), FAIL);
	make_img(&end, &(end.data), end.value);
	return (SUCCESS);
}
