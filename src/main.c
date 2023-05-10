/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:26:01 by eflaquet          #+#    #+#             */
/*   Updated: 2023/05/10 16:26:54 by eflaquet         ###   ########.fr       */
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
		return (ft_free_object(end.value->object), free(end.value)
			, ft_putstr_fd(ERROR_MLX, 0), FAIL);
	mlx_make_img(&end, &(end.data));
	return (SUCCESS);
}
