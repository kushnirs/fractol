/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.cl                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 02:33:31 by sergee            #+#    #+#             */
/*   Updated: 2018/01/24 23:49:20 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int		parse_color_(int c1, unsigned int it)
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

__kernel void	draw_mandelbrot(__global int *buff, int width,int high,
	double re,double im, double index, double j_x, double j_y)
{
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	int		i = 0;
	double	a[2] = {0, 0};
	double	b = 0;

	while ((a[0] * a[0] + b * b) < 4.0 && ++i < 128)
	{
		a[1] = a[0] * a[0] - b * b + re + (x - width / 2 + j_x) * index;
		b = 2 * a[0] * b + im + (y - high / 2 + j_y) * index;
		a[0] = a[1];
	}
	buff[y * width + x] = parse_color_(i, 128);
}
