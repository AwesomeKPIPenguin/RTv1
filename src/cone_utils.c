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

void	ft_get_angles(t_cone *cone, double (*ang)[2])
{
	t_point		vec;

	vec = ft_vectornew(cone->base, cone->vert);
	if (vec.x == 0.0 && vec.z == 0.0)
		(*ang)[0] = M_PI_2;
	else
		(*ang)[0] = (vec.z == 0.0) ? 0.0 :
			acos(ft_vectors_cos(ft_pointnew(vec.x, 0, vec.z),
								ft_pointnew(1.0, 0.0, 0.0)));
	if (vec.y == 0.0 && vec.z == 0.0)
		(*ang)[1] = M_PI_2;
	else
		(*ang)[1] = (vec.z == 0.0) ? 0.0 :
			acos(ft_vectors_cos(ft_pointnew(0, vec.y, vec.z),
								ft_pointnew(0.0, 1.0, 0.0)));
}

void	ft_get_t(t_cone *cone, t_point pnt[4], double (*t)[3])
{
	t_point		n;
	t_point		v;

	v = ft_add_vector(cone->base, ft_scale_vector(
		cone->bv, -(cone->base_rad * cone->bv_dist) /
			(cone->vert_rad * (1.0 - cone->base_rad / cone->vert_rad))));
	n = ft_mul_vector_v(pnt[1], ft_vectornew(pnt[0], v));
	
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
