/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 12:22:37 by sergee            #+#    #+#             */
/*   Updated: 2018/01/24 15:50:57 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	draw_fract(t_mlx *data)
{
	int		xy[2];
	int		i;
	double	a[2];
	double	b;

	xy[0] = -1;
	while (++xy[0] < data->width)
	{
		xy[1] = -1;
		while (++xy[1] < data->high)
		{
			i = -1;
			a[0] = 0;
			b = 0;
			while ((a[0] * a[0] + b * b) < 4 && ++i < 256)
			{
				a[1] = a[0] * a[0] - b * b + data->re +
					(xy[0] - data->width / 2) * data->index;
				b = 2 * a[0] * b + data->im + (xy[1] - HIGH / 2) * data->index;
				a[0] = a[1];
			}
			data->data_adr[xy[1] * data->width + xy[0]] = parse_color(i, 256);
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
}

static int	mouse_action(int button, int x, int y, t_mlx *data)
{
	button == M_UP ? data->index -= data->index / 20 : 0;
	button == M_UP ? data->re = formula(data->re, data->re +
					(x - data->width / 2) * data->index, 0.05) : 0;
	button == M_UP ? data->im = formula(data->im, data->im +
					(y - data->high / 2) * data->index, 0.05) : 0;
	button == M_DOWN ? data->index += data->index / 20 : 0;
	ft_bzero(data->data_adr, data->high * data->sl);
	draw_fract(data);
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
	draw_fract(&data);
	mlx_mouse_hook(data.win, &mouse_action, &data);
	mlx_key_hook(data.win, &key_action, &data);
	mlx_hook(data.win, 17, 0, &close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}
