/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:30:11 by eflaquet          #+#    #+#             */
/*   Updated: 2023/01/10 11:30:47 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	msg_name(char *str)
{
	ft_putstr_fd(str, 0);
	exit (FAIL);
}

static t_line	*new_elem(char *str)
{
	t_line	*new;

	new = malloc(sizeof(t_line));
	if (!new)
		return (NULL);
	new->line = ft_strdup(str);
	if (!new->line)
		return (NULL);
	new->next = NULL;
	return (new);
}

static t_line	*set_line(int ld, t_line **l)
{
	t_line	*tmp;
	char	*line;

	line = get_next_line(ld);
	if (!line)
		return (NULL);
	*l = new_elem(line);
	tmp = *l;
	while (line)
	{
		free(line);
		line = get_next_line(ld);
		if (!line)
			break ;
		tmp->next = new_elem(line);
		if (!tmp->next)
			return (clear_line(l), NULL);
		tmp = tmp->next;
	}
	if (line)
		free(line);
	return (*l);
}

t_line	*check_name(char	*file)
{
	int		len;
	int		ld;
	t_line	*line;

	len = ft_strlen(file);
	if (len > 3 && !ft_strcmp(file + (len - 3), ".rf"))
		msg_name("\e[0;91mError\nname for the file or not .rt\e[0m");
	ld = open(file, O_RDONLY);
	if (ld == -1)
		msg_name("\e[0;91mError\nfile is not open\e[0m");
	line = set_line(ld, &line);
	if (line)
		norm_file(line);
	close(ld);
	return (line);
}

void	clear_line(t_line **l)
{
	t_line	*line;

	while (*l)
	{
		line = *l;
		*l = (*l)->next;
		free(line->line);
		free(line);
	}
	*l = NULL;
}
