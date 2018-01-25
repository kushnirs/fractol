/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 01:03:53 by sergee            #+#    #+#             */
/*   Updated: 2018/01/25 12:14:50 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	draw_pentagon(t_point p1, double r2, double ang3, t_mlx *data)
{
	int		j;
	t_point	xy[2];

	j = -1;
	while (++j < 4)
	{
		xy[0].x = p1.x + r2 * cos(ang3 + j * (M_PI / 5) * 2);
		xy[0].y = p1.y + r2 * sin(ang3 + j * (M_PI / 5) * 2);
		xy[1].x = p1.x + r2 * cos(ang3 + (j + 1) * M_PI / 5 * 2);
		xy[1].y = p1.y + r2 * sin(ang3 + (j + 1) * M_PI / 5 * 2);
		draw_line(data, xy[0], xy[1], 0xffffff - 50000 * j);
	}
}

static int	draw_star(t_mlx *data, t_point p1, double r_a[], int i)
{
	int		j;
	t_point	p2;
	double	h;
	double	r2;
	double	ang[2];

	h = 2 * r_a[0] * cos(M_PI / 5);
	j = -1;
	while (++j < 5)
	{
		ang[0] = r_a[1] + M_PI / 5 * j * 2;
		p2.x = p1.x - h * cos(ang[0]);
		p2.y = p1.y - h * sin(ang[0]);
		r2 = r_a[0] / (2 * cos(M_PI / 5) + 1);
		ang[1] = r_a[1] + M_PI + (2 * j + 1) * (M_PI / 5);
		draw_pentagon(p1, r2, ang[1], data);
		if (i > 0)
			draw_star(data, p2, (double[]){r_a[0] / (2 * cos(M_PI / 5) + 1),
				r_a[1] + M_PI + (2 * j + 1) * M_PI / 5}, i - 1);
	}
	return (0);
}

static int		key_action_(int key, t_mlx *data)
{
	t_point	p;

	if (key == ESC)
	{
		mlx_destroy_window(data->mlx, data->win);
		return(0);
	}
	key == UP ? data->j_y += 50 : 0;
	key == DOWN ? data->j_y -= 50 : 0;
	key == RIGHT ? data->j_x -= 50 : 0;
	key == LEFT ? data->j_x += 50 : 0;
	p = (t_point){.x = data->width / 2 - data->j_x,
		.y = data->high / 2 - data->j_y};
	ft_bzero(data->data_adr, data->high * data->sl);
	draw_star(data, p, (double[]){150, M_PI / 2}, data->index);
	mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
	return (0);
}

static int	mouse_action(int button, int x, int y, t_mlx *data)
{
	t_point	p;

	p = (t_point){.x = data->width / 2 - data->j_x, .y = data->high / 2 - data->j_y};
	x = y;
	button == M_UP && data->index < 6 ? data->index++ : 0;
	button == M_DOWN && data->index > 1 ? data->index-- : 0;
	ft_bzero(data->data_adr, data->high * data->sl);
	draw_star(data, p, (double[]){150, M_PI / 2}, data->index);
	mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
	return (0);
}

int			star(void)
{
	t_mlx	data;
	t_point	p;

	data = (t_mlx){.width = WIDTH, .high = HIGH,
		.index = 1, .j_x = 0, .j_y = 0};
	p = (t_point){.x = data.width / 2, .y = data.high / 2};
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.width, data.high, "Durer Star");
	data.image = mlx_new_image(data.mlx, data.width, data.high);
	data.data_adr =
	(t_ui *)mlx_get_data_addr(data.image, &data.bpp, &data.sl, &data.endian);
	draw_star(&data, p, (double[]){150, M_PI / 2}, data.index);
	mlx_put_image_to_window(data.mlx, data.win, data.image, 0, 0);
	mlx_mouse_hook(data.win, &mouse_action, &data);
	mlx_key_hook(data.win, &key_action_, &data);
	mlx_hook(data.win, 17, 0, &close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}
