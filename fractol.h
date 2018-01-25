/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 12:14:12 by sergee            #+#    #+#             */
/*   Updated: 2018/01/25 10:27:06 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include "OpenCL/opencl.h"
# include "minilibx/mlx.h"
# include "libft/printf/ft_printf.h"

# define DEVICE_TYPE CL_DEVICE_TYPE_GPU
# define HIGH	1300
# define WIDTH	2000
# define B_A	0
# define B_W	13
# define B_D	2
# define B_S	1
# define B_Q	12
# define B_E	14
# define B_PLUS	69
# define B_MIN	78
# define M_UP	5
# define M_DOWN	4
# define M_L	1
# define M_R	2
# define UP		126
# define DOWN	125
# define LEFT	123
# define RIGHT	124
# define ESC	53
# define PI		3.14159265358979323846

typedef	struct			s_kernel
{
	cl_device_id		dev_id;
	cl_context			context;
	cl_command_queue	com_queue;
	cl_mem				memobj;
	cl_program			program;
	cl_kernel			kernel;
	cl_platform_id		p_id;
	cl_uint				ret_num_dev;
	cl_uint				ret_num_p;
	size_t				gl_w_s;
}						t_host;

typedef struct			s_point
{
	double				x;
	double				y;
}						t_point;

typedef struct			s_mlx
{
	void				*mlx;
	void				*win;
	void				*image;
	t_ui				*data_adr;
	int					bpp;
	int					sl;
	int					endian;
	double				index;
	double				re;
	double				im;
	double				j_x;
	double				j_y;
	int					m_act;
	int					width;
	int					high;
	t_host				host;
}						t_mlx;

double					formula(double a, double b, double t);
void					kernel_param(t_mlx *data);
int						host_fract(char *filename, char *funcname, t_mlx *data);
void					draw_line(t_mlx *data, t_point p0,
						t_point p1, int color);
void					draw_button(t_mlx *data, t_point start, int s[2]);
void					draw_menu(t_mlx *data);
t_ui					parse_color(int c1, int c2, double t);
t_ui					parse_color_2(int c1, t_ui t);
int						preview(int x, int y, t_mlx *data);
int						mouse_menu(int button, int x, int y, t_mlx *data);
int						key_action(int key, t_mlx *data);
int						close_window(t_mlx *data);
int						mandelbrot(void);
int						square(void);
int						julia(void);
int						tree(void);
int						triangle(void);
int						triangle2(void);
int						star(void);
int						leaf(void);

#endif
