/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 12:13:11 by sergee            #+#    #+#             */
/*   Updated: 2018/01/18 14:41:33 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// static void	draw_menu(t_mlx *data)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < 600 * 400)
// 		data->data_adr[i] = ft_hex_to_dec("0xf7f7f7");
// 	draw_line(data, (double[]){10, 100}, (double[]){10, 10}, 0);
// 	draw_line(data, (double[]){100, 100}, (double[]){10, 50}, 0);
// 	draw_line(data, (double[]){10, 10}, (double[]){10, 50}, 0);
// 	draw_line(data, (double[]){10, 100}, (double[]){50, 50}, 0);

// }

int main()
{
	// t_mlx	data;

	// data = (t_mlx){.index = 1, .re = M_PI / 4, .im = M_PI / 4};
	// data.mlx = mlx_init();
	// data.win = mlx_new_window(data.mlx, 600, 400, "FRACTO'L");
	// data.image = mlx_new_image(data.mlx, 600, 400);
	// data.data_adr =
	// 	(t_ui *)mlx_get_data_addr(data.image, &data.bpp, &data.sl, &data.endian);
	// draw_menu(&data);
	// mlx_put_image_to_window(data.mlx, data.win, data.image, 0, 0);
	// // mlx_mouse_hook(data.win, &mouse_action, &data);
	// mlx_key_hook(data.win, &key_action, &data);
	// mlx_hook(data.win, 17, 0, &close_window, &data);
	// mlx_loop(data.mlx);
	// mandelbrot();
	julia();
	// tree();
	// square();
	// leaf();
	return (0);
}