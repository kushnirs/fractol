/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 09:48:05 by sergee            #+#    #+#             */
/*   Updated: 2018/01/17 13:10:30 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	draw_tree(t_mlx *data, double x, double y, double a, double b)
{
	double	x_n;
	double	y_n;

	if (a > 1)
	{
		a *= 0.73;
		x_n = (x + a * cos(b));
		y_n = (y - a * sin(b));
		draw_line(data, (double[]){x, x_n}, (double[]){y, y_n},
			ft_hex_to_dec("0xff6347") * a / 2);
		draw_tree(data, x_n, y_n, a, b + data->re);
		draw_tree(data, x_n, y_n, a, b - data->im);
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
	draw_tree(data, WIDTH / 2, HIGH, WIDTH - 920, M_PI / 2);
	mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
	return (0);
}

int			tree()
{
	t_mlx	data;

	data = (t_mlx){.index = 1, .re = M_PI / 4, .im = M_PI / 4};
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIDTH, HIGH, "Pythagoras tree");
	data.image = mlx_new_image(data.mlx, WIDTH, HIGH);
	data.data_adr =
		(t_ui *)mlx_get_data_addr(data.image, &data.bpp, &data.sl, &data.endian);
	draw_tree(&data, WIDTH / 2, HIGH, WIDTH - 920, M_PI / 2);
	mlx_put_image_to_window(data.mlx, data.win, data.image, 0, 0);
	mlx_mouse_hook(data.win, &mouse_action, &data);
	mlx_key_hook(data.win, &key_action, &data);
	mlx_hook(data.win, 17, 0, &close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}