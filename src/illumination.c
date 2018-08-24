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

void		ft_illuminate(t_parg *parg, t_coll *coll)
{
	t_list			*l_node;
	t_light_node	*l;
	double			cos;
	double			cl_len;

	l_node = parg->e->scn->lights[parg->section];
	coll->illum = 0.0;
	coll->phong = 0.0;
	while (l_node)
	{
		l = (t_light_node *)(l_node->content);
		cos = ft_vectors_cos(coll->norm,
			ft_vectornew(coll->coll_pnt, l->light->origin));
		if (cos > 0 && !ft_iscollide(parg->e->scn, coll->coll_pnt,
			ft_unitvectornew(coll->coll_pnt, l->light->origin),
			l->light->origin))
		{
			l->is_visible = 1;
			cl_len = ft_get_dist(coll->coll_pnt, l->light->origin);
			coll->illum += (!cl_len) ?
				l->light->bright :
				l->light->bright * cos / (pow(cl_len / BRIGHT_UNIT, 2));

//			printf("distance: %-16.6f; cosine: %-16.6f; result: %3d;\n",
//				cl_len, cos, res[1]);

			if (coll->illum >= 1.0)
				break;
		}
		l_node = l_node->next;
	}
	coll->illum = ft_limitf(0.0, 1.0, coll->illum);
}
