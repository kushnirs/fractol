/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 12:25:33 by sergee            #+#    #+#             */
/*   Updated: 2018/01/17 17:32:05 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void draw_square(t_mlx *data)
{
	int		i;
	double	d[2];
	double	x[4];
	double	y[4];

	d[0] = 283 * 3;
	d[1] = 0;
	i = -1;
	while (++i < 1200)
	{
		x[0] = (int)(WIDTH / 2 + d[0] * cos(d[1] + M_PI / 4));
		y[0] = (int)(HIGH / 2 + d[0] * sin(d[1] + M_PI / 4));
		x[1] = (int)(WIDTH / 2 + d[0] * cos(d[1] + 3 * M_PI / 4));
		y[1] = (int)(HIGH / 2 + d[0] * sin(d[1] + 3 * M_PI / 4));
		x[2] = (int)(WIDTH / 2 + d[0] * cos(d[1] + 5 * M_PI / 4));
		y[2] = (int)(HIGH / 2 + d[0] * sin(d[1] + 5 * M_PI / 4));
		x[3] = (int)(WIDTH / 2 + d[0] * cos(d[1] + 7 * M_PI / 4));
		y[3] = (int)(HIGH / 2 + d[0] * sin(d[1] + 7 * M_PI / 4));
		draw_line(data,(double[]){x[0], x[1]}, (double[]){y[0], y[1]}, 200);
		draw_line(data,(double[]){x[1], x[2]}, (double[]){y[1], y[2]}, 200);
		draw_line(data,(double[]){x[2], x[3]}, (double[]){y[2], y[3]}, 200);
		draw_line(data,(double[]){x[3], x[0]}, (double[]){y[3], y[0]}, 200);
		d[1] += M_PI / data->re;
		d[0] *= sin(M_PI / data->im);
	}
}

static int	mouse_action(int button, int x, int y, t_mlx *data)
{
	printf("re= %f\n", data->re);
	printf("im= %f\n", data->im);
	x = y;
	button == M_UP  && data->re <= 30? data->re += 0.5 : 0;
	button == M_UP && data->im >= 2? data->im -= 0.05 : 0;
	button == M_DOWN && data->re >= 2 ? data->re -= 0.3 : 0;
	ft_bzero(data->data_adr, HIGH * data->sl);
	draw_square(data);
	mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
	return (0);
}

int			square()
{
	t_mlx		data;

	data = (t_mlx){.index = 1, .re = 20, .im = 3};
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIDTH, HIGH, "Square");
	data.image = mlx_new_image(data.mlx, WIDTH, HIGH);
	data.data_adr =
		(t_ui *)mlx_get_data_addr(data.image, &data.bpp, &data.sl, &data.endian);
	draw_square(&data);
	mlx_put_image_to_window(data.mlx, data.win, data.image, 0, 0);
	mlx_mouse_hook(data.win, &mouse_action, &data);
	mlx_key_hook(data.win, &key_action, &data);
	mlx_hook(data.win, 17, 0, &close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}