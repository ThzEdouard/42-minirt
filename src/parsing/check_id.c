/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_id.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:11:56 by eflaquet          #+#    #+#             */
/*   Updated: 2023/04/14 14:42:34 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_len(t_line *line, enum s_info info)
{
	int		nb;
	t_line	*tmp;

	tmp = line;
	nb = 0;
	while (tmp)
	{
		if (tmp->info == info)
			nb++;
		tmp = tmp->next;
	}
	if (nb != 1)
		return (FAIL);
	return (SUCCESS);
}

int	check_id_min(t_line *line, t_value **tmps)
{
	t_object	*value;

	while (line)
	{
		if (line && line->info == SP)
		{
			(*tmps)->object = check_sp(line->line, 1);
			if (!(*tmps)->object)
				return (ft_free_object((*tmps)->object), FAIL);
		}
		if (line && line->info == PL)
		{
			(*tmps)->object = check_pl(line->line, 1);
			if (!(*tmps)->object)
				return (ft_free_object((*tmps)->object), FAIL);
		}
		if (line && line->info == CY)
		{
			(*tmps)->object = check_cy(line->line, 1);
			if (!(*tmps)->object)
				return (ft_free_object((*tmps)->object), FAIL);
		}
		line = line->next;
		if ((*tmps)->object)
			break ;

	}
	value = (*tmps)->object;
	while (line)
	{
		if (line && line->info == SP)
		{
			value->next = check_sp(line->line, 1);
			if (!value->next)
				return (ft_free_object((*tmps)->object), FAIL);
		}
		if (line && line->info == PL)
		{
			value->next = check_pl(line->line, 1);
			if (!value->next)
				return (ft_free_object((*tmps)->object), FAIL);
		}
		if (line && line->info == CY)
		{
			value->next = check_cy(line->line, 1);
			if (!value->next)
				return (ft_free_object((*tmps)->object), FAIL);
		}
		if (value->next)
			value = value->next;
		line = line->next;
	}
	//(*tmp)->object = value;
	return (SUCCESS);
}

int	check_id_maj(t_line *line, t_value **tmp)
{
	t_value	*value;

	value = malloc(sizeof(t_value));
	if (!value)
		return (FAIL);
	if (!check_len(line, A) || !check_len(line, C) || !check_len(line, L))
		return (FAIL);
	while (line)
	{
		if (line && line->info == A && !check_a(line->line, 1, &value->lum_am))
			return (printf("FAIL"), free(value), FAIL);
		if (line && line->info == C && !check_c(line->line, 1, &value->cam))
			return (printf("FAIL"), free(value), FAIL);
		if (line && line->info == L && !check_l(line->line, 1, &value->lum))
			return (printf("FAIL"), free(value), FAIL);
		line = line->next;
	}
	*tmp = value;
	return (SUCCESS);
}
