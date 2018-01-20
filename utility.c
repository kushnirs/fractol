/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 21:58:17 by sergee            #+#    #+#             */
/*   Updated: 2018/01/20 18:52:43 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	draw_line(t_mlx *data, t_point p0, t_point p1, int color)
{
	double		t;
	double		k;
	double		xy[2];

	k = 1.0 / sqrt((p1.x - p0.x) * (p1.x - p0.x) +\
		(p1.y - p0.y) * (p1.y - p0.y));
	t = 0;
	while (t <= 1)
	{
		xy[0] = p0.x + t * (p1.x - p0.x);
		xy[1] = p0.y + t * (p1.y - p0.y);
		if (xy[0] >= 0 && xy[0] < data->width &&
			xy[1] >= 0 && xy[1] < data->high)
			data->data_adr[(int)xy[0] + (int)xy[1] * data->width] = color;
		t += k;
	}
}

double		formula(double a, double b, double t)
{
	return ((1 - t) * a + b * t);
}

int			close_window(t_mlx *data)
{
	mlx_destroy_window(data->mlx, data->win);
	return (0);
}

int			key_action(int key, t_mlx *data)
{
	key == ESC ? mlx_destroy_window(data->mlx, data->win) : 0;
	return (0);
}

t_ui		parse_color(int c1, t_ui it)
{
	double			t;
	unsigned char	dr;
	unsigned char	dg;
	unsigned char	db;

	t = (double)c1 / (double)it;
	dr = 9 * (1 - t) * t * t * t * 255;
	dg = 15 * (1 - t) * (1 - t) * t * t * 255;
	db = 8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255;
	return (dr * 0x10000 + dg * 0x100 + db);
}
