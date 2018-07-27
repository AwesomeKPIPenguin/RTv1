//
// Created by Dimon on 11.07.2018.
//

#include "../rtv1.h"


/*
**	k[0] - own color koef
**	k[1] - specularity koef
**	k[2] - transparency koef
*/

static t_color	ft_apply_koef(t_coll coll, t_color color, double koef)
{
	t_color	res;
	int		i;

	i = -1;
	while (++i < 3)
		res.argb[i] = (t_byte)((((double)coll.o->color.argb[i]) * koef) /
			pow(255, 2) * (double)color.argb[i]);
	return (res);
}

static t_color	ft_get_final_color(t_coll coll,
									t_color spclr_col, t_color trans_col)
{
	t_object	*o;
	t_color		res;

	o = coll.o;
	res = coll.o->color;

//	printf("spclr: %#8X, trans: %#8X;\nillum: %3d, %#8X -> %#8X;\n\n",
//		spclr_col.val, trans_col.val, coll.illum, coll.o->color.val, res.val);

	if (o->spclr && o->trans)
		return (ft_apply_a(ft_add_color(
			ft_apply_koef(coll, res,
				255 - ft_limitf(0, 255, o->spclr + o->trans)),
			ft_add_color(
				ft_apply_koef(coll, spclr_col, o->spclr),
				ft_apply_koef(coll, trans_col, o->trans))),
			coll.illum / 255.0 * o->spclr));
	else if (o->spclr)
		return (ft_apply_a(ft_add_color(
			ft_apply_koef(coll, res, 255 - o->spclr),
			ft_apply_koef(coll, spclr_col, o->spclr)),
			coll.illum / 255.0 * o->spclr));
	else if (o->trans)
		return (ft_apply_a(ft_add_color(
			ft_apply_koef(coll, res, 255 - o->trans),
			ft_apply_koef(coll, trans_col, o->trans)),
			coll.illum / 255.0 * o->spclr));
	else
		return (ft_apply_a(res, coll.illum / 255.0 * o->spclr));
}

static t_color	ft_throw_ray(t_env *e, t_object *o,
							t_point origin, t_point direct)
{
//	printf("in ft_throw_ray      (%15.6f, %15.6f, %15.6f) -> (%15.6f, %15.6f, %15.6f);\n",
//		origin.x, origin.y, origin.z, direct.x, direct.y, direct.z);

	t_coll		coll;
	t_color		spclr_col;
	t_color		trans_col;

	spclr_col.val = -1;
	trans_col.val = 0;
 	coll = ft_get_collision(e->scn, origin, direct, o);
	if (!coll.o)
		return (spclr_col);
	spclr_col.val = 0;
	if (coll.o->spclr)
		spclr_col = ft_throw_ray(e, coll.o, coll.coll_pnt, coll.spclr_vec);

//	throw transparency ray

	return (ft_get_final_color(coll, spclr_col, trans_col));
}

t_color			ft_trace_ray(t_env *e, int x, int y)
{
	t_color		res;
	t_point		vec;
//		double		half_diag;

	vec = e->scn->cam->vs_start_point;
	vec = ft_add_vector(vec,
		ft_scale_vector(e->scn->cam->vs_x_step_vec, x));
	vec = ft_add_vector(vec,
		ft_scale_vector(e->scn->cam->vs_y_step_vec, y));
	vec = ft_unitvectornew(e->scn->cam->origin, vec);
	res = ft_throw_ray(e, NULL, e->scn->cam->origin, vec);
//	if (res.val < 0)
//	{
//		half_diag = sqrt(pow(WIN_WIDTH / 2.0, 2) + pow(WIN_HEIGHT / 2.0, 2));
//		res = ft_apply_a(e->scn->bg_color, 127.0 + ft_get_dist(
//				ft_pointnew(WIN_WIDTH / 2.0, WIN_HEIGHT / 2.0, 0.0),
//				ft_pointnew(x, y, 0.0)) / half_diag * 30.0);
//	}
	return (res);
}
