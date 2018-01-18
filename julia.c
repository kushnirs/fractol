/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 02:33:31 by sergee            #+#    #+#             */
/*   Updated: 2018/01/18 20:37:08 by skushnir         ###   ########.fr       */
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

static void		draw_fract(t_mlx *data)
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
			a = 1.5 * (x - WIDTH / 2) /
			(0.5 * data->index * WIDTH ) + data->j_x;
			b = (y - HIGH / 2) / (0.5 * data->index * HIGH) + data->j_y;
			while ((a * a + b * b) < 4 && ++i < 128)
			{
				lox = a * a - b * b + data->re;
				b = 2 * a * b + data->im;
				a = lox;
			}
			data->data_adr[y * WIDTH + x] = (i * 9) % 255;
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
}

static int		mouse_move(int x, int y, t_mlx *data)
{
	y = x;
	data->m_act ? data->im = 1.5 * (x - WIDTH / 2) /
		(0.5 * data->index * WIDTH ) + data->j_x : 0;
	data->m_act ? data->re = (y - HIGH / 2) /
		(0.5 * data->index * HIGH) + data->j_y : 0;
	data->m_act ? draw_fract(data) : 0;
	return (0);
}

static int		mouse_action(int button, int x, int y, t_mlx *data)
{
	button == M_L ? data->m_act++ : 0;
	button == M_UP ? data->index += data->index / 20 : 0;
	button == M_UP ? data->j_x = formula(data->j_x, data->j_x +
		1.5 * (x - WIDTH / 2) / (0.5 * data->index * WIDTH), 0.06) : 0;
	button == M_UP ? data->j_y = formula(data->j_y, data->j_y +
		(y - HIGH / 2) / (0.5 * data->index * HIGH), 0.06) : 0;
	button == M_DOWN ? data->index -= data->index / 20 : 0;
	draw_fract(data);
	return (0);
}

int 			julia(void)
{
	t_mlx	data;

	data = (t_mlx){.index = 1, .re = -0.70176, .im = -0.3842, .j_x = 0,
		.j_y = 0, .m_act = 0};
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIDTH, HIGH, "Julia");
	data.image = mlx_new_image(data.mlx, WIDTH, HIGH);
	data.data_adr =
	(t_ui *)mlx_get_data_addr(data.image, &data.bpp, &data.sl, &data.endian);
	draw_fract(&data);
	mlx_mouse_hook(data.win, &mouse_action, &data);
	mlx_key_hook(data.win, &key_action, &data);
	mlx_hook(data.win, 5, 0, &ft_off, &data);
	mlx_hook(data.win, 6, 0, &mouse_move, &data);
	mlx_hook(data.win, 17, 0, &close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}
