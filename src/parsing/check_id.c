/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_id.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:11:56 by eflaquet          #+#    #+#             */
/*   Updated: 2023/05/08 19:21:04 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_id_min2(t_line *line, t_value **tmps)
{
	t_object	*value;

	value = (*tmps)->object;
	while (line)
	{
		if (!process_line(line, &value->next, tmps))
			return (FAIL);
		if (value->next)
			value = value->next;
		line = line->next;
	}
	return (SUCCESS);
}

int	check_id_min(t_line *line, t_value **tmps)
{
	while (line)
	{
		if (!process_line(line, &((*tmps)->object), tmps))
			return (ft_free_object(((*tmps)->object)), FAIL);
		line = line->next;
		if ((*tmps)->object)
			break ;
	}
	if (check_id_min2(line, tmps) == FAIL)
		return (ft_free_object(((*tmps)->object)), FAIL);
	return (SUCCESS);
}

int	check_id_maj(t_line *line, t_value **tmp)
{
	t_value	*value;

	value = malloc(sizeof(t_value));
	if (!value)
		return (FAIL);
	if (!check_len(line, A) || !check_len(line, C) || !check_len(line, L))
		return (free(value), FAIL);
	while (line)
	{
		if (line->info == A)
			if (!check_a(line->line, 1, &value->lum_am))
				return (free(value), FAIL);
		if (line->info == C)
			if (!check_c(line->line, 1, &value->cam))
				return (free(value), FAIL);
		if (line->info == L)
			if (!check_l(line->line, 1, &value->lum))
				return (free(value), FAIL);
		line = line->next;
	}
	*tmp = value;
	return (SUCCESS);
}
