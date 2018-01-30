/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 02:33:31 by sergee            #+#    #+#             */
/*   Updated: 2018/01/30 13:48:06 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int		mouse_move(int x, int y, t_mlx *data)
{
	data->m_act ? data->im = 1.5 * (y - data->high / 2) /
		(0.5 * data->index * data->high) + data->j_y : 0;
	data->m_act ? data->re = (x - data->width / 2) /
		(0.5 * data->index * data->width) + data->j_x : 0;
	data->m_act ? kernel_param(data) : 0;
	return (0);
}

static int		mouse_action(int button, int x, int y, t_mlx *data)
{
	button == M_UP ? data->index += data->index / 20 : 0;
	button == M_UP ? data->j_x = formula(data->j_x, data->j_x +
	(x - data->width / 2) / (0.5 * data->index * data->width), 0.06) : 0;
	button == M_UP ? data->j_y = formula(data->j_y, data->j_y +
	1.5 * (y - data->high / 2) / (0.5 * data->index * data->high), 0.06) : 0;
	button == M_DOWN ? data->index -= data->index / 20 : 0;
	kernel_param(data);
	return (0);
}

int				julia(void)
{
	t_mlx	data;

	data = (t_mlx){.width = WIDTH, .high = HIGH, .index = 1, .re = -0.70176,
		.im = -0.3842, .j_x = 0, .j_y = 0, .m_act = 0};
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.width, data.high, "Julia");
	data.image = mlx_new_image(data.mlx, data.width, data.high);
	data.data_adr =
	(t_ui *)mlx_get_data_addr(data.image, &data.bpp, &data.sl, &data.endian);
	host_fract("./kernel/julia.cl", "draw_julia", &data);
	mlx_mouse_hook(data.win, &mouse_action, &data);
	mlx_key_hook(data.win, &key_action, &data);
	mlx_hook(data.win, 6, 0, &mouse_move, &data);
	mlx_hook(data.win, 17, 0, &close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}
