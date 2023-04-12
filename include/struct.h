/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:33:40 by eflaquet          #+#    #+#             */
/*   Updated: 2023/04/12 11:04:42 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define HEIGHT 1224
# define WIDTH 1224
# define EPSILON 0.0001
# define ALBEDO 0.3

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
	float	x;
	float	y;
	float	z;
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
	float		dia;
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
	float		dia_cy;
	float		h_cy;
	t_rgb		rgb;
	struct s_cy	*next;
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

typedef struct s_ray
{
	t_coord	origin;
	t_coord	diection;
}				t_ray;

//-------------------------------------------//

typedef struct	s_mlx
{
	void	*mlx;
	void	*mlx_win;
}				t_mlx;

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

#endif
