/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 09:48:05 by sergee            #+#    #+#             */
/*   Updated: 2018/01/25 01:24:44 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int		ft_off(int button, int x, int y, t_mlx *data)
{
	(void)button;
	(void)x;
	(void)y;
	data->m_act = 0;
	return (0);
}

static int	draw_tree(t_mlx *data, t_point p0, t_point p1)
{
	t_ui	color;
	t_point	xy;

	if (p1.x > 2)
	{
		p1.x *= data->index;
		xy.x = (p0.x + p1.x * cos(p1.y));
		xy.y = (p0.y - p1.x * sin(p1.y));
		color = parse_color(0x8B4513, 0xff00, 1 / p1.x);
		draw_line(data, p0, xy, color);
		draw_tree(data, xy, (t_point){p1.x, p1.y + data->re});
		draw_tree(data, xy, (t_point){p1.x, p1.y - data->im});
	}
	return (0);
}

static int	mouse_action(int button, int x, int y, t_mlx *data)
{
	x = y;
	button == M_L ? data->m_act++ : 0;
	data->m_act && button == M_UP && data->index < 0.73 ?
		data->index += 0.01 : 0;
	data->m_act && button == M_DOWN && data->index > 0.5 ?
		data->index -= 0.01 : 0;
	button == M_UP && data->re >= 0.1 ? data->re -= 0.01 : 0;
	button == M_UP && data->im <= 1 ? data->im += 0.01 : 0;
	button == M_DOWN && data->re <= 1 ? data->re += 0.01 : 0;
	button == M_DOWN && data->im >= 0.1 ? data->im -= 0.01 : 0;
	ft_bzero(data->data_adr, data->high * data->sl);
	draw_tree(data, (t_point){.x = data->width / 2, .y = data->high},
					(t_point){.x = data->width * 0.25, .y = M_PI / 2});
	mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
	return (0);
}

int			tree(void)
{
	t_mlx	data;
	t_point	p[2];

	data = (t_mlx){.width = WIDTH, .high = HIGH,
		.index = 0.5, .re = M_PI / 4, .im = M_PI / 4};
	p[0] = (t_point){.x = data.width / 2, .y = data.high};
	p[1] = (t_point){.x = data.width * 0.25, .y = M_PI / 2};
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.width, data.high,
				"Pythagoras tree");
	data.image = mlx_new_image(data.mlx, data.width, data.high);
	data.data_adr =
	(t_ui *)mlx_get_data_addr(data.image, &data.bpp, &data.sl, &data.endian);
	draw_tree(&data, p[0], p[1]);
	mlx_put_image_to_window(data.mlx, data.win, data.image, 0, 0);
	mlx_mouse_hook(data.win, &mouse_action, &data);
	mlx_key_hook(data.win, &key_action, &data);
	mlx_hook(data.win, 5, 0, &ft_off, &data);
	mlx_hook(data.win, 17, 0, &close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}
