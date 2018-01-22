/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apollon.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 01:03:53 by sergee            #+#    #+#             */
/*   Updated: 2018/01/21 03:37:19 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	draw_circle(t_mlx *data, t_point p1, double r, double ang, int i)
{
	int		j[2];
	t_point	p2;
	t_point	xy[2];
	double	h;
	double	r2;
	double	ang2;
	double	ang3;

	h = 2 * r * cos(M_PI / 5);
	j[0] = -1;
	while (++j[0] < 5)
	{
		ang2 = ang + M_PI / 5 * j[0] * 2;
		p2.x = p1.x - h * cos(ang2);
		p2.y = p1.y - h * sin(ang2);
		r2 = r / (2 * cos(M_PI / 5) + 1);
		ang3 = ang + M_PI + (2 * j[0] + 1) * M_PI / 5;
		j[1] = -1;
		while (++j[1] < 4)
		{
			xy[0].x = p1.x - r2 * cos(ang3 + j[1] * M_PI / 5 * 2);
			xy[0].y = p1.x - r2 * sin(ang3 + j[1] * M_PI / 5 * 2);
			xy[1].x = p1.x - r2 * cos(ang3 + (j[1] + 1) * M_PI / 5 * 2);
			xy[1].y = p1.x - r2 * sin(ang3 + (j[1] + 1) * M_PI / 5 * 2);
			draw_line(data, xy[0], xy[1], ft_hex_to_dec("0xffffff"));
		}
		if (i)
			draw_circle(data, p2, r / (2 * cos(M_PI / 5) + 1), ang + M_PI + (2 * j[0] + 1) * M_PI / 5, i - 1);
	}
	return (0);
}

int	apollon(void)
{
	t_mlx	data;
	t_point	p;

	data = (t_mlx){.width = WIDTH, .high = HIGH,
		.index = 100};
	p = (t_point){.x = data.width / 2 , .y = data.high / 2};
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.width, data.high, "Pythagoras tree");
	data.image = mlx_new_image(data.mlx, data.width, data.high);
	data.data_adr =
	(t_ui *)mlx_get_data_addr(data.image, &data.bpp, &data.sl, &data.endian);
	draw_circle(&data, p, 100, M_PI / 2, 1);
	mlx_put_image_to_window(data.mlx, data.win, data.image, 0, 0);
	// mlx_mouse_hook(data.win, &mouse_action, &data);
	mlx_key_hook(data.win, &key_action, &data);
	mlx_hook(data.win, 17, 0, &close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}
