/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 12:22:37 by sergee            #+#    #+#             */
/*   Updated: 2018/01/18 20:35:12 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	draw_fract(t_mlx *data)
{
	int		x;
	int		y;
	int		i;
	double	a;
	double	b;
	double	lox;

	ft_bzero(data->data_adr, HIGH * data->sl);
	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HIGH)
		{
			i = -1;
			a = 0;
			b = 0;
			while ((a * a + b * b) < 4 && ++i < 256)
			{
				lox = a * a - b * b + data->re + (x - WIDTH / 2) * data->index;
				b = 2 * a * b + data->im + (y - HIGH / 2) * data->index;
				a = lox;
			}
			data->data_adr[y * WIDTH + x] = i * 25 % 256;
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
}

static int	mouse_action(int button, int x, int y, t_mlx *data)
{
	button == M_UP ? data->index -= data->index / 20 : 0;
	button == M_UP ? data->re = formula(data->re, data->re +
					(x - WIDTH / 2) * data->index, 0.05) : 0;
	button == M_UP ? data->im = formula(data->im, data->im +
					(y - HIGH / 2) * data->index, 0.05) : 0;
	button == M_DOWN ? data->index += data->index / 20 : 0;
	draw_fract(data);
	return (0);
}

int			mandelbrot(void)
{
	t_mlx	data;

	data = (t_mlx){.index = 0.003, .re = -0.75, .im = 0};
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIDTH, HIGH, "Mandelbrot");
	data.image = mlx_new_image(data.mlx, WIDTH, HIGH);
	data.data_adr =
	(t_ui *)mlx_get_data_addr(data.image, &data.bpp, &data.sl, &data.endian);
	draw_fract(&data);
	mlx_mouse_hook(data.win, &mouse_action, &data);
	mlx_key_hook(data.win, &key_action, &data);
	mlx_hook(data.win, 17, 0, &close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}
