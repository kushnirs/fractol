/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 12:14:12 by sergee            #+#    #+#             */
/*   Updated: 2018/01/18 21:50:20 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h>
# include <math.h>
# include "minilibx/mlx.h"
# include "libft/printf/ft_printf.h"

# define HIGH	900
# define WIDTH	1200
# define B_A	0
# define B_W	13
# define B_D	2
# define B_S	1
# define B_Q	12
# define B_E    14
# define B_PLUS 69
# define B_MIN  78
# define M_UP   5
# define M_DOWN 4
# define M_L	1
# define M_R	2
# define UP		126
# define DOWN	125
# define LEFT	123
# define RIGHT	124
# define ESC	53
# define PI		3.14159265358979323846

typedef struct	s_point
{
	double	x;
	double	y;
}				t_point;

typedef struct	s_mlx
{
	void	*mlx;
	void	*win;
	void	*image;
	t_ui	*data_adr;
	int		bpp;
	int		sl;
	int		endian;
	double	index;
	double	re;
	double	im;
	double	j_x;
	double	j_y;
	int		m_act;
}				t_mlx;

void				draw_line(t_mlx *data, t_point p0, t_point p1, int color);
int					key_action(int key, t_mlx *data);
int					close_window(t_mlx *data);
unsigned int		parse_color(int c1, t_ui it);
double				formula(double a, double b, double t);
int 				mandelbrot();
int					square();
int					julia();
int					tree();
int					leaf();
#endif