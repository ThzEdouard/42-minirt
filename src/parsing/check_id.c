/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_id.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:11:56 by eflaquet          #+#    #+#             */
/*   Updated: 2023/04/14 16:58:12 by julmuntz         ###   ########.fr       */
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

static t_object	*get_check(enum s_info type, t_line *line, t_object *value,
t_value **tmps)
{
	if (type == SP)
	{
		value = check_sp(line->line, 1);
		if (!value)
			ft_free_object((*tmps)->object);
	}
	if (type == PL)
	{
		value = check_pl(line->line, 1);
		if (!value)
			ft_free_object((*tmps)->object);
	}
	if (type == CY)
	{
		value = check_cy(line->line, 1);
		if (!value)
			ft_free_object((*tmps)->object);
	}
	return (value);
}

static int	check_id_min2(t_line *line, t_value **tmps)
{
	t_object	*value;

	while (line)
	{
		if (line && line->info == SP)
			value->next = get_check(SP, line, value->next, tmps);
		if (line && line->info == PL)
			value->next = get_check(PL, line, value->next, tmps);
		if (line && line->info == CY)
			value->next = get_check(CY, line, value->next, tmps);
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
		if (line && line->info == SP)
			(*tmps)->object = get_check(SP, line, (*tmps)->object, tmps);
		if (line && line->info == PL)
			(*tmps)->object = get_check(PL, line, (*tmps)->object, tmps);
		if (line && line->info == CY)
			(*tmps)->object = get_check(CY, line, (*tmps)->object, tmps);
		line = line->next;
		if ((*tmps)->object)
			break ;
	}
	if (check_id_min2(line, tmps) == FAIL)
		return (FAIL);
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
