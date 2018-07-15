//
// Created by Dimon on 11.07.2018.
//

#include "../rtv1.h"


/*
**	k[0] - own color koef
**	k[1] - specularity koef
**	k[2] - transparency koef
*/

static t_color	ft_apply_koef(t_coll coll, t_color color, t_byte koef)
{
	t_color	res;
	int		i;

	i = -1;
	while (++i < 3)
		res.argb[i] = (t_byte)((1.0 -
			((255.0 - (double)coll.o->color.argb[i]) * (double)koef) /
			pow(255, 2)) * (double)color.argb[i]);
	return (res);
}

static t_color	ft_get_final_color(t_env *e, t_coll coll,
									t_color spclr_col, t_color trans_col)
{
	t_object	*o;
	t_color		res;

	o = coll.o;
	res = ft_apply_a(o->color, coll.illum);
	if (o->spclr && o->trans)
		return (ft_add_color(res, ft_add_color(spclr_col, trans_col)));
	else if (o->spclr)
		return (ft_add_color(res, spclr_col));
	else if (o->trans)
		return (ft_add_color(res, trans_col));
	else
		return (res);
}

static t_color	ft_throw_ray(t_env *e, t_point origin, t_point direct)
{
	t_coll		coll;
	t_color		spclr_col;
	t_color		trans_col;

	coll = ft_find_collision(e->scn, origin, direct);
	if (!coll.o)
		return (e->scn->bg_color);
	else
	{
		if (coll.o->spclr)
			spclr_col = ft_apply_koef(coll,
				ft_throw_ray(e, coll.coll_pnt, coll.spclr_vec), coll.o->spclr);
		if (coll.o->trans)
			trans_col = ft_apply_koef(coll,
				ft_throw_ray(e, coll.coll_pnt, coll.trans_vec), coll.o->trans);
		return (ft_get_final_color(e, coll, spclr_col, trans_col));
	}
}

t_color			ft_trace_ray(t_env *e, int x, int y)
{
	t_color		res;
	t_point		vec;

	vec = e->scn->cam->vs_start_point;
	vec = ft_add_vector(vec, ft_mul_vector_s(e->scn->cam->vs_x_step_vec, x));
	vec = ft_add_vector(vec, ft_mul_vector_s(e->scn->cam->vs_y_step_vec, y));
	res = ft_throw_ray(e, e->scn->cam->origin, vec);
	return (res);
}
