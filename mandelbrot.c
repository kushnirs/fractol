/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 12:22:37 by sergee            #+#    #+#             */
/*   Updated: 2018/01/29 12:35:16 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	mouse_action(int button, int x, int y, t_mlx *data)
{
	button == M_UP ? data->index -= data->index / 20 : 0;
	button == M_UP ? data->re = formula(data->re, data->re +
					(x - data->width / 2) * data->index, 0.05) : 0;
	button == M_UP ? data->im = formula(data->im, data->im +
					(y - data->high / 2) * data->index, 0.05) : 0;
	button == M_DOWN ? data->index += data->index / 20 : 0;
	kernel_param(data);
	return (0);
}

static int	key_action_(int key, t_mlx *data)
{
	if (key == ESC)
	{
		mlx_destroy_window(data->mlx, data->win);
		return (0);
	}
	key == UP ? data->j_y += 50 : 0;
	key == DOWN ? data->j_y -= 50 : 0;
	key == RIGHT ? data->j_x -= 50 : 0;
	key == LEFT ? data->j_x += 50 : 0;
	kernel_param(data);
	return (0);
}

int			mandelbrot(void)
{
	t_mlx	data;

	data = (t_mlx){.width = WIDTH, .high = HIGH,
		.index = 0.003, .re = -0.75, .im = 0};
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.width, data.high, "Mandelbrot");
	data.image = mlx_new_image(data.mlx, data.width, data.high);
	data.data_adr =
	(t_ui *)mlx_get_data_addr(data.image, &data.bpp, &data.sl, &data.endian);
	host_fract("./kernel/mandelbrot.cl", "draw_mandelbrot", &data);
	mlx_mouse_hook(data.win, &mouse_action, &data);
	mlx_key_hook(data.win, &key_action_, &data);
	mlx_hook(data.win, 17, 0, &close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}
