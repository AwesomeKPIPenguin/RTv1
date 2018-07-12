//
// Created by Dimon on 11.07.2018.
//

#include "../rtv1.h"

t_point		ft_find_collision(t_list *objs, t_object *dist,
								t_point origin, t_point direct)
{
	t_point		*coll;
	t_list		*node;
	t_object	*o;

	coll = NULL;
	node = objs;
	while (node)
	{
		o = (t_object *)(node->content);
		if ((coll = o->ft_get_collision_point(o, origin, direct)))
		{
			dist = o;
			return (*coll);
		}
		node = node->next;
	}
	return (NULL);
}

t_color		ft_throw_ray(t_env *e, t_point origin, t_point direct)
{

}

t_color		ft_cast_ray(t_env *e, int x, int y)
{
	t_color		res;
	t_point		vec;

	vec = e->scn->cam->vs_start_point;
	vec = ft_add_vector(vec, ft_mul_vector(e->scn->cam->vs_x_step_vec, x));
	vec = ft_add_vector(vec, ft_mul_vector(e->scn->cam->vs_y_step_vec, y));
	res = ft_throw_ray(e, e->scn->cam->origin, vec);

	return (res);
}
