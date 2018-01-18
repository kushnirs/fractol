/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 12:13:11 by sergee            #+#    #+#             */
/*   Updated: 2018/01/18 22:04:22 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	draw_button(t_mlx *data ,t_point start, int s[2], char *str)
{
	t_point	tmp[3];

	tmp[0] = (t_point){start.x + s[0], start.y};
	tmp[1] = (t_point){start.x, start.y + s[1]};
	tmp[2] = (t_point){tmp[1].x + s[0], tmp[1].y};
	draw_line(data, start, tmp[0], 0);
	draw_line(data, start, tmp[1], 0);
	draw_line(data, tmp[1], tmp[2], 0);
	draw_line(data, tmp[0], tmp[2], 0);
	mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
	mlx_string_put(data->mlx, data->win,
		start.x + s[1] / 2, start.y + s[0] / 2, 123456, str);
}

static void	draw_menu(t_mlx *data)
{
	int	i;
	// int w;
	// int h;

	i = -1;
	ft_bzero(data->data_adr, WIDTH * HIGH * 4);
	while (++i < WIDTH * HIGH)
		data->data_adr[i] = ft_hex_to_dec("0xf7f7f7");
	draw_button(data, (t_point){15, 500}, (int[]){200, 50}, "zdorov");
	draw_button(data, (t_point){15, 700}, (int[]){200, 50}, "sobaka");
	// mlx_put_image_to_window(data->mlx, data->win, mlx_xpm_file_to_image(data->mlx, "images.xpm", &w, &h), 500, 200);
}

int main(void)
{
	t_mlx	data;

	data = (t_mlx){.index = 1, .re = M_PI / 4, .im = M_PI / 4};
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIDTH, HIGH, "FRACTO'L");
	data.image = mlx_new_image(data.mlx, WIDTH, HIGH);
	data.data_adr =
		(t_ui *)mlx_get_data_addr(data.image, &data.bpp, &data.sl, &data.endian);
	draw_menu(&data);
	// mlx_mouse_hook(data.win, &mouse_action, &data);
	mlx_key_hook(data.win, &key_action, &data);
	mlx_hook(data.win, 17, 0, &close_window, &data);
	// mandelbrot();
	// julia();
	// tree();
	// square();
	// leaf();
	mlx_loop(data.mlx);
	return (0);
}