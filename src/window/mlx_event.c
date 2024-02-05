/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:29:48 by eflaquet          #+#    #+#             */
/*   Updated: 2023/05/03 15:30:19 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
