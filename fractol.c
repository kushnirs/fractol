/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 12:13:11 by sergee            #+#    #+#             */
/*   Updated: 2018/01/21 02:54:13 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int main(void)
{
	t_mlx	data;

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

// static int	draw_circle(t_mlx *data, int i)
// {
// 	double	a[4];
// 	double	b[4];
// 	double	r;
// 	double	flx;
// 	double	fly;
// 	t_point	p[2];

// 	p[0].x = 0.2;
// 	p[0].y = 0.3;
// 	a[0] = 0;
// 	b[0] = 0;
// 	r = sqrt(3);
// 	while (i--)
// 	{
// 		a[0] = (double)rand() / RAND_MAX;
// 		a[1] = 3 * (1 + r - p[0].x) / ((1 + r - p[0].x) *
// 			(1 + r - p[0].x) + p[0].y * p[0].y) - (1 + r) / (2 + r);
// 		b[1] = 3 * p[0].y / ((1 + r - p[0].x) *
// 			(1 + r - p[0].x) + p[0].y * p[0].y);
// 		a[0] <= 1 / 3 && a[0] >= 0 ? p[1].x = a[1] : 0;
// 		a[0] <= 1 / 3 && a[0] >= 0 ? p[1].y = b[1] : 0;
// 		a[2] = -0.5;
// 		b[2] = r / 2;
// 		a[3] = -0.5;
// 		b[3] = -r / 2;
// 		flx = a[1] / ((a[1] * a[1]) + (b[1] * b[1]));
// 		fly = -b[1] / ((a[1] * a[1]) + (b[1] * b[1]));
// 		a[0] <= 2 / 3 && a[0] >= 1 / 3 ? p[1].x = flx * a[2] - flx * b[2] : 0;
// 		a[0] <= 2 / 3 && a[0] >= 1 / 3 ? p[1].y = flx * a[2] + flx * b[2] : 0;
// 		a[0] <= 3 / 3 && a[0] >= 2 / 3 ? p[1].x = flx * a[3] - flx * b[3] : 0;
// 		a[0] <= 3 / 3 && a[0] >= 2 / 3 ? p[1].y = flx * a[3] + flx * b[3] : 0;
// 		p[0].x = p[1].x;
// 		p[0].y = p[1].y;
// 		printf("x=%f\n", p);
// 		if (p[0].x >= 0 && p[0].x < data->width &&
// 			p[0].y >= 0 && p[0].y < data->high)
// 			data->data_adr[(int)p[0].x + data->width / 2 +
// 				((int)p[0].y +  data->high / 2) * data->width] = 3329330;
// 	}

// 	return (0);

// }

// static int	draw_circle(t_mlx *data, t_point p1, double r, double ang, int i)
// {
// 	int		j[2];
// 	t_point	p2;
// 	t_point	xy[2];
// 	double	h;
// 	double	r2;
// 	double	ang2;
// 	double	ang3;

// 	h = 2 * r * cos(M_PI / 5);
// 	j[0] = -1;
// 	while (++j[0] < 5)
// 	{
// 		ang2 = ang + M_PI / 5 * j[0] * 2;
// 		p2.x = p1.x - h * cos(ang2);
// 		p2.y = p1.y - h * sin(ang2);
// 		r2 = r / (2 * cos(M_PI / 5) + 1);
// 		ang3 = ang + M_PI + (2 * j[0] + 1) * M_PI / 5;
// 		j[1] = -1;
// 		while (++j[1] < 4)
// 		{
// 			xy[0].x = p1.x + r2 * cos(ang3 + j[1] * M_PI / 5 * 2);
// 			xy[0].y = p1.x + r2 * sin(ang3 + j[1] * M_PI / 5 * 2);
// 			xy[1].x = p1.x + r2 * cos(ang3 + (j[1] + 1) * M_PI / 5 * 2);
// 			xy[1].y = p1.x + r2 * sin(ang3 + (j[1] + 1) * M_PI / 5 * 2);
// 			draw_line(data, xy[0], xy[1], ft_hex_to_dec("0xffffff"));
// 		}
// 		if (i)
// 			draw_circle(data, p2, r / (2 * cos(M_PI / 5) + 1), ang3, i - 1);
// 	}
// 	return (0);
// }