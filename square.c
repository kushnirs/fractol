/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 12:25:33 by sergee            #+#    #+#             */
/*   Updated: 2018/01/18 21:39:37 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	draw_square(t_mlx *data)
{
	int		i;
	double	d[2];
	t_point	xy[4];

	d[0] = 283 * 3;
	d[1] = 0;
	i = -1;
	while (++i < 1200)
	{
		xy[0].x = (int)(WIDTH / 2 + d[0] * cos(d[1] + M_PI / 4));
		xy[0].y = (int)(HIGH / 2 + d[0] * sin(d[1] + M_PI / 4));
		xy[1].x = (int)(WIDTH / 2 + d[0] * cos(d[1] + 3 * M_PI / 4));
		xy[1].y = (int)(HIGH / 2 + d[0] * sin(d[1] + 3 * M_PI / 4));
		xy[2].x = (int)(WIDTH / 2 + d[0] * cos(d[1] + 5 * M_PI / 4));
		xy[2].y = (int)(HIGH / 2 + d[0] * sin(d[1] + 5 * M_PI / 4));
		xy[3].x = (int)(WIDTH / 2 + d[0] * cos(d[1] + 7 * M_PI / 4));
		xy[3].y = (int)(HIGH / 2 + d[0] * sin(d[1] + 7 * M_PI / 4));
		draw_line(data, xy[0], xy[1], 200);
		draw_line(data, xy[1], xy[2], 200);
		draw_line(data, xy[2], xy[3], 200);
		draw_line(data, xy[3], xy[0], 200);
		d[1] += M_PI / data->re;
		d[0] *= sin(M_PI / data->im);
	}
}

static int	mouse_action(int button, int x, int y, t_mlx *data)
{
	(void)x;
	(void)y;
	button == M_UP && data->re <= 29 ? data->re += 0.5 : 0;
	button == M_UP && data->im >= 2 ? data->im -= 0.05 : 0;
	button == M_DOWN && data->re <= 31 ? data->re -= 0.3 : 0;
	button == M_DOWN && data->re >= 2 ? data->im += 0.03 : 0;
	ft_bzero(data->data_adr, HIGH * data->sl);
	draw_square(data);
	mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
	return (0);
}

int			square(void)
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
