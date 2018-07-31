//
// Created by Dimon on 11.07.2018.
//

#include "../rtv1.h"

static t_color	ft_throw_ray(t_env *e, t_object *o,
							   t_point origin, t_point direct)
{
//	printf("in ft_throw_ray      (%15.6f, %15.6f, %15.6f) -> (%15.6f, %15.6f, %15.6f);\n",
//		origin.x, origin.y, origin.z, direct.x, direct.y, direct.z);

	t_coll		coll;
	t_color		spclr_col;
	t_color		trans_col;

	spclr_col.val = 0;
	trans_col.val = 0;
	coll = ft_get_collision(e->scn, origin, direct, o);
	if (!coll.o)
		return (e->scn->bg_color);
	if (coll.o->spclr)
		spclr_col = (o->s_blur) ?
			ft_throw_rays(e, coll, &(coll.spclr_vec), o->s_blur) :
			ft_throw_ray(e, coll.o, coll.coll_pnt, coll.spclr_vec);
	if (coll.o->trans)
		trans_col = (o->t_blur) ?
			ft_throw_rays(e, coll, &(coll.trans_vec), o->t_blur) :
			ft_throw_ray(e, coll.o, coll.coll_pnt, coll.trans_vec);
	return (ft_get_final_color(coll, spclr_col, trans_col));
}

t_color			ft_throw_rays(t_env *e, t_coll coll, t_point *vec, double k)
{
	double		max_angle;
	int			rays;
	int			i;
	t_color		color;
	t_color		res;

	max_angle = ft_torad(k * 90.0);
	rays = ft_limit(1, 10, (int)(k * 10.0));
	i = -1;
	res.val = 0;
	*vec = ft_change_blur_vec(coll.norm, *vec, max_angle);
	while (++i < rays)
	{
		color = ft_throw_ray(e, coll.o, coll.coll_pnt,
			ft_turn_vector(ft_get_blur_proj(coll.coll_pnt, *vec), *vec,
				(double)rand() / (double)RAND_MAX * max_angle));
		res = (i) ? ft_add_color(res, color) : color;
	}
	return (res);
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
