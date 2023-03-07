/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:06:33 by eflaquet          #+#    #+#             */
/*   Updated: 2023/03/07 16:57:19 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_strchr(char *line)
{
	while (*line && *line != 10)
	{
		if (*line && !ft_isalnum(*line)
			&& (*line != 46 && *line != 45 && *line != 44 && *line != 32))
			return (ft_putstr_fd("\e[0;91mError\nvalue add not \e[0m", 0), FAIL);
		line++;
	}
	return (SUCCESS);
}

static t_info	add_info(char *id)
{
	if (!ft_strcmp(id, "A"))
		return (A);
	if (!ft_strcmp(id, "C"))
		return (C);
	if (!ft_strcmp(id, "L"))
		return (L);
	if (!ft_strcmp(id, "sp"))
		return (SP);
	if (!ft_strcmp(id, "pl"))
		return (PL);
	if (!ft_strcmp(id, "cy"))
		return (CY);
	return (NOT);
}

static int	check_id(t_line *line, int i, int x)
{
	char	*id;
	t_line	*tmp;

	tmp = line;
	while (tmp)
	{
		i = 0;
		id = NULL;
		while (tmp->line[i] && !ft_isalpha(tmp->line[i]))
			i++;
		x = i;
		while (tmp->line[x] && ft_isalpha(tmp->line[x]))
			x++;
		if (ft_isalpha(tmp->line[i]))
			id = ft_substr(tmp->line, i, x);
		if (id)
		{
			tmp->info = add_info(id);
			free(id);
			if (tmp->info == NOT)
				return (ft_putstr_fd("NOT", 0), FAIL);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

static int	check_nub_id(t_line *line)
{
	t_line	*tmp;


	return (SUCCESS);
}

int	norm_file(t_line *line)
{
	t_line	*tmp;

	tmp = line;
	while (tmp)
	{
		if (!check_strchr(tmp->line))
			return (clear_line(&line), FAIL);
		tmp = tmp->next;
	}
	if (!check_id(line, 0, 0))
		return (clear_line(&line), FAIL);
	if (!check_nub_id(line))
		return (clear_line(&line), FAIL);
	return (SUCCESS);
}
