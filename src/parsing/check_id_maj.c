/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_id_maj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:11:56 by eflaquet          #+#    #+#             */
/*   Updated: 2023/04/05 16:41:38 by eflaquet         ###   ########.fr       */
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
		return (ft_putstr_fd("non", 0), FAIL);
	return (SUCCESS);
}

int	check_id_maj(t_line *line)
{
	t_value	*value;

	value = malloc(sizeof(t_value));
	if (!value)
		return (FAIL);
	if (!check_len(line, A) || !check_len(line, C) || !check_len(line, L))
		return (FAIL);
	while (line)
	{
		if (line && line->info == A && !check_a(line, 1, &value->lum_am))
			return (printf("FAIL"), free(value), FAIL);
		if (line && line->info == C && !check_c(line, 1, &value->cam))
			return (printf("FAIL"), free(value), FAIL);
		if (line && line->info == L && !check_l(line, 1, &value->lum))
			return (printf("FAIL"), free(value), FAIL);
		line = line->next;
	}
	printf("A     %f      %d,%d,%d\n", value->lum_am.ratio, value->lum_am.rgb.r, value->lum_am.rgb.g, value->lum_am.rgb.b);
	printf("C     %f,%f,%f     %f,%f,%f     %d\n", value->cam.pv.x, value->cam.pv.y, value->cam.pv.z, value->cam.axe.x, value->cam.axe.y, value->cam.axe.z, value->cam.fov);
	printf("L     %f,%f,%f     %f     %d,%d,%d\n", value->lum.pl.x, value->lum.pl.y, value->lum.pl.z, value->lum.ratio, value->lum.rgb.r, value->lum.rgb.g, value->lum.rgb.b);
	free(value);
	return (SUCCESS);
}
