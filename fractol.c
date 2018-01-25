/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 12:13:11 by sergee            #+#    #+#             */
/*   Updated: 2018/01/25 20:28:01 by sergee           ###   ########.fr       */
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

int		main(int ac, char **av)
{
	t_mlx	data;

	(void)av;
	ac != 1 ? exit(ft_printf("Don't panic! Use main menu:)\n")) : 0;
	data = (t_mlx){.width = 620, .high = 650,
		.index = 1, .re = M_PI / 4, .im = M_PI / 4};
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.width, data.high, "FRACTO'L");
	data.image = mlx_new_image(data.mlx, data.width, data.high);
	data.data_adr =
	(t_ui *)mlx_get_data_addr(data.image, &data.bpp, &data.sl, &data.endian);
	draw_menu(&data);
	mlx_mouse_hook(data.win, &mouse_menu, &data);
	mlx_key_hook(data.win, (int (*)())&exit, &data);
	mlx_hook(data.win, 6, 0, &preview, &data);
	mlx_hook(data.win, 17, 0, (int (*)())&exit, &data);
	mlx_loop(data.mlx);
	return (0);
}
