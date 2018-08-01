//
// Created by Dimon on 31.07.2018.
//

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

static t_color	ft_add_3_colors(t_color c_1, t_color c_2, t_color c_3)
{
	int		i;
	double	sum;

	i = -1;
	sum = 3.0;
	sum -= (c_1.argb[3]) ? 1.0 : 0.0;
	sum -= (c_2.argb[3]) ? 1.0 : 0.0;
	sum -= (c_3.argb[3]) ? 1.0 : 0.0;
	if (!sum)
	{
		c_1.val = 0;
		return (c_1);
	}
	while (++i < 3)
		c_1.argb[i] = (t_byte)((double)((int)c_1.argb[i] + (int)c_2.argb[i] +
			(int)c_3.argb[i]) / sum);
	return (c_1);
}

t_color		ft_sum_colors(t_coll coll, t_color color_s, t_color color_t)
{
	t_color		res;
	t_object	*o;
	int			i;

	res.val = 0;
	o = coll.o;
	i = -1;
	while (++i < 3)
	{
		if (o->diff)
			res.argb[i] = (t_byte)(o->color.argb[i] * o->diff *
				ft_limitf(0.0, 1.0, coll.illum + o->ambnt));
		else
			res.val = INT_MAX;
		if (o->spclr)
			color_s.argb[i] = (t_byte)((double)(color_s.argb[i]) * o->spclr);
		else
			color_s.val = INT_MAX;
		if (o->trans)
			color_t.argb[i] = (t_byte)((double)(color_t.argb[i]) * o->trans);
		else
			color_s.val = INT_MAX;
	}
	return (ft_add_3_colors(res, color_s, color_t));
}
