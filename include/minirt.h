/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:20:27 by eflaquet          #+#    #+#             */
/*   Updated: 2023/04/04 16:59:07 by eflaquet         ###   ########.fr       */
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
#include <stdio.h>

# define FAIL 0
# define SUCCESS 1
# define CHAR_INT_MAX "2147483647"
# define CHAR_INT_MIN "-2147483648"

typedef enum s_info
{
	A,
	C,
	L,
	SP,
	PL,
	CY,
	NL,
	NOT
}			t_info;

//struct for the save in to rgb or coord//

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}			t_rgb;

typedef struct s_coord
{
	char	*x;
	char	*y;
	char	*z;
}			t_coord;

//-------------------------------------------//

//struct for lumiere ambiante, camera, lumiere//

typedef struct s_la
{
	float	ratio;
	t_rgb	rgb;
}			t_la;

typedef struct s_ca
{
	t_coord	pv;
	t_coord	axe;
	int		fov;
}			t_ca;

typedef struct s_l
{
	t_coord	pl;
	float	ratio;
	t_rgb	rgb;
}			t_l;

//-------------------------------------------//

//struct for sphere, plan, cylindre//

typedef struct s_sp
{
	t_coord		ps;
	char		*dia;
	t_rgb		rgb;
	struct s_sp	*next;
}			t_sp;

typedef struct s_pl
{
	t_coord		pf;
	t_coord		vod;
	t_rgb		rgb;
	struct s_pl	*next;
}			t_pl;

typedef struct s_cy
{
	t_coord		pf;
	t_coord		vod;
	char		*dia_cy;
	char		*h_cy;
	t_rgb		rgb;
}			t_cy;

//-------------------------------------------//

typedef struct s_value
{
	t_la	lum_am;
	t_ca	cam;
	t_l		lum;
	t_sp	*sphere;
	t_pl	*plan;
	t_cy	*cylindre;
}			t_value;

typedef struct s_line
{
	char			*line;
	t_info			info;
	struct s_line	*next;
}				t_line;

//-------------------------------------------//

t_line	*check_name_norm(char	*file);
int		check_id_maj(t_line *line);
int		norm_file(t_line *line);
void	clear_line(t_line **l);

#endif