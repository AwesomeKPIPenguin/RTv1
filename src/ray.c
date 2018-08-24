/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 13:25:05 by domelche          #+#    #+#             */
/*   Updated: 2018/08/23 13:25:05 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

static double	ft_get_phong(t_parg *parg, t_coll coll)
{
	double			phong;
	t_list			*node;
	t_light_node	*lnode;
	double			len;

	phong = 0;
	node = parg->e->scn->lights[parg->section];
	len = 0;
	while (node)
	{
		lnode = (t_light_node *)(node->content);
		if (!lnode->is_visible || (len = ft_linetopoint_dist(coll.coll_pnt,
			coll.spclr_vec, lnode->light->origin)) > 30.0)
		{
			node = node->next;
			continue ;
		}
		phong = MAX(phong, coll.o->phong * lnode->light->bright *
			pow((30.0 - len), 2) * BRIGHT_UNIT * /* some_const */ 255.0 /
			ft_get_dist(coll.coll_pnt, lnode->light->origin));
		node = node->next;
	}
	return (phong);
}

static t_color	ft_throw_ray(t_parg *parg, t_object *o,
							   t_point origin, t_point direct)
{
//	printf("in ft_throw_ray      (%15.6f, %15.6f, %15.6f) -> (%15.6f, %15.6f, %15.6f);\n",
//		origin.x, origin.y, origin.z, direct.x, direct.y, direct.z);

	t_coll		coll;
	t_color		spclr_col;
	t_color		trans_col;

	spclr_col.val = 0;
	trans_col.val = 0;
	coll = ft_get_collision(parg, origin, direct, o);
	if (!coll.o)
		return (parg->e->scn->bg_color);
	if (coll.o->spclr)
		spclr_col = (o->s_blur) ?
			ft_throw_rays(parg, coll, &(coll.spclr_vec), o->s_blur) :
			ft_throw_ray(parg, coll.o, coll.coll_pnt, coll.spclr_vec);
	if (coll.o->trans)
		trans_col = (o->t_blur) ?
			ft_throw_rays(parg, coll, &(coll.trans_vec), o->t_blur) :
			ft_throw_ray(parg, coll.o, coll.coll_pnt, coll.trans_vec);
	if (coll.o->phong != 0.0)
		spclr_col = ft_apply_a(spclr_col, ft_get_phong(parg, coll));
	return (ft_sum_colors(coll, spclr_col, trans_col));
}

t_color			ft_throw_rays(t_parg *parg, t_coll coll, t_point *vec, double k)
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
		color = ft_throw_ray(parg, coll.o, coll.coll_pnt,
			ft_turn_vector(ft_get_blur_proj(coll.coll_pnt, *vec), *vec,
				(double)rand() / (double)RAND_MAX * max_angle));
		res = (i) ? ft_add_color(res, color) : color;
	}
	return (res);
}

t_color			ft_trace_ray(t_parg *parg, int x, int y)
{
	t_color		res;
	t_point		vec;
//		double		half_diag;

	vec = parg->e->scn->cam->vs_start_point;
	vec = ft_add_vector(vec,
		ft_scale_vector(parg->e->scn->cam->vs_x_step_vec, x));
	vec = ft_add_vector(vec,
		ft_scale_vector(parg->e->scn->cam->vs_y_step_vec, y));
	vec = ft_unitvectornew(parg->e->scn->cam->origin, vec);
	res = ft_throw_ray(parg, NULL, parg->e->scn->cam->origin, vec);
//	if (res.val < 0)
//	{
//		half_diag = sqrt(pow(WIN_WIDTH / 2.0, 2) + pow(WIN_HEIGHT / 2.0, 2));
//		res = ft_apply_a(e->scn->bg_color, 127.0 + ft_get_dist(
//				ft_pointnew(WIN_WIDTH / 2.0, WIN_HEIGHT / 2.0, 0.0),
//				ft_pointnew(x, y, 0.0)) / half_diag * 30.0);
//	}
	return (res);
}
