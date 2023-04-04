/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_id_maj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:11:56 by eflaquet          #+#    #+#             */
/*   Updated: 2023/04/04 17:51:09 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_len(t_line *line, enum s_info info)
{
	int	nb;
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

int	check_int_max_min(char *line)
{
	if (*line == '-')
	{
		if (ft_strlen(line) > ft_strlen(CHAR_INT_MIN) || ft_atoi(line) < ft_atoi(CHAR_INT_MIN))
			return (FAIL);
	}
	else
	{
		if (ft_strlen(line) > ft_strlen(CHAR_INT_MAX) || ft_atoi(line) > ft_atoi(CHAR_INT_MAX))
			return (FAIL);
	}
	return (SUCCESS);
}

int	check_range_float(float min, float max, float nb)
{
	(void) min , (void)max, (void)nb;
	return (SUCCESS);
}

// int	check_range_int(int min, int max, int nb)
// {
// 	return (SUCCESS);
// }



int	check_rgb(char *line)
{
	char	*tmp;

	tmp = line;
	while (*line)
	{
		if (!ft_isdigit(*line) && *line == 46)
			return (FAIL);
		line++;
	}

	return (SUCCESS);
}



static int	check_A(t_line *tmp, int start, t_la *tmp_la)
{
	char	*line;
	char	**array_line;
	int		x;
	(void)tmp_la;
	while (tmp)
	{
		if (tmp->info == A)
			line = tmp->line;
		tmp = tmp->next;
	}
	array_line = ft_split(line, 32);
	if (!array_line)
		return (FAIL);
	while(array_line[start])
	{
		x = 0;
		while(array_line[start][x])
		{
				if (!ft_isdigit(array_line[start][x]) && (array_line[start][x] != 45 && array_line[start][x] != 44 && array_line[start][x] != 46))
					return (ft_free2(array_line) ,FAIL);
			x++;
		}
		start++;
	}
	if (start > 3 || (!check_range_float(0.0, 1.0, (float)ft_atoi(array_line[1])) && !check_rgb(array_line[2])))
		return (ft_free2(array_line) ,FAIL);
	printf("SUCCES\n");
	ft_free2(array_line);
	return (SUCCESS);
}

// static int	check_C(t_line *tmp)
// {
// 	char	*line;
// 	char	**array_line;

// 	while (tmp)
// 	{
// 		if (tmp->info == C)
// 			line = tmp->line;
// 		tmp = tmp->next;
// 	}
// 	array_line = ft_split(line, 32);
// 	return (SUCCESS);
// }

// static int	check_L(t_line *tmp)
// {
// 	char	*line;
// 	char	**array_line;

// 	while (tmp)
// 	{
// 		if (tmp->info == L)
// 			line = tmp->line;
// 		tmp = tmp->next;
// 	}
// 	array_line = ft_split(line, 32);
// 	return (SUCCESS);
// }

int	check_id_maj(t_line *line)
{
	t_value	*value;

	value = malloc(sizeof(t_value));
	if (!value)
		return (FAIL);
	if (!check_len(line, A) || !check_len(line, C) || !check_len(line, L))
		return (FAIL);
	check_A(line, 1,&value->lum_am);
	free(value);
	return (SUCCESS);
}
