/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:21:30 by julmuntz          #+#    #+#             */
/*   Updated: 2023/05/10 16:21:56 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_len(t_line *line, enum s_info info)
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
		return (ft_putstr_fd(ERROR_SYNTAX, 0), FAIL);
	return (SUCCESS);
}

t_object	*get_check(enum s_info type, t_line *line, t_object *value,
		t_value **tmps)
{
	bool	found;

	found = false;
	if (type == SP || type == PL || type == CY)
		found = true;
	if (type == SP)
		value = check_sp(line->line, 1);
	else if (type == PL)
		value = check_pl(line->line, 1);
	else if (type == CY)
		value = check_cy(line->line, 1);
	if (!value && !found)
		ft_free_object((*tmps)->object);
	return (value);
}

int	process_line(t_line *line, t_object **object, t_value **tmps)
{
	if (line->info == SP || line->info == PL || line->info == CY)
	{
		*object = get_check(line->info, line, *object, tmps);
		if (!*object)
			return (ft_free_object((*tmps)->object), FAIL);
	}
	return (SUCCESS);
}
