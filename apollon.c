/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apollon.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 01:03:53 by sergee            #+#    #+#             */
/*   Updated: 2018/01/20 11:30:54 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	draw_circle(t_mlx *data, t_point p, double r)
{
	double	i;
	t_point	c;
 	
	i = 0;
	while (i < 360)
	{
		c.x = r * cos(i * M_PI / 180) + p.x;
		c.y = r * sin(i * M_PI / 180) + p.y;
		data->data_adr[(int)c.x + (int)c.y * data->width] =
			ft_hex_to_dec("0xffffff");
		i += 0.1;
	}
}

int	apollon(void)
{
	t_mlx	data;
	t_point	p;

	data = (t_mlx){.width = WIDTH, .high = HIGH,
		.index = 1};
	p = (t_point){.x = data.width / 2, .y = data.high / 2};
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.width, data.high, "Pythagoras tree");
	data.image = mlx_new_image(data.mlx, data.width, data.high);
	data.data_adr =
	(t_ui *)mlx_get_data_addr(data.image, &data.bpp, &data.sl, &data.endian);
	draw_circle(&data, p, data.high / 2 - 1);
	mlx_put_image_to_window(data.mlx, data.win, data.image, 0, 0);
	// mlx_mouse_hook(data.win, &mouse_action, &data);
	mlx_key_hook(data.win, &key_action, &data);
	mlx_hook(data.win, 17, 0, &close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}
