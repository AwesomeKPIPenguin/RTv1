/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 13:25:05 by domelche          #+#    #+#             */
/*   Updated: 2018/08/23 13:26:14 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_get_coll_pnts_cyl(t_cone *cone, t_point3 (*pnt)[4])
{
	t_point3	a;
	double		s;
	double		dist;

	a = ft_3_line_line_inter((*pnt)[0], (*pnt)[1], cone->base, cone->bv);
	if ((dist = ft_3_line_point_dist(cone->base, cone->bv, a)) >
		cone->base_rad ||
			ft_3_vector_cos((*pnt)[1], ft_3_vectornew((*pnt)[0], a)) < 0)
		return (ft_set_coll_pnts_null(pnt));
	s = cone->base_rad * sqrt(1 - pow(dist / cone->base_rad, 2)) /
		sqrt(1 - pow(ft_3_vector_cos(cone->bv, (*pnt)[1]), 2));
	(*pnt)[0] = ft_3_add_vector(a, ft_3_vector_scale((*pnt)[1], -s));
	(*pnt)[1] = ft_3_add_vector(a, ft_3_vector_scale((*pnt)[1], s));
}

void	ft_get_coll_pnts(t_cone *cone, t_point3 (*pnt)[4], int is_cyl)
{
	double		cos_t_2;
	t_point3	v_co[2];
	double		dv_dot;
	double		cov_dot;
	double		res[3];

	if (is_cyl)
		return (ft_get_coll_pnts_cyl(cone, pnt));
	v_co[0] = ft_3_vector_scale(cone->bv, -1.0);
	cos_t_2 = pow(cone->bv_dist / sqrt(pow(cone->base_rad - cone->vert_rad, 2) +
		pow(cone->bv_dist, 2)), 2);
	v_co[1] = ft_3_vectornew(cone->main_vert, (*pnt)[0]);
	dv_dot = ft_3_vector_dot((*pnt)[1], v_co[0]);
	cov_dot = ft_3_vector_dot(v_co[1], v_co[0]);
	ft_solve_sqr(pow(dv_dot, 2) - cos_t_2,
		2 * (dv_dot * cov_dot - ft_3_vector_dot((*pnt)[1], v_co[1]) * cos_t_2),
		pow(cov_dot, 2) - ft_3_vector_dot(v_co[1], v_co[1]) * cos_t_2, &res);
	if (res[0] == 0.0)
		return (ft_set_coll_pnts_null(pnt));
	v_co[0] = (*pnt)[0];
	(*pnt)[0] = (res[1] < 0.0) ? ft_3_nullpointnew() :
				ft_3_add_vector(v_co[0], ft_3_vector_scale((*pnt)[1], res[1]));
	(*pnt)[1] = (res[2] < 0.0) ? ft_3_nullpointnew() :
				ft_3_add_vector(v_co[0], ft_3_vector_scale((*pnt)[1], res[2]));
}

void	ft_is_between_planes(t_point3 (*pnt)[4], t_point3 base, t_point3 vert)
{
	t_point3	bv;
	t_point3	vb;

	bv = ft_3_vectornew(base, vert);
	vb = ft_3_vector_scale(bv, -1);
	if (ft_3_isnullpoint((*pnt)[0]) ||
			ft_3_vector_cos(bv, ft_3_vectornew(base, (*pnt)[0])) < 0 ||
			ft_3_vector_cos(vb, ft_3_vectornew(vert, (*pnt)[0])) < 0)
		(*pnt)[0] = ft_3_nullpointnew();
	if (ft_3_isnullpoint((*pnt)[1]) ||
			ft_3_vector_cos(bv, ft_3_vectornew(base, (*pnt)[1])) < 0 ||
			ft_3_vector_cos(vb, ft_3_vectornew(vert, (*pnt)[1])) < 0)
		(*pnt)[1] = ft_3_nullpointnew();
}

void	ft_collide_cone_planes(t_cone *cone, t_point3 origin, t_point3 direct,
							t_point3 (*pnt)[4])
{
	(*pnt)[2] = ft_3_line_plane_inter(cone->base, cone->bv, origin, direct);
	if (ft_3_vector_cos(direct, ft_3_vectornew(origin, (*pnt)[2])) < 0 ||
		ft_3_point_point_dist(cone->base, (*pnt)[2]) > fabs(cone->base_rad))
		(*pnt)[2] = ft_3_nullpointnew();
	(*pnt)[3] = ft_3_line_plane_inter(cone->vert, cone->bv, origin, direct);
	if (ft_3_vector_cos(direct, ft_3_vectornew(origin, (*pnt)[3])) < 0 ||
		ft_3_point_point_dist(cone->vert, (*pnt)[3]) > fabs(cone->vert_rad))
		(*pnt)[3] = ft_3_nullpointnew();
}

t_point3	ft_get_closest(t_point3 cam, t_point3 pnt[4])
{
	double		dist;
	double		tmp;
	t_point3	res;
	int			i;

	dist = -1;
	res = ft_3_nullpointnew();
	i = -1;
	while (++i < 4)
	{
		if (ft_3_isnullpoint(pnt[i]))
			continue ;
		tmp = ft_3_point_point_dist(cam, pnt[i]);
		if (dist < 0 || tmp < dist)
		{
			dist = tmp;
			res = pnt[i];
		}
	}
	return (res);
}
