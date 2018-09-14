/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 13:25:05 by domelche          #+#    #+#             */
/*   Updated: 2018/08/23 13:26:43 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

t_img	*ft_imgnew(t_env *e)
{
	t_img	*img;

//	(void)e;

	img = (t_img *)ft_smemalloc(sizeof(t_img), "ft_imgnew");
	img->ptr = mlx_new_image(e->mlx, WIN_WIDTH, WIN_HEIGHT);
	img->data = mlx_get_data_addr(img->ptr, &(img->bpp),
		&(img->size_line), &(img->endian));
	img->bpp /= 8;
	return (img);
}

void	ft_pixel_put_image(t_env *e, int x, int y, int color)
{

	//printf("%#.6X;\n", color);

//	(void)e;
//	(void)color;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	*(int *)(e->img->data + (y * (int)WIN_WIDTH + x) * e->img->bpp) = color;
}

void	ft_smooth(t_img *base, t_img *res)
{
	int		x;
	int		y;
	int 	i;
	t_color	color;

	color.val = 0;
	x = 0;
	while (++x < WIN_WIDTH - 1)
	{
		y = 0;
		while (++y < WIN_HEIGHT - 1)
		{
			//printf("%d\n", (*(int *)(base->data + ((y) * (int)WIN_WIDTH + x) * base->bpp)));

			i = -1;
			while (++i < 3)
				color.argb[i] = (t_byte)((
					(double)((*(t_color *)(base->data +
						((y - 1) * (int)WIN_WIDTH + x - 1) * base->bpp)).argb[i]) +
					(double)((*(t_color *)(base->data +
						((y - 1) * (int)WIN_WIDTH + x) * base->bpp)).argb[i]) +
					(double)((*(t_color *)(base->data +
						((y - 1) * (int)WIN_WIDTH + x + 1) * base->bpp)).argb[i]) +
					(double)((*(t_color *)(base->data +
						((y) * (int)WIN_WIDTH + x + 1) * base->bpp)).argb[i]) +
					(double)((*(t_color *)(base->data +
						((y + 1) * (int)WIN_WIDTH + x + 1) * base->bpp)).argb[i]) +
					(double)((*(t_color *)(base->data +
						((y + 1) * (int)WIN_WIDTH + x) * base->bpp)).argb[i]) +
					(double)((*(t_color *)(base->data +
						((y + 1) * (int)WIN_WIDTH + x - 1) * base->bpp)).argb[i]) +
					(double)((*(t_color *)(base->data +
						((y) * (int)WIN_WIDTH + x - 1) * base->bpp)).argb[i]) +
					(double)((*(t_color *)(base->data +
						((y) * (int)WIN_WIDTH + x) * base->bpp)).argb[i])) / 9.0);

			//printf("%#6X;\n", color.val);

			*(int *)(res->data + (y * (int)WIN_WIDTH + x) * res->bpp) = color.val;
		}
	}
}
