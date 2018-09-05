/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 13:25:05 by domelche          #+#    #+#             */
/*   Updated: 2018/08/23 13:25:05 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

/*
**	x/y[0] - start point, iterator;
**	x/y[1] - end point;
*/

void	*ft_section_handle(void *arg)
{
	t_parg		*parg;
	int			x[2];
	int			y[2];
	int			y_iter;

	parg = (t_parg *)arg;
	x[0] = (parg->section % 4) * (WIN_WIDTH / (THREADS / 2)) - 1;
	y[0] = (parg->section / 4) * (WIN_HEIGHT / 2) - 1;
	x[1] = x[0] + WIN_WIDTH / (THREADS / 2) + 1;
	y[1] = y[0] + WIN_HEIGHT / 2 + 1;
	while (++x[0] < x[1])
	{
		y_iter = y[0];
		while (++y_iter < y[1])
			ft_pixel_put_image(parg->e, x[0], y_iter,
				/*printf("%#.6X;\n", */ft_trace_ray(parg, x[0], y_iter).val);
	}
	return (NULL);
}


/*

int		*ft_get_img_color_ptr(t_img *img, int x, int y)
{
	return ((int *)(img->data + (y * (int)WIN_WIDTH + x) * img->bpp));
}

int		ft_sum_pxls(t_env *e, int x, int y)
{
	int		res;
	int		*data;

	data = ft_get_img_color_ptr(e->img, x, y);
	res = *data;
	if ()
}

int		ft_smooth_pixel(t_env *e, int x, int y)
{
	int		res;
	int		*data;
	int		pxls;

	if (!x || x == WIN_WIDTH - 1)
	{
		if (!y || y == WIN_HEIGHT - 1)
			pxls = 4;
		else
			pxls = 6;
	}
	else
	{
		if (!y || y == WIN_HEIGHT - 1)
			pxls = 6;
		else
			pxls = 9;
	}
}

t_img	*ft_smooth_img(t_env *e)
{
	int		x;
	int		y;
	int		*data;

	y = -1;
	while (++y)
	{
		x = -1;
		while (++x)
		{
			data = ft_get_img_color_ptr(img, x, y);
		}
	}
}

*/

void	ft_render(t_env *e)
{
	pthread_t	threads[THREADS];
	t_parg		pargs[THREADS];
	int			i;

	i = -1;
	while (++i < THREADS)
	{
		pargs[i].section = i;
		pargs[i].e = e;
	}

//	pargs[4].section = 4;
//	pargs[4].e = e;

	i = -1;
	while (++i < THREADS)
		pthread_create(&threads[i], NULL,
			ft_section_handle, (void *)&pargs[i]);

//	ft_section_handle((void *)&pargs[4]);

	i = -1;
	while (++i < THREADS)
		pthread_join(threads[i], NULL);
//	ft_smooth(e->img, e->smooth_img);
//	ft_smooth(e->smooth_img, e->img);
//	ft_smooth(e->img, e->smooth_img);
	mlx_put_image_to_window(e->mlx, e->win, e->img->ptr, 0, 0);
}
