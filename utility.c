/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 21:58:17 by sergee            #+#    #+#             */
/*   Updated: 2018/01/30 14:09:07 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	formula(double a, double b, double t)
{
	return ((1 - t) * a + b * t);
}

int		close_window(t_mlx *data)
{
	mlx_destroy_window(data->mlx, data->win);
	return (0);
}

int		key_action(int key, t_mlx *data)
{
	key == ESC ? mlx_destroy_window(data->mlx, data->win) : 0;
	if (key == B_Q)
		!data->m_act ? data->m_act++ : data->m_act--;
	return (0);
}

t_ui	parse_color_2(int c1, t_ui it)
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

t_ui	parse_color(int c1, int c2, double t)
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
