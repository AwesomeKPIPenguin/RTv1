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

#include "../rtv1.h"

void	ft_get_t_cyl(t_cone *cone, t_point (*pnt)[4], double (*t)[3])
{
	t_point		a;
	double		s;
	double		dist;
	double		oa_dist;

	a = ft_line_line_closest((*pnt)[0], (*pnt)[1], cone->base, cone->bv);

//	printf("a: (%f, %f, %f);\n", a.x, a.y, a.z);

	if ((dist = ft_linetopoint_dist(cone->base, cone->bv, a)) >
		cone->base_rad || ft_vectors_cos((*pnt)[1], ft_vectornew((*pnt)[0], a)) < 0)
	{
		(*t)[0] = 0.0;
		return ;
	}
	s = cone->base_rad * sqrt(1 - pow(dist / cone->base_rad, 2)) /
		sqrt(1 - pow(ft_vectors_cos(cone->bv, (*pnt)[1]), 2));
	oa_dist = ft_get_dist((*pnt)[0], a);
	(*t)[0] = 1.0;
	(*t)[1] = oa_dist - s;
	(*t)[2] = oa_dist + s;
}

//void	ft_get_t_cone(t_point tmp_pnt[3], t_point (*pnt)[4], double (*t)[3],
//						double tan_[2])
//{
//	t_point		uvw[3];
//	t_point		delta[2];
//	t_point		tmp;
//
//	uvw[0] = ft_tounitvector(ft_mul_vector_v(tmp_pnt[2], tmp_pnt[0]));
//	uvw[1] = tmp_pnt[2];
//	uvw[2] = ft_mul_vector_v(uvw[0], uvw[1]);
//	delta[0] = ft_add_vector(uvw[1], ft_scale_vector(uvw[2], tan_[1]));
//	delta[1] = delta[0];
//	tmp = ft_scale_vector(uvw[0], sqrt(pow(tan_[0], 2) - pow(tan_[1], 2)));
//	delta[0] = ft_add_vector(delta[0], tmp);
//	delta[1] = ft_add_vector(delta[1], ft_scale_vector(tmp, -1.0));
//	(*t)[0] = 1.0;
//	tmp = ft_mul_vector_v((*pnt[1]), delta[0]);
//	(*t)[1] = ft_mul_vector_s(
//		ft_mul_vector_v(ft_vectornew((*pnt[0]), tmp_pnt[1]), delta[0]), tmp) /
//			pow(ft_vector_len(tmp), 2);
//	tmp = ft_mul_vector_v((*pnt[1]), delta[1]);
//	(*t)[2] = ft_mul_vector_s(
//		ft_mul_vector_v(ft_vectornew((*pnt[0]), tmp_pnt[1]), delta[1]), tmp) /
//			pow(ft_vector_len(tmp), 2);
//}

/*
**	tmp_pnt[0] - n;
**	tmp_pnt[1] - V;
**	tmp_pnt[2] - vb;
*/

