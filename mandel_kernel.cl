
static unsigned int	parse_color_(int c1, unsigned int it)
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

__kernel void	draw_fract(__global int *buff, int width, int high, double re, double im, double index)
{
	int		xy[2];
	int		i;
	double	a[2];
	double	b;

	xy[0] = -1;
	while (++xy[0] < width)
	{
		xy[1] = -1;
		while (++xy[1] < high)
		{
			i = -1;
			a[0] = 0;
			b = 0;
			while ((a[0] * a[0] + b * b) < 4 && ++i < 256)
			{
				a[1] = a[0] * a[0] - b * b + re + (xy[0] - width / 2) * index;
				b = 2 * a[0] * b + im + (xy[1] - high / 2) * index;
				a[0] = a[1];
			}
			buff[xy[1] * width + xy[0]] = parse_color_(i, 256);
		}
	}
}
