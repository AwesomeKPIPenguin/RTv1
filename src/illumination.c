/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   illumination.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 13:25:05 by domelche          #+#    #+#             */
/*   Updated: 2018/08/23 13:26:31 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

/*
**	by now, the searching ray would stop if any object will be found
**	(specularity and transparency will be taken into account latter)
*/

int			ft_iscollide
				(t_scene *scn, t_point3 origin, t_point3 direct, t_point3 light)
{
	t_list		*o_node;
	t_object	*o;
	t_point3	coll;

	origin = ft_3_add_vector(origin, direct);
	o_node = scn->objs;
	while (o_node)
	{
		o = (t_object *)(o_node->content);
		coll = o->ft_collide(o->fig, origin, direct);
		if (!ft_3_isnullpoint(coll) &&
			ft_3_pointcmp(ft_3_unitvectornew(coll, origin),
				ft_3_vector_scale(ft_3_unitvectornew(coll, light), -1), 1e-6))
			return (1);
		o_node = o_node->next;
	}
	return (0);
}

void		ft_illuminate(t_parg *parg, t_coll *coll)
{
	t_list			*node;
	t_light			*l;
	double			cos[2];
	double			cl_len;

	coll->illum = 0.0;
	coll->phong = 127.0;
	node = parg->e->scn->lights;
	while (node)
	{
		l = (t_light *)(node->content);
		cos[0] = ft_3_vector_cos(coll->norm,
								 ft_3_vectornew(coll->coll_pnt, l->origin));
		if (cos[0] >= 0 && !ft_iscollide(parg->e->scn,
			coll->coll_pnt, ft_3_unitvectornew(coll->coll_pnt, l->origin),
			l->origin))
		{
			cos[1] = ft_3_vector_cos(coll->spclr_vec,
				ft_3_vectornew(coll->coll_pnt, l->origin));
			cl_len = ft_3_point_point_dist(coll->coll_pnt, l->origin);
			coll->illum += (!cl_len) ? l->bright :
				l->bright * cos[0] / (pow(cl_len / BRIGHT_UNIT, 2));
			if (cos[1] > 0.9)
				coll->phong = MAX(coll->phong, pow(cos[1] - 0.9, 2) *
					coll->o->phong * 100.0 * 255.0);
		}
		node = node->next;
	}
	coll->illum = ft_limitf(0.0, 1.0, coll->illum);
}
