//
// Created by Dimon on 14.07.2018.
//

#include "../rtv1.h"

t_coll			ft_find_collision(t_scene *scn,	t_point origin, t_point direct)
{
	t_coll		coll;
	t_list		*node;
	t_object	*o;
	t_point		norm;

	node = scn->objs;
	coll.o = NULL;
	while (node)
	{
		o = (t_object *)(node->content);
		if (o->ft_is_reachable(o->fig, origin, direct) && !ft_isnullpoint(
				coll.coll_pnt = o->ft_collide(o->fig, origin, direct)))
		{
			coll.o = o;
			norm = o->ft_get_norm(o->fig, coll.coll_pnt);
			if (o->spclr)
				coll.spclr_vec = ft_reflect_vector(origin, coll.coll_pnt, norm);

			// get transparency

			coll.illum = ft_illuminate(scn, coll.coll_pnt, norm);

			printf("collision:\npoint: (%f, %f, %f);\nreflection vector: (%f, %f, %f);\n\n",
				coll.coll_pnt.x, coll.coll_pnt.y, coll.coll_pnt.z,
				coll.spclr_vec.x, coll.spclr_vec.y, coll.spclr_vec.z);

			return (coll);
		}
		node = node->next;
	}
	return (coll);
}
