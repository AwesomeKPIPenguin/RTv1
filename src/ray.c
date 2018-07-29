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
	res.val = 0;

}

static t_point	ft_change_vec(t_point origin, t_point norm,
									t_point vec, double angle)
{
	t_point	proj;

	proj = ft_project_vector(origin, norm, vec);
	if (acos(ft_vectors_cos(norm, vec)) + angle <= M_PI_2)
		return (vec);
	return (ft_turn_vector(proj, norm, M_PI_2 - angle));
}

t_color			ft_throw_rays(t_env *e, t_coll coll, t_point *vec, double k)
{
	double		max_angle;
	double		angle;
	int			rays;
	int			i;
	t_color		res;

	max_angle = ft_torad(k * 90.0);
	rays = ft_limit(1, 10, (int)(k * 10.0));
	i = -1;
	res.val = 0;
	*vec = ft_change_vec(coll.coll_pnt, coll.norm, *vec, max_angle);
	while (++i < rays)
	{
		angle = (double)rand() / (double)RAND_MAX * max_angle;

		res = ft_add_color();
	}
}

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
		ft_throw_rays();

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
