/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 21:58:17 by sergee            #+#    #+#             */
/*   Updated: 2018/01/17 13:13:14 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	draw_line(t_mlx *data, double x[2], double y[2], int color)
{
	double		t;
	double		k;
	double		xy[2];

	k = 1.0 / sqrt((pow((x[1] - x[0]), 2) + pow((y[1] - y[0]), 2)));
	t = 0;
	while (t <= 1)
	{

		xy[0] = x[0] + t * (x[1] - x[0]);
		xy[1] = y[0] + t * (y[1] - y[0]);
		if (xy[0] >= 0 && xy[0] < WIDTH && xy[1] >= 0 && xy[1] < HIGH)
			data->data_adr[(int)xy[0] + (int)xy[1] * WIDTH] = color;
		t += k;
	}
}

double		formula(double a, double b, double t)
{
	return ((1 - t) * a + b * t);
}

int					close_window(t_mlx *data)
{
	data = NULL;
	exit(0);
	return (0);
}

int					key_action(int key, t_mlx *data)
{
	data = 0;
	key == ESC ? exit(0) : 0;
	// key == UP ? data->move_y += 50 : 0;
	// key == DOWN ? data->move_y += -50 : 0;
	// key == RIGHT ? data->move_x += -50 : 0;
	// key == LEFT ? data->move_x += 50 : 0;
	// key == B_A ? data->rot.ry -= 5 : 0;
	// key == B_W ? data->rot.rx -= 5 : 0;
	// key == B_Q ? data->rot.rz -= 5 : 0;
	// key == B_D ? data->rot.ry += 5 : 0;
	// key == B_S ? data->rot.rx += 5 : 0;
	// key == B_E ? data->rot.rz += 5 : 0;
	// key == B_PLUS ? data->size += data->size / 10 : 0;
	// key == B_MIN ? data->size -= data->size / 10 : 0;
	return (0);
}

unsigned int		parse_color(int c1, int c2, double t)
{
	unsigned char dr;
	unsigned char dg;
	unsigned char db;

	dr = (1 - t) * (double)(c1 / 0x10000 % 256) +
		t * (double)(c2 / 0x10000 % 256);
	dg = (1 - t) * (double)(c1 / 0x100 % 256) + t * (double)(c2 / 0x100 % 256);
	db = (1 - t) * (double)(c1 % 256) + t * (double)(c2 % 256);
	return (dr * 0x10000 + dg * 0x100 + db);
}
