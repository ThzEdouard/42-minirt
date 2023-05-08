/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:06:33 by eflaquet          #+#    #+#             */
/*   Updated: 2023/05/08 19:18:23 by julmuntz         ###   ########.fr       */
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

static char	*get_id(char *line)
{
	int		i;
	int		x;
	int		save_i;
	char	*id;

	id = NULL;
	i = 0;
	while (line[i] && !ft_isalpha(line[i]))
		i++;
	x = 0;
	save_i = i;
	while (line[i] && ft_isalpha(line[i++]))
		x++;
	if (ft_isalpha(line[save_i]))
		id = ft_substr(line, save_i, x);
	return (id);
}

static int	check_id(t_line *line)
{
	char	*id;

	while (line)
	{
		id = get_id(line->line);
		if (id)
		{
			line->info = add_info(id);
			id = ft_free(id);
			if (line->info == NOT)
				return (ft_putstr_fd("NOT", 0), FAIL);
		}
		else
			line->info = NL;
		line = line->next;
	}
	return (SUCCESS);
}

int	norm_file(t_line *line, t_value **value)
{
	t_line	*tmp;

	tmp = line;
	while (tmp)
	{
		if (!check_strchr(tmp->line))
			return (clear_line(&line), FAIL);
		tmp = tmp->next;
	}
	if (!check_id(line))
		return (clear_line(&line), FAIL);
	if (!check_id_maj(line, value))
		return (clear_line(&line), FAIL);
	(*value)->object = NULL;
	if (!check_id_min(line, value))
		return (clear_line(&line), free(*value), FAIL);
	return (SUCCESS);
}
