/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 13:25:05 by domelche          #+#    #+#             */
/*   Updated: 2018/08/23 13:25:05 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

t_point		ft_change_blur_vec(t_point norm, t_point vec, double angle)
{
	t_point	proj;

	proj = ft_project_vector(norm, vec);
	if (acos(ft_vectors_cos(norm, vec)) + angle <= M_PI_2)
		return (vec);
	return (ft_turn_vector(proj, norm, M_PI_2 - angle));
}

t_point		ft_get_blur_proj(t_point origin, t_point norm)
{
	t_point		zero_proj;
	double		angle;

	zero_proj = ft_project_vector(norm,
		ft_vectornew(origin, ft_pointnew(0.0, 0.0, 0.0)));
	if (ft_vector_len(zero_proj) == 0.0)
		zero_proj = ft_project_vector(norm,
			ft_vectornew(origin, ft_pointnew(42.0, 0.0, 0.0)));
	if (ft_vector_len(zero_proj) == 0.0)
		zero_proj = ft_project_vector(norm,
			ft_vectornew(origin, ft_pointnew(0.0, 42.0, 0.0)));
	zero_proj = ft_tounitvector(zero_proj);
	angle = (double)rand() / (double)RAND_MAX * M_2_PI;
	return (ft_turn_vector_near(zero_proj, norm, angle));
}

//static t_color	ft_add_3_colors(t_color c_1, t_color c_2, t_color c_3)
//{
//	int		i;
//	double	sum;
//
//	i = -1;
//	sum = 3.0;
//	sum -= (c_1.argb[3]) ? 1.0 : 0.0;
//	sum -= (c_2.argb[3]) ? 1.0 : 0.0;
//	sum -= (c_3.argb[3]) ? 1.0 : 0.0;
//	if (!sum)
//	{
//		c_1.val = 0;
//		return (c_1);
//	}
//	while (++i < 3)
//		c_1.argb[i] = (t_byte)((double)((int)c_1.argb[i] + (int)c_2.argb[i] +
//			(int)c_3.argb[i]) / sum);
//	return (c_1);
//}

t_color		ft_sum_colors(t_coll coll, t_color color_s, t_color color_t)
{
	t_color		res;
	t_object	*o;
	int			i;

	res.val = 0;
	o = coll.o;
	i = -1;

//	if (o->spclr != 0)
//		printf("color_s: %#6X, spclr: %5.4f, res: %f;\n",
//			color_s.val, o->spclr, (double)(color_s.argb[2]) * o->spclr);

	while (++i < 3)
		res.argb[i] = (t_byte)((double)o->color.argb[i] * o->diff *
			(ft_limitf(0.0, 1.0, coll.illum + o->ambnt)) +
			(double)(color_s.argb[i]) * o->spclr +
			(double)(color_t.argb[i]) * o->trans);

//	printf("obj_color:   %#.6X; diffuse: %3.2f; illumination: %3.2f;\nspclr_color: %#.6X; specularity: %3.2f;\ntrans_color: %#.6X; transparency: %3.2f;\nres: %#.6X;\n\n",
//		o->color.val, o->diff, coll.illum + o->ambnt, color_s.val, o->spclr, color_t.val, o->trans, res.val);

	return (res);
}
