/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:20:27 by eflaquet          #+#    #+#             */
/*   Updated: 2023/04/06 15:57:49 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "mlx.h"
# include "libft.h"
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>

# include "checker.h"

# define FAIL 0
# define SUCCESS 1

t_line	*check_name_norm(char	*file, t_value **value);
int		check_id_maj(t_line *line, t_value **tmp);
int		check_id_min(t_line *line, t_value **tmp);
int		norm_file(t_line *line, t_value **value);
void	clear_line(t_line **l);

#endif