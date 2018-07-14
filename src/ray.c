//
// Created by Dimon on 11.07.2018.
//

#include "../rtv1.h"

t_coll		ft_find_collision(t_list *objs, t_object **dst,
								t_point origin, t_point direct)
{
	t_coll		coll;
	t_list		*node;
	t_object	*o;

	node = objs;
	while (node)
	{
		o = (t_object *)(node->content);
		if (o->ft_is_reachable(o->fig, origin, direct) && !ft_isnullpoint(
				coll.coll_pnt = o->ft_collide(o->fig, origin, direct)))
		{
			*dst = o;
			if (o->spclr)
				coll.spclr_vec = ft_reflect_vector(origin, coll.coll_pnt,
					o->ft_get_norm(o->fig, coll.coll_pnt));
			// get specularity
			coll.illum = ft_illuminate();
			return (coll);
		}
		node = node->next;
	}
	return (coll);
}

t_color		ft_throw_ray(t_env *e, t_point origin, t_point direct)
{
	t_object	*o;
	t_point		coll;

	o = NULL;
	coll = ft_find_collision(e->scn->objs, &o, origin, direct);
	if (!o)
		return (e->scn->bg_color);

}

t_color		ft_cast_ray(t_env *e, int x, int y)
{
	t_color		res;
	t_point		vec;

	vec = e->scn->cam->vs_start_point;
	vec = ft_add_vector(vec, ft_mul_vector_s(e->scn->cam->vs_x_step_vec, x));
	vec = ft_add_vector(vec, ft_mul_vector_s(e->scn->cam->vs_y_step_vec, y));
	res = ft_throw_ray(e, e->scn->cam->origin, vec);

	return (res);
}
