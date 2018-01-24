/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.cl                                           :+:      :+:    :+:   */
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

__kernel void	draw_julia(__global int *data, int width,int high,
	double re,double im, double index, double j_x, double j_y)
{
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	int		i = 0;
	double	a[2];
	double	b;

	a[0] = 1.5 * (x - width / 2) / (0.5 * index * width) + j_x;
	b = (y - high / 2) / (0.5 * index * high) + j_y;
	while ((a[0] * a[0] + b * b) < 4 && ++i < 128)
	{
		a[1] = a[0] * a[0] - b * b + re;
		b = 2 * a[0] * b + im;
		a[0] = a[1];
	}
	data[y * width + x] = parse_color_(i, 128);
}
