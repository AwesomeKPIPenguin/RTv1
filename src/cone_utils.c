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

void	ft_get_t(t_cone *cone, t_point pnt[4], double (*t)[3], int is_cyl)
{
	t_point		n;
	t_point		v;
	t_point		vb;
	t_point		uvw[3];
	t_point		delta[2];
	t_point		tmp;
	double		cos_t;
	double		tan_a;
	double		tan_t;

	v = (is_cyl) ? ft_null_pointnew() :
		ft_add_vector(cone->base, ft_scale_vector(
			cone->bv, -(cone->base_rad * cone->bv_dist) /
				(cone->vert_rad * (1.0 - cone->base_rad / cone->vert_rad))));
	n = ft_tounitvector(ft_mul_vector_v(pnt[1],
		ft_vectornew(pnt[0], cone->vert)));
	vb = ft_scale_vector(cone->bv, -1.0);
	cos_t = sqrt(1 - pow(ft_mul_vector_s(n, vb), 2));
	tan_a = (is_cyl) ? 0.0 : cone->base_rad / ft_get_dist(v, cone->base);
	tan_t = tan(acos(cos_t));
	if ((is_cyl) ? ft_linetoline_dist(cone->base, cone->bv, pnt[0], pnt[1]) >
			cone->base_rad :
		cos_t < cos(atan(tan_a)))
	{
		(*t)[0] = 0.0;
		return ;
	}
	uvw[0] = ft_tounitvector(ft_mul_vector_v(vb, n));
	uvw[1] = vb;
	uvw[2] = ft_mul_vector_v(uvw[0], uvw[1]);
	delta[0] = ft_add_vector(uvw[1], ft_scale_vector(uvw[2], tan_t));
	delta[1] = delta[0];
	tmp = ft_scale_vector(uvw[0], sqrt(pow(tan_a, 2) - pow(tan_t, 2)));
	delta[0] = ft_add_vector(delta[0], tmp);
	delta[1] = ft_add_vector(delta[1], ft_scale_vector(tmp, -1.0));
	(*t)[0] = 1.0;
	tmp = ft_mul_vector_v(pnt[1], delta[0]);
	(*t)[1] = ft_mul_vector_s(
			ft_mul_vector_v(ft_vectornew(pnt[0], v), delta[0]), tmp) /
		pow(ft_vector_len(tmp), 2);
	tmp = ft_mul_vector_v(pnt[1], delta[1]);
	(*t)[2] = ft_mul_vector_s(
			ft_mul_vector_v(ft_vectornew(pnt[0], v), delta[1]), tmp) /
		pow(ft_vector_len(tmp), 2);
}

void	ft_is_between_planes(t_point (*pnt)[4], t_point base, t_point vert)
{
	t_point	bv;
	t_point	vb;

	bv = ft_vectornew(base, vert);
	vb = ft_scale_vector(bv, -1);
	if (ft_vectors_cos(bv, ft_vectornew(base, *pnt[0])) < 0 ||
		ft_vectors_cos(vb, ft_vectornew(vert, *pnt[0])) < 0)
		*pnt[0] = ft_null_pointnew();
	if (ft_vectors_cos(bv, ft_vectornew(base, *pnt[1])) < 0 ||
		ft_vectors_cos(vb, ft_vectornew(vert, *pnt[1])) < 0)
		*pnt[1] = ft_null_pointnew();
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
	(*pnt)[3] = ft_collide_plane((void *)(pln[1]), origin, direct);
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
