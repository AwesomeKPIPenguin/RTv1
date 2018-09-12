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

void	ft_get_t(t_cone *cone, t_point (*pnt)[4], double (*t)[3], int is_cyl)
{
//	t_point		tmp_pnt[3];
//	double		cos_t;
//	double		tan_[2];
//
//	if (is_cyl)
//		return (ft_get_t_cyl(cone, pnt, t));
//	tmp_pnt[1] = ft_add_vector(cone->base, ft_scale_vector(
//		cone->bv, -(cone->base_rad * cone->bv_dist) /
//			(cone->vert_rad * (1.0 - cone->base_rad / cone->vert_rad))));
//	tmp_pnt[0] = ft_tounitvector(ft_mul_vector_v((*pnt)[1], ft_vectornew((*pnt)[0],
//		tmp_pnt[1])));
//	tmp_pnt[2] = ft_scale_vector(cone->bv, -1.0);
//	cos_t = sqrt(1 - pow(ft_mul_vector_s(tmp_pnt[0], tmp_pnt[2]), 2));
//	tan_[0] = cone->base_rad / ft_get_dist(tmp_pnt[1], cone->base);
//	tan_[1] = tan(acos(cos_t));
//	if (cos_t < cos(atan(tan_[0])))
//	{
//		(*t)[0] = 0.0;
//		return ;
//	}
//
//	cos_t = cos(atan(tan_[0]));
//
//	ft_get_t_cone(tmp_pnt, pnt, t, tan_);


	t_point		c;
	t_point		c_proj;
	t_point		n;
	double		dist;
	double		r;
	double		shift;

	c = ft_line_line_closest((*pnt)[0], (*pnt)[1], cone->base, cone->bv);
	c_proj = ft_project_point(cone->base, cone->bv, c);
	r = (is_cyl) ? cone->base_rad : (cone->base_rad - cone->vert_rad) /
			cone->bv_dist * ft_get_dist(c_proj, cone->base);
	dist = ft_get_dist(c, c_proj);
	if (dist > r)
	{
		(*t)[0] = 0.0;
		return ;
	}
	else if (dist == r)
	{
		(*t)[0] = 1.0;
		(*t)[1] = ft_get_dist((*pnt)[0], c);
		(*t)[2] = (*t)[1];
	}
	n = ft_tounitvector(ft_mul_vector_v(ft_vectornew(c, c_proj), cone->bv));
	shift = r * sqrt(1 - pow(dist / cone->base_rad, 2)) /
			sqrt(1 - pow(ft_vectors_cos(cone->bv, (*pnt)[1]), 2));
}

void	ft_is_between_planes(t_point (*pnt)[4], t_point base, t_point vert)
{
	t_point	bv;
	t_point	vb;

	bv = ft_vectornew(base, vert);
	vb = ft_scale_vector(bv, -1);
	if (ft_vectors_cos(bv, ft_vectornew(base, (*pnt)[0])) < 0 ||
		ft_vectors_cos(vb, ft_vectornew(vert, (*pnt)[0])) < 0)
		(*pnt)[0] = ft_null_pointnew();
	if (ft_vectors_cos(bv, ft_vectornew(base, (*pnt)[1])) < 0 ||
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
