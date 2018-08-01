//
// Created by Dimon on 12.07.2018.
//

#include "../rtv1.h"

double		ft_torad(double degrees)
{
	return (degrees * M_PI / 180.0);
}

void		ft_solve_sqr(double a, double b, double c, double (*res)[3])
{
	double	d;

	d = pow(b, 2) - 4.0 * a * c;
	if (d < 0)
	{
		*res[0] = 0;
		return ;
	}
	d = sqrt(d);
	(*res)[0] = 1;
	(*res)[1] = (-b + d) / (2.0 * a);
	(*res)[2] = (-b - d) / (2.0 * a);
}

t_color		ft_apply_a(t_color color, double bright)
{
	double	k;

	k = bright - 127.0;
	color.argb[2] += (double)((k > 0) ? 255 - color.argb[2] : color.argb[2]) /
		128.0 * k;
	color.argb[1] += (double)((k > 0) ? 255 - color.argb[1] : color.argb[1]) /
		128.0 * k;
	color.argb[0] += (double)((k > 0) ? 255 - color.argb[0] : color.argb[0]) /
		128.0 * k;
	return (color);
}

t_color		ft_color_apply_k(t_color color, double k)
{
	color.argb[2] *= k;
	color.argb[1] *= k;
	color.argb[0] *= k;
	return (color);
}

t_color		ft_add_color(t_color c_1, t_color c_2)
{
	c_1.argb[2] += (c_2.argb[2] - c_1.argb[2]) / 2;
	c_1.argb[1] += (c_2.argb[1] - c_1.argb[1]) / 2;
	c_1.argb[0] += (c_2.argb[0] - c_1.argb[0]) / 2;
	return (c_1);
}
