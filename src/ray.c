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
	double			phong_tmp;
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
		phong_tmp = coll.o->phong * lnode->light->bright *
			pow((30.0 - len), 2) * BRIGHT_UNIT * /* some_const */ 255.0 /
			ft_get_dist(coll.coll_pnt, lnode->light->origin);

//		printf("phong_tmp: %12.4f;\n", phong_tmp);

		phong = MAX(phong, phong_tmp);
		node = node->next;
	}
	return (phong);
}

static t_color	ft_throw_ray(t_parg *parg, t_object *o,
							   t_point od[2], int depth)
{
//	printf("in ft_throw_ray      (%15.6f, %15.6f, %15.6f) -> (%15.6f, %15.6f, %15.6f);\n",
//		origin.x, origin.y, origin.z, direct.x, direct.y, direct.z);

	t_coll		coll;
	t_color		spclr_col;
	t_color		trans_col;
	double		num[2];


	spclr_col.val = 0;
	trans_col.val = 0;
	coll = ft_get_collision(parg, od[0], od[1], o);
	if (!coll.o)
		return (parg->e->scn->bg_color);
	od[0] = coll.coll_pnt;
	num[1] = depth;
	if (coll.o->spclr && depth < DEPTH)
	{
		od[1] = coll.spclr_vec;
		num[0] = coll.o->s_blur;
		spclr_col = (coll.o->s_blur) ?
			ft_throw_rays(parg, coll, &(coll.spclr_vec), num) :
			ft_throw_ray(parg, coll.o, od, depth + 1);

//		printf("spclr_col: %#6X;\n", spclr_col.val);
	}
	if (coll.o->trans && depth < DEPTH)
	{
		od[1] = coll.trans_vec;
		num[0] = coll.o->t_blur;
		trans_col = (coll.o->t_blur) ?
			ft_throw_rays(parg, coll, &(coll.trans_vec), num) :
			ft_throw_ray(parg, coll.o, od, depth + 1);
	}
	if (coll.o->phong != 0.0)
		spclr_col = ft_apply_a(spclr_col, ft_get_phong(parg, coll));
	return (ft_sum_colors(coll, spclr_col, trans_col));
}

t_color			ft_throw_rays(t_parg *parg, t_coll coll, t_point *vec,
								double num[2])
{
	double		max_angle;
	int			rays;
	int			i;
	t_color		color[2];
	t_point		od[2];

	max_angle = ft_torad(num[0] * 10.0);
	rays = ft_limit(1, 10, (int)(sin(max_angle) * 10.0));
	i = -1;
	color[1].val = 0;
	*vec = ft_change_blur_vec(coll.norm, *vec, max_angle);
	while (++i < rays)
	{
		od[0] = coll.coll_pnt;
		od[1] = ft_turn_vector(ft_get_blur_proj(coll.coll_pnt, *vec),
			*vec, (double)rand() / (double)RAND_MAX * max_angle);
		color[0] = ft_throw_ray(parg, coll.o, od, (int)(num[1] + 1));
		color[1] = (i) ? ft_add_color(color[1], color[0]) : color[0];
	}
	return (color[1]);
}

t_color			ft_trace_ray(t_parg *parg, int x, int y)
{
	t_color		res;
	t_point		od[2];
//		double		half_diag;

	od[0] = parg->e->scn->cam->origin;
	od[1] = parg->e->scn->cam->vs_start_point;
	od[1] = ft_add_vector(od[1],
		ft_scale_vector(parg->e->scn->cam->vs_x_step_vec, x));
	od[1] = ft_add_vector(od[1],
		ft_scale_vector(parg->e->scn->cam->vs_y_step_vec, y));
	od[1] = ft_unitvectornew(parg->e->scn->cam->origin, od[1]);
	res = ft_throw_ray(parg, NULL, od, 0);
//	if (res.val < 0)
//	{
//		half_diag = sqrt(pow(WIN_WIDTH / 2.0, 2) + pow(WIN_HEIGHT / 2.0, 2));
//		res = ft_apply_a(e->scn->bg_color, 127.0 + ft_get_dist(
//				ft_pointnew(WIN_WIDTH / 2.0, WIN_HEIGHT / 2.0, 0.0),
//				ft_pointnew(x, y, 0.0)) / half_diag * 30.0);
//	}
	return (res);
}
