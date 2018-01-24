/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 18:47:48 by sergee            #+#    #+#             */
/*   Updated: 2018/01/24 10:34:31 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		draw_menu(t_mlx *data)
{
	int	i;
	int w;
	int h;

	i = -1;
	while (++i < data->width * data->high)
		data->data_adr[i] = ft_hex_to_dec("0xffffff");
	draw_button(data, (t_point){15, 200}, (int[]){200, 50});
	draw_button(data, (t_point){15, 255}, (int[]){200, 50});
	draw_button(data, (t_point){15, 310}, (int[]){200, 50});
	draw_button(data, (t_point){15, 365}, (int[]){200, 50});
	draw_button(data, (t_point){15, 420}, (int[]){200, 50});
	draw_button(data, (t_point){15, 475}, (int[]){200, 50});
	draw_button(data, (t_point){15, 530}, (int[]){200, 50});
	draw_button(data, (t_point){15, 585}, (int[]){200, 50});
	mlx_string_put(data->mlx, data->win, 65, 215, 0, "Mandelbrot");
	mlx_string_put(data->mlx, data->win, 90, 270, 0, "Julia");
	mlx_string_put(data->mlx, data->win, 45, 325, 0, "Barnsley Fern");
	mlx_string_put(data->mlx, data->win, 45, 380, 0, "Spiral Squares");
	mlx_string_put(data->mlx, data->win, 40, 435, 0, "Pythagoras Tree");
	mlx_string_put(data->mlx, data->win, 20, 490, 0, "Sierpinski triangle");
	mlx_string_put(data->mlx, data->win, 15, 545, 0, "Centroid of Triangle");
	mlx_string_put(data->mlx, data->win, 65, 600, 0, "Durer Star");
	mlx_put_image_to_window(data->mlx, data->win,
		mlx_xpm_file_to_image(data->mlx, "img/logo3.xpm", &w, &h), 0, 0);
}

static void	preview_(int x, int y, t_mlx *data)
{
	int w;
	int h;

	x >= 15 && x <= 215 && y >= 475 && y <= 525 ?
	mlx_put_image_to_window(data->mlx, data->win,
	mlx_xpm_file_to_image(data->mlx, "img/triangle.xpm", &w, &h), 250, 200) : 0;
	x >= 15 && x <= 215 && y >= 530 && y <= 580 ?
	mlx_put_image_to_window(data->mlx, data->win,
	mlx_xpm_file_to_image(data->mlx,
		"img/triangle2.xpm", &w, &h), 250, 200) : 0;
	x >= 15 && x <= 215 && y >= 585 && y <= 635 ?
	mlx_put_image_to_window(data->mlx, data->win,
	mlx_xpm_file_to_image(data->mlx, "img/star.xpm", &w, &h), 250, 200) : 0;
	((x >= 15 || x <= 215) && (y < 200 || y > 635)) || (x < 15 || x > 215) ?
	mlx_put_image_to_window(data->mlx, data->win,
	mlx_xpm_file_to_image(data->mlx, "img/lox.xpm", &w, &h), 250, 200) : 0;
}

int			preview(int x, int y, t_mlx *data)
{
	int w;
	int h;

	x >= 15 && x <= 215 && y >= 200 && y <= 250 ?
	mlx_put_image_to_window(data->mlx, data->win,
	mlx_xpm_file_to_image(data->mlx, "img/mandel.xpm", &w, &h), 250, 200) : 0;
	x >= 15 && x <= 215 && y >= 255 && y <= 305 ?
	mlx_put_image_to_window(data->mlx, data->win,
	mlx_xpm_file_to_image(data->mlx, "img/julia.xpm", &w, &h), 250, 200) : 0;
	x >= 15 && x <= 215 && y >= 310 && y <= 360 ?
	mlx_put_image_to_window(data->mlx, data->win,
	mlx_xpm_file_to_image(data->mlx, "img/leaf.xpm", &w, &h), 250, 200) : 0;
	x >= 15 && x <= 215 && y >= 365 && y <= 415 ?
	mlx_put_image_to_window(data->mlx, data->win,
	mlx_xpm_file_to_image(data->mlx, "img/square.xpm", &w, &h), 250, 200) : 0;
	x >= 15 && x <= 215 && y >= 420 && y <= 470 ?
	mlx_put_image_to_window(data->mlx, data->win,
	mlx_xpm_file_to_image(data->mlx, "img/tree.xpm", &w, &h), 250, 200) : 0;
	preview_(x, y, data);
	return (0);
}

void		draw_button(t_mlx *data, t_point start, int s[2])
{
	t_point	tmp[3];

	tmp[0] = (t_point){start.x + s[0], start.y};
	tmp[1] = (t_point){start.x, start.y + s[1]};
	tmp[2] = (t_point){tmp[1].x + s[0], tmp[1].y};
	draw_line(data, start, tmp[0], 0);
	draw_line(data, start, tmp[1], 0);
	draw_line(data, tmp[1], tmp[2], 0);
	draw_line(data, tmp[0], tmp[2], 0);
	mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
}

int			mouse_menu(int button, int x, int y, t_mlx *data)
{
	(void)data;
	if (button == M_L)
	{
		x >= 15 && x <= 215 && y >= 200 && y <= 250 ? mandelbrot() : 0;
		x >= 15 && x <= 215 && y >= 255 && y <= 305 ? julia() : 0;
		x >= 15 && x <= 215 && y >= 310 && y <= 360 ? leaf() : 0;
		x >= 15 && x <= 215 && y >= 365 && y <= 415 ? square() : 0;
		x >= 15 && x <= 215 && y >= 420 && y <= 470 ? tree() : 0;
		x >= 15 && x <= 215 && y >= 475 && y <= 525 ? triangle() : 0;
		x >= 15 && x <= 215 && y >= 530 && y <= 580 ? triangle2() : 0;
		x >= 15 && x <= 215 && y >= 585 && y <= 635 ? star() : 0;
	}
	return (0);
}
