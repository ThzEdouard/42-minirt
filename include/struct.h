/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:33:40 by eflaquet          #+#    #+#             */
/*   Updated: 2023/04/29 12:22:18 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define HEIGHT 800
# define WIDTH 800
# define EPSILON 0.0001
# define ALBEDO 0.003

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

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}				t_vector;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}			t_rgb;

//-------------------------------------------//

//struct for lumiere ambiante, camera, lumiere//

typedef struct s_la
{
	float	ratio;
	t_rgb	rgb;
}			t_la;

typedef struct s_ca
{
	t_vector	pv;
	t_vector	axe;
	int		fov;
}			t_ca;

typedef struct s_l
{
	t_vector	pl;
	float	ratio;
	t_rgb	rgb;
}			t_l;

//-------------------------------------------//

//struct for sphere, plan, cylindre//

typedef struct s_object
{
	t_vector		center;
	t_vector		axis;
	t_rgb			rgb;
	float			diameter;
	float			height;
	t_info			info;
	struct s_object	*next;
}				t_object;

typedef struct s_impact
{
	t_vector	p_inter;
	t_vector	normal;
	t_rgb	rgb;
	t_info	info;
	double	distance;
}				t_impact;

//-------------------------------------------//

typedef struct s_value
{
	t_la		lum_am;
	t_ca		cam;
	t_l			lum;
	t_object	*object;
}			t_value;

typedef struct s_line
{
	char			*line;
	t_info			info;
	struct s_line	*next;
}				t_line;

typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
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

typedef struct s_end
{
	t_mlx	mlx;
	t_data	data;
	t_value	*value;
}				t_end;

#endif
