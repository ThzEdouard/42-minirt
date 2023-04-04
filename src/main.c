/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:26:01 by eflaquet          #+#    #+#             */
/*   Updated: 2023/04/04 10:29:36 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_line	*file_line;

	if (argc > 2)
		exit(FAIL);
	file_line = check_name_norm(argv[1]);
	if (!file_line)
		return (FAIL);
	clear_line(&file_line);
	return (SUCCESS);
}
