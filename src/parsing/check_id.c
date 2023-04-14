/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_id.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:11:56 by eflaquet          #+#    #+#             */
/*   Updated: 2023/04/14 09:33:20 by eflaquet         ###   ########.fr       */
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

int	check_id_min(t_line *line, t_value **tmp)
{
	t_value	*value;

	value = *tmp;
	while (line)
	{
		if (line && line->info == SP && !check_sp(line->line, 1,
				&value->object))
			return (ft_free_object(value->object), FAIL);
		if (line && line->info == PL && !check_pl(line->line, 1,
				&value->object))
			return (ft_free_object(value->object), FAIL);
		if (line && line->info == CY && !check_cy(line->line, 1,
				&value->object))
			return (ft_free_object(value->object), FAIL);
		line = line->next;
	}
	*tmp = value;
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
