/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 17:19:35 by sergee            #+#    #+#             */
/*   Updated: 2018/01/18 04:04:35 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static double fRand(double fMin, double fMax)
{
    double f;

    f = (double)rand() / RAND_MAX;
    return (fMin + f * (fMax - fMin));
}

static int num_func(int n_f)
{
	int i;
	double	r;
	double	prob[4] = {0.01, 0.85, 0.07, 0.07};

	r = fRand(0.0, 1.0);
	i = -1;
	while (++i <= 3)
	{
		r -= prob[i];
		if (r <= 0)
		{
			n_f = i;
			break;
		}
	}
	return (n_f);
}

static void	draw_leaf(t_mlx *data, double coef[4][6])
{
	int		i[2];
	int		n_f;
	double	temp[2];
	double	xy[2];

	temp[0] = WIDTH / 2;
	temp[1] = HIGH;
	n_f = 0;
	i[0] = -1;
	while (++i[0] < 400000)
	{
		n_f = num_func(n_f);
		xy[0] = coef[n_f][0] * temp[0] + coef[n_f][1] * temp[1] + coef[n_f][4];
		xy[1] = coef[n_f][2] * temp[0] + coef[n_f][3] * temp[1] + coef[n_f][5];
		temp[0] = xy[0];
		temp[1] = xy[1];
		xy[0] = (int)(xy[0] * (int)(WIDTH / 12) + WIDTH / 2);
		xy[1] = (int)(xy[1] * (int)(HIGH / 9.92));
		if (xy[0] >= 0 && xy[0] < WIDTH && xy[1] >= 0 && xy[1] < HIGH)
			data->data_adr[(int)xy[0] + (int)xy[1] * WIDTH] = 3329330;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
}

int	leaf()
{
	t_mlx		data;
	double	coef[4][6] = {{0, 0, 0, 0.16, 0, 0},
		{0.85, 0.04, -0.04, 0.85, 0, 1.6},
		{0.2, -0.24, 0.23, 0.22, 0, 1.3},
		{-0.15, 0.28, 0.26, 0.24, 0, 0.44}};

	data = (t_mlx){.index = 1, .re = 20, .im = 3};
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIDTH, HIGH, "Leaf");
	data.image = mlx_new_image(data.mlx, WIDTH, HIGH);
	data.data_adr =
		(t_ui *)mlx_get_data_addr(data.image, &data.bpp, &data.sl, &data.endian);
	draw_leaf(&data, coef);
	// mlx_mouse_hook(data.win, &mouse_action, &data);
	mlx_key_hook(data.win, &key_action, &data);
	mlx_hook(data.win, 17, 0, &close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}