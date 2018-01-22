/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 00:38:50 by sergee            #+#    #+#             */
/*   Updated: 2018/01/22 14:00:23 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	draw_triangle(t_mlx *data, t_point p[3], int i)
{
	t_point	m;

	m.x = (p[0].x + p[1].x + p[2].x) / 3;
	m.y = (p[0].y + p[1].y + p[2].y) / 3;
	draw_line(data, p[0], p[1], ft_hex_to_dec("0xffffff"));
	draw_line(data, p[1], p[2], ft_hex_to_dec("0xffffff"));
	draw_line(data, p[2], p[0], ft_hex_to_dec("0xffffff"));
	draw_line(data, p[0], m, ft_hex_to_dec("0xffffff"));
	draw_line(data, p[1], m, ft_hex_to_dec("0xffffff"));
	draw_line(data, p[2], m, ft_hex_to_dec("0xffffff"));
	if (--i)
	{
		draw_triangle(data, (t_point[]){p[0], m, p[1]}, i);
		draw_triangle(data, (t_point[]){p[1], m, p[2]}, i);
		draw_triangle(data, (t_point[]){p[2], m, p[0]}, i);
	}
	return (0);
}

static int	mouse_action(int button, int x, int y, t_mlx *data)
{
	t_point	p[3];

	p[0] = (t_point){.x = 1, .y = data->high - 1};
	p[1] = (t_point){.x = data->width / 2, .y = 1};
	p[2] = (t_point){.x = data->width - 1, .y = data->high - 1};
	x = y;
	button == M_UP && data->index < 8 ? data->index++ : 0;
	button == M_DOWN && data->index > 1 ? data->index-- : 0;
	ft_bzero(data->data_adr, data->high * data->sl);
	draw_triangle(data, (t_point[]){p[0], p[1], p[2]}, data->index);
	mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
	return (0);
}

int			triangle2(void)
{
	t_mlx	data;
	t_point	p[3];

	data = (t_mlx){.width = WIDTH, .high = HIGH, .index = 1};
	p[0] = (t_point){.x = 1, .y = data.high - 1};
	p[1] = (t_point){.x = data.width / 2, .y = 1};
	p[2] = (t_point){.x = data.width - 1, .y = data.high - 1};
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.width, data.high,
		"Centroid of Triangle");
	data.image = mlx_new_image(data.mlx, data.width, data.high);
	data.data_adr =
	(t_ui *)mlx_get_data_addr(data.image, &data.bpp, &data.sl, &data.endian);
	draw_triangle(&data, (t_point[]){p[0], p[1], p[2]}, data.index);
	mlx_put_image_to_window(data.mlx, data.win, data.image, 0, 0);
	mlx_mouse_hook(data.win, &mouse_action, &data);
	mlx_key_hook(data.win, &key_action, &data);
	mlx_hook(data.win, 17, 0, &close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}
