//
// Created by Dimon on 14.07.2018.
//

#include "../rtv1.h"

/*
**	by now, the searching ray would stop if any object will be found
**	(specularity and transparency will be taken into account latter)
*/

int			ft_iscollide(t_scene *scn, t_point origin, t_point direct,
							t_point light)
{
	t_list		*o_node;
	t_object	*o;
	t_point		coll;

	o_node = scn->objs;
	while (o_node)
	{
		o = (t_object *)(o_node->content);
		coll = o->ft_collide(o->fig, origin, direct);
		if (ft_pointcmp(direct, ft_unitvectornew(coll, light)))
			return (1);
		o_node = o_node->next;
	}
	return (0);
}

t_byte		ft_illuminate(t_scene *scn, t_point coll, t_point norm)
{
	t_list		*l_node;
	t_light		*l;
	t_byte		res[2];
	double		cos;
	double		cl_len;

	l_node = scn->lights;
	res[0] = 0;
	while (l_node)
	{
		l = (t_light *)(l_node->content);
		cos = ft_vectors_cos(norm, ft_vectornew(coll, l->origin));
		if (cos > 0 && !ft_iscollide(scn, coll,
			ft_unitvectornew(coll, l->origin), l->origin))
		{
			cl_len = ft_get_dist(coll, l->origin);
			res[1] = (cl_len < l->bright * BRIGHT_UNIT) ?
				(t_byte)(l->bright * cos / (pow(cl_len / BRIGHT_UNIT, 2))) : 0;
			res[0] = (res[1] > res[0]) ? res[1] : res[0];
		}
		l_node = l_node->next;
	}
	return (res[0]	);
}
