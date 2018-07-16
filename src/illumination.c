//
// Created by Dimon on 14.07.2018.
//

#include "../rtv1.h"

/*
**	by now, the searching ray would stop if any object will be found
**	(specularity and transparency will be taken into account latter)
*/

int			ft_iscollide(t_scene *scn, t_point origin, t_point direct)
{
	t_list		*o_node;
	t_object	*o;

	o_node = scn->objs;
	while (o_node)
	{
		o = (t_object *)(o_node->content);
		if (o->ft_is_reachable(o->fig, origin, direct) && !ft_isnullpoint(
				o->ft_collide(o->fig, origin, direct)))
			return (1);
		o_node = o_node->next;
	}
	return (0);
}

t_byte		ft_illuminate(t_scene *scn, t_point coll, t_point norm)
{
	t_list		*l_node;
	t_light		*l;
	t_byte		res;
	double		cos;

	l_node = scn->lights;
	res = 0;
	while (l_node)
	{
		l = (t_light *)(l_node->content);
		cos = ft_vectors_cos(norm, ft_vectornew(coll, l->origin));
		if (cos > 0 && !ft_iscollide(scn, coll, l->origin))
			res += l->bright * BRIGHT_UNIT * cos /
				(pow(ft_get_dist(coll, l->origin), 2)) - res;
		l_node = l_node->next;
	}
	return (res);
}
