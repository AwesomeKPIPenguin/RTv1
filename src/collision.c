/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 13:21:02 by domelche          #+#    #+#             */
/*   Updated: 2018/08/23 13:25:52 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

static t_point	ft_get_collision_point(t_list *objs, t_object **obj,
										t_point od[2], t_object *except)
{
	t_list		*node;
	t_point		pnt[2];
	double		dist[2];
	t_object	*o;

	node = objs;
	pnt[0] = ft_null_pointnew();
	dist[0] = DBL_MAX;
	while (node)
	{
		o = (t_object *)(node->content);
		if (o == except)
		{
			node = node->next;
			continue ;
		}
		if (o->ft_is_reachable(o->fig, od[0], od[1]) &&
			!ft_isnullpoint(pnt[1] = o->ft_collide(o->fig, od[0], od[1])) &&
			(dist[1] = ft_get_dist(od[0], pnt[1]))	< dist[0])
		{
			pnt[0] = pnt[1];
			dist[0] = dist[1];
			*obj = o;
		}
		node = node->next;
	}
	return (pnt[0]);
}

t_coll			ft_get_collision(t_scene *scn, t_point origin, t_point direct,
								t_object *except)
{
	t_coll		coll;
	t_point		od[2];

	coll.o = NULL;
	od[0] = origin;
	od[1] = direct;
	if (ft_isnullpoint(coll.coll_pnt =
			ft_get_collision_point(scn->objs, &(coll.o), od, except)))
		return (coll);
	coll.norm = coll.o->ft_get_norm(coll.o->fig, coll.coll_pnt);

//	if (coll.coll_pnt.y > -400.0)
//	{
//		printf("coll: (%-10.4f, %-10.4f, %-10.4f);\n",
//			   coll.coll_pnt.x, coll.coll_pnt.y, coll.coll_pnt.z);
//		printf("norm: (%-10.4f, %-10.4f, %-10.4f);\n\n",
//			   coll.norm.x, coll.norm.y, coll.norm.z);
//	}

	if (coll.o->spclr)
		coll.spclr_vec = ft_reflect_vector(origin, coll.coll_pnt, coll.norm);

	// get transparency

	ft_illuminate(scn, &coll);

//	printf("collision:\npoint: (%f, %f, %f);\nreflection vector: (%f, %f, %f);\n\n",
//		coll.coll_pnt.x, coll.coll_pnt.y, coll.coll_pnt.z,
//		coll.spclr_vec.x, coll.spclr_vec.y, coll.spclr_vec.z);

	return (coll);
}
