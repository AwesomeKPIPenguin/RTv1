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

void	ft_get_t(t_cone *cone, double ang[2], t_point pnt[4], double (*t)[3])
{
	double	ctg;
	double	a[3];
	double	b[3];

	ctg = ft_get_dist(cone->base, cone->vert) /
		  (cone->base_rad - cone->vert_rad);
	a[0] = pnt[1].x * cos(ang[1]) + pnt[1].y * sin(ang[0]) * sin(ang[1]) +
		   pnt[1].z * cos(ang[0]) * sin(ang[1]);
	a[1] = -pnt[1].x * sin(ang[1]) + pnt[1].y * sin(ang[0]) * cos(ang[1]) +
		   pnt[1].z * cos(ang[0]) * cos(ang[1]);
	a[2] = (pnt[1].y * cos(ang[0]) - pnt[1].z * sin(ang[0])) / ctg;
	b[0] = pnt[0].x * cos(ang[1]) + pnt[0].y * sin(ang[0]) * sin(ang[1]) +
		   pnt[0].z * cos(ang[0]) * sin(ang[1]);
	b[1] = -pnt[0].x * sin(ang[1]) + pnt[0].y * sin(ang[0]) * cos(ang[1]) +
		   pnt[0].z * cos(ang[0]) * cos(ang[1]);
	b[2] = (pnt[0].y * cos(ang[0]) - pnt[0].z * sin(ang[0])) / ctg;
	ft_solve_sqr(pow(a[0], 2) + pow(a[1], 2) + pow(a[2], 2),
				 a[0] * b[0] + a[1] * b[1] + a[2] * b[2],
				 pow(b[0], 2) + pow(b[1], 2) + pow(b[2], 2), t);
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
	*pnt[2] = ft_collide_plane((void *)(pln[0]), origin, direct);
	*pnt[3] = ft_collide_plane((void *)(pln[1]), origin, direct);
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
			dist = tmp;
	}
	return (res);
}