void	ft_get_coll_pnts(t_cone *cone, t_point (*pnt)[4], int is_cyl)
{
//	t_point		c;
//	t_point		c_proj;
//	t_point		v;
//	t_point		vc;
//	t_point		direct;
//	double		dist;
//	double		r;
//	double		shift;
//
//	c = ft_line_line_closest((*pnt)[0], (*pnt)[1], cone->base, cone->bv);
//	c_proj = ft_project_point(cone->base, cone->bv, c);
//	if (!is_cyl)
//		v = ft_add_vector(cone->base, ft_scale_vector(cone->bv, cone->base_rad *
//			cone->bv_dist / (cone->base_rad - cone->vert_rad)));
//	r = (is_cyl) ? cone->base_rad : (cone->base_rad - cone->vert_rad) /
//		cone->bv_dist * ft_get_dist(c_proj, v);
//	dist = ft_get_dist(c, c_proj);
//	direct = (*pnt)[1];
//	if (dist > r)
//	{
//		(*pnt)[0] = ft_null_pointnew();
//		(*pnt)[1] = (*pnt)[0];
//		return ;
//	}
//	else if (dist == r)
//	{
//		(*pnt)[0] = c;
//		(*pnt)[1] = ft_null_pointnew();
//		return ;
//	}
//	shift = sqrt(pow(r, 2) - pow(dist, 2)) /
//			sqrt(1 - pow(ft_vectors_cos(cone->bv, (*pnt)[1]), 2));
//	(*pnt)[0] = ft_add_vector(c, ft_scale_vector((*pnt)[1], -shift));
//	(*pnt)[1] = ft_add_vector(c, ft_scale_vector((*pnt)[1], shift));
//	if (is_cyl)
//		return ;
//	if (ft_get_dist(v, (*pnt)[0]) > ft_get_dist(v, (*pnt)[1]))
//	{
//		(*pnt)[2] = (*pnt)[0];
//		(*pnt)[0] = (*pnt)[1];
//		(*pnt)[1] = (*pnt)[2];
//	}
//	shift = ft_planetopoint_dist(c_proj, cone->bv, (*pnt)[0]);
//	vc = ft_unitvectornew(v, c_proj);
//	(*pnt)[0] = ft_add_vector((*pnt)[0], ft_scale_vector(vc, shift));
//	(*pnt)[1] = ft_add_vector((*pnt)[1], ft_scale_vector(vc, -shift));
//	(*pnt)[0] = ft_line_line_closest(c, direct,
//		v, ft_unitvectornew(v, (*pnt)[0]));
//	(*pnt)[1] = ft_line_line_closest(c, direct,
//		v, ft_unitvectornew(v, (*pnt)[1]));



	double		cos_t_2;
	t_point		c;
	t_point		v;
	t_point		co;
	t_point		coll[2];
	double		dv_dot;
	double		cov_dot;
	double		res[3];

	(void)is_cyl;

	//if (!is_cyl)
		c = ft_add_vector(cone->base, ft_scale_vector(cone->bv, cone->base_rad *
			cone->bv_dist / (cone->base_rad - cone->vert_rad)));
	v = ft_scale_vector(cone->bv, -1.0);
	cos_t_2 = pow(cone->bv_dist / sqrt(pow(cone->base_rad - cone->vert_rad, 2) +
		pow(cone->bv_dist, 2)), 2);
	co = ft_vectornew(c, (*pnt)[0]);
	dv_dot = ft_mul_vector_s((*pnt)[1], v);
	cov_dot = ft_mul_vector_s(co, v);
	ft_solve_sqr(pow(dv_dot, 2) - cos_t_2,
		2 * (dv_dot * cov_dot - ft_mul_vector_s((*pnt)[1], co) * cos_t_2),
		pow(cov_dot, 2) - ft_mul_vector_s(co, co) * cos_t_2, &res);
	coll[0] = ft_null_pointnew();
	coll[1] = ft_null_pointnew();
	if (res[0])
	{
		coll[0] = ft_add_vector((*pnt)[0], ft_scale_vector((*pnt)[1], res[1]));
		coll[1] = ft_add_vector((*pnt)[0], ft_scale_vector((*pnt)[1], res[2]));
	}
	(*pnt)[0] = coll[0];
	(*pnt)[1] = coll[1];
}

void	ft_is_between_planes(t_point (*pnt)[4], t_point base, t_point vert)
{
	t_point	bv;
	t_point	vb;

	bv = ft_vectornew(base, vert);
	vb = ft_scale_vector(bv, -1);
	if (ft_isnullpoint((*pnt)[0]) ||
		ft_vectors_cos(bv, ft_vectornew(base, (*pnt)[0])) < 0 ||
		ft_vectors_cos(vb, ft_vectornew(vert, (*pnt)[0])) < 0)
		(*pnt)[0] = ft_null_pointnew();
	if (ft_isnullpoint((*pnt)[1]) ||
		ft_vectors_cos(bv, ft_vectornew(base, (*pnt)[1])) < 0 ||
		ft_vectors_cos(vb, ft_vectornew(vert, (*pnt)[1])) < 0)
		(*pnt)[1] = ft_null_pointnew();
}

void	ft_collide_cone_planes(t_cone *cone, t_point origin, t_point direct,
							t_point (*pnt)[4])
{
	t_plane		*pln[2];
	t_point		norm;

	pln[0] = ft_planenew();
	pln[1] = ft_planenew();
	norm = ft_vectornew(cone->base, cone->vert);
	pln[0]->norm = norm;
	pln[0]->origin = cone->base;
	pln[1]->norm = norm;
	pln[1]->origin = cone->vert;
	(*pnt)[2] = ft_collide_plane((void *)(pln[0]), origin, direct);
	if (ft_linetopoint_dist(cone->base, cone->bv, (*pnt)[2]) > cone->base_rad)
		(*pnt)[2] = ft_null_pointnew();
	(*pnt)[3] = ft_collide_plane((void *)(pln[1]), origin, direct);
	if (ft_linetopoint_dist(cone->base, cone->bv, (*pnt)[3]) > cone->vert_rad)
		(*pnt)[3] = ft_null_pointnew();
}

t_point	ft_get_closest(t_point cam, t_point pnt[4])
{
	double	dist;
	double	tmp;
	t_point	res;
	int		i;

	dist = -1;
	res = ft_null_pointnew();
	i = -1;
	while (++i < 4)
	{
		if (ft_isnullpoint(pnt[i]))
			continue ;
		tmp = ft_get_dist(cam, pnt[i]);
		if (dist < 0 || tmp < dist)
		{
			dist = tmp;
			res = pnt[i];
		}
	}
	return (res);
}
