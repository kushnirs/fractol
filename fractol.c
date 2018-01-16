/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 12:13:11 by sergee            #+#    #+#             */
/*   Updated: 2018/01/16 21:48:06 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		get_fract_color(int i)
{
	static int palette[] = {
		0x800000, 0x8B0000, 0xA52A2A, 0xB22222, 0xDC143C, 0xFF0000, 0xFF6347,
		0xFF7F50, 0xCD5C5C, 0xF08080, 0xE9967A, 0xFA8072, 0xFFA07A, 0xFF4500,
		0xFF8C00, 0xFFA500, 0xFFD700, 0xB8860B, 0xDAA520, 0xEEE8AA, 0xBDB76B,
		0xF0E68C, 0x808000, 0xFFFF00, 0x9ACD32, 0x556B2F, 0x6B8E23, 0x7CFC00,
		0x7FFF00, 0xADFF2F, 0x006400, 0x008000, 0x228B22, 0x00FF00, 0x32CD32,
		0x90EE90, 0x98FB98, 0x8FBC8F, 0x00FA9A, 0x00FF7F, 0x2E8B57, 0x66CDAA,
		0x3CB371, 0x20B2AA, 0x2F4F4F, 0x008080, 0x008B8B, 0x00FFFF, 0x00FFFF,
		0xE0FFFF, 0x00CED1, 0x40E0D0, 0x48D1CC, 0xAFEEEE, 0x7FFFD4, 0xB0E0E6,
		0x5F9EA0, 0x4682B4, 0x6495ED, 0x00BFFF, 0x1E90FF, 0xADD8E6, 0x87CEEB,
		0x87CEFA, 0x191970, 0x000080, 0x00008B, 0x0000CD, 0x0000FF, 0x4169E1,
		0x8A2BE2, 0x4B0082, 0x483D8B, 0x6A5ACD, 0x7B68EE, 0x9370DB, 0x8B008B,
		0x9400D3, 0x9932CC, 0xBA55D3, 0x800080, 0xD8BFD8, 0xDDA0DD, 0xEE82EE,
		0xFF00FF, 0xDA70D6, 0xC71585, 0xDB7093, 0xFF1493, 0xFF69B4, 0xFFB6C1,
		0xFFC0CB, 0xFAEBD7, 0xF5F5DC, 0xFFE4C4, 0xFFEBCD, 0xF5DEB3, 0xFFF8DC,
		0xFFFACD, 0xFAFAD2, 0xFFFFE0, 0x8B4513, 0xA0522D, 0xD2691E, 0xCD853F,
		0xF4A460, 0xDEB887, 0xD2B48C, 0xBC8F8F, 0xFFE4B5, 0xFFDEAD, 0xFFDAB9,
		0xFFE4E1, 0xFFF0F5, 0xFAF0E6, 0xFDF5E6, 0xFFEFD5, 0xFFF5EE, 0xF5FFFA,
		0x708090, 0x778899, 0xB0C4DE, 0xE6E6FA, 0xFFFAF0, 0xF0F8FF, 0xF8F8FF,
		0xF0FFF0, 0xFFFFF0, 0xF0FFFF, 0xFFFAFA, 0x000000, 0x696969, 0x808080,
		0xA9A9A9, 0xC0C0C0, 0xD3D3D3, 0xDCDCDC, 0xF5F5F5, 0xFFFFFF
	};
	return (palette[i % 139]);
}

int main(int ac, char **av)
{
	int		x;
	int		y;
	int i;
	double a;
	double b;
	double lox;
	t_mlx	data;

	av = 0;
	ac != 2 ? exit(ft_printf("lox\n")) : 0;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIDTH, HIGH, "FRACTOL");
	data.image = mlx_new_image(data.mlx, WIDTH, HIGH);
	data.data_adr = (t_ui *)mlx_get_data_addr(data.image, &data.bpp, &data.sl, &data.endian);
	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HIGH)
		{
			i = -1;
			a = 0;
			b = 0;
			while ((a * a + b * b) < 4 && ++i < 256)
			{
				lox = a * a - b * b + -0.75 + (x - WIDTH / 2) * 0.005;
				b = 2 * a * b + 0 + (y - HIGH / 2) * 0.005;
				a = lox;
			}
			data.data_adr[y * WIDTH + x] = get_fract_color(i);
		}
	}
	mlx_put_image_to_window(data.mlx, data.win, data.image, 0, 0);
	// mlx_mouse_hook(data.win, &mouse_action, &data);
	// mlx_key_hook(data.win, &key_action, &data);
	// mlx_hook(data.win, 17, 0, &close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}