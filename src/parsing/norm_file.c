/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:06:33 by eflaquet          #+#    #+#             */
/*   Updated: 2023/01/09 18:40:23 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_range(char *str, char *min, char *max)
{
	
	return (SUCCESS);
}

static int	check_strchr(char *line)
{
	while (line)
	{
		if (!ft_isalnum(*line) && *line != 46 && *line != 44)
			return (FAIL);
	}
	return (SUCCESS);
}

int	norm_file(t_line *line)
{
	t_line	*tmp;

	tmp = line;
	while (tmp)
	{
		if (!check_strchr(tmp->line))
			return (FAIL);
		tmp = tmp->next;
	}
	return (0);
}
