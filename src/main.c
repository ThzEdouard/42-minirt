/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:26:01 by eflaquet          #+#    #+#             */
/*   Updated: 2023/01/10 16:38:56 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_line	*file_line;

	if (argc > 2)
		exit(0);
	file_line = check_name(argv[1]);
	if (!file_line)
		return (0);
	if (!norm_file(file_line))
		return (0);
	clear_line(&file_line);
	return ();
}
