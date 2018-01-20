/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 16:53:27 by sergee            #+#    #+#             */
/*   Updated: 2018/01/20 18:45:20 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	draw_triangle(t_mlx *data, t_point p0, t_point p1,
							t_point p2, int i)
{
	t_point point[3];

	point[0] = (t_point){.x = (p0.x + p1.x) / 2, .y = (p0.y + p1.y) / 2};
	point[1] = (t_point){.x = (p1.x + p2.x) / 2, .y = (p1.y + p2.y) / 2};
	point[2] = (t_point){.x = (p0.x + p2.x) / 2, .y = (p0.y + p2.y) / 2};
	draw_line(data, p0, p1, ft_hex_to_dec("0xffffff"));
	draw_line(data, p1, p2, ft_hex_to_dec("0xffffff"));
	draw_line(data, p2, p0, ft_hex_to_dec("0xffffff"));
	if (i--)
	{
		draw_triangle(data, p0, point[0], point[2], i);
		draw_triangle(data, p1, point[0], point[1], i);
		draw_triangle(data, p2, point[1], point[2], i);
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
	button == M_UP  && data->index < 11? data->index++ : 0;
	button == M_DOWN && data->index > 1? data->index-- : 0;
	ft_bzero(data->data_adr, data->high * data->sl);
	draw_triangle(data, p[0], p[1], p[2], data->index);
	mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
	return (0);
}

int	triangle(void)
{
	t_mlx	data;
	t_point	p[3];

	data = (t_mlx){.width = WIDTH, .high = HIGH, .index = 1};
	p[0] = (t_point){.x = 1, .y = data.high - 1};
	p[1] = (t_point){.x = data.width / 2, .y = 1};
	p[2] = (t_point){.x = data.width - 1, .y = data.high - 1};
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.width, data.high,
		"Sierpinski triangle");
	data.image = mlx_new_image(data.mlx, data.width, data.high);
	data.data_adr =
	(t_ui *)mlx_get_data_addr(data.image, &data.bpp, &data.sl, &data.endian);
	draw_triangle(&data, p[0], p[1], p[2], data.index);
	mlx_put_image_to_window(data.mlx, data.win, data.image, 0, 0);
	mlx_mouse_hook(data.win, &mouse_action, &data);
	mlx_key_hook(data.win, &key_action, &data);
	mlx_hook(data.win, 17, 0, &close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}