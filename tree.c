/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 09:48:05 by sergee            #+#    #+#             */
/*   Updated: 2018/01/18 21:35:48 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	draw_tree(t_mlx *data, t_point p0, t_point p1)
{
	t_point	xy;

	if (p1.x > 1)
	{
		p1.x *= 0.73;
		xy.x = (p0.x + p1.x * cos(p1.y));
		xy.y = (p0.y - p1.x * sin(p1.y));
		draw_line(data, p0, xy,	ft_hex_to_dec("0xff6347") * p1.x / 2);
		draw_tree(data, xy, (t_point){p1.x, p1.y + data->re, 0});
		draw_tree(data, xy, (t_point){p1.x, p1.y - data->im, 0});
	}
	return (0);
}

static int	mouse_action(int button, int x, int y, t_mlx *data)
{
	x = y;
	button == M_UP && data->re >= 0.1 ? data->re -= 0.01 : 0;
	button == M_UP && data->im <= 1 ? data->im += 0.01 : 0;
	button == M_DOWN && data->re <= 1 ? data->re += 0.01 : 0;
	button == M_DOWN && data->im >= 0.1 ? data->im -= 0.01 : 0;
	ft_bzero(data->data_adr, HIGH * data->sl);
	draw_tree(data, (t_point){.x = WIDTH / 2, .y = HIGH},
					(t_point){.x = WIDTH - 920, .y =  M_PI / 2});
	mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
	return (0);
}

int			tree(void)
{
	t_mlx	data;
	t_point	p[2];

	p[0] = (t_point){.x = WIDTH / 2, .y = HIGH};
	p[1] = (t_point){.x = WIDTH - 920, .y = M_PI / 2};
	data = (t_mlx){.index = 1, .re = M_PI / 4, .im = M_PI / 4};
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIDTH, HIGH, "Pythagoras tree");
	data.image = mlx_new_image(data.mlx, WIDTH, HIGH);
	data.data_adr =
	(t_ui *)mlx_get_data_addr(data.image, &data.bpp, &data.sl, &data.endian);
	draw_tree(&data, p[0], p[1]);
	mlx_put_image_to_window(data.mlx, data.win, data.image, 0, 0);
	mlx_mouse_hook(data.win, &mouse_action, &data);
	mlx_key_hook(data.win, &key_action, &data);
	mlx_hook(data.win, 17, 0, &close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}
