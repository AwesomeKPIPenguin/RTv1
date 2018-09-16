/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 13:25:05 by domelche          #+#    #+#             */
/*   Updated: 2018/08/23 13:27:31 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

t_point3	ft_point3new(double x, double y, double z)
{
	t_point3	point;
	
	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

t_point3	ft_null_point3new(void)
{
	return (ft_point3new(DBL_MIN, DBL_MIN, DBL_MIN));
}

int			ft_isnullpoint3(t_point3 point)
{
	return ((point.x == DBL_MIN && point.y == DBL_MIN && point.z == DBL_MIN) ?
		1 : 0);
}

t_point3	ft_atopoint3(char *str)
{
	t_point3		point;
	
	while (*str && *str != '(')
		++str;
	if (!*str)
		ft_error("invalid scene file");
	point.x = ft_atod(++str);
	while (*str && *str != ',')
		++str;
	if (!*str)
		ft_error("invalid scene file");
	point.y = ft_atod(++str);
	while (*str && *str != ',')
		++str;
	if (!*str)
		ft_error("invalid scene file");
	point.z = ft_atod(++str);
	while (*str && *str != ')')
		++str;
	if (!*str)
		ft_error("invalid scene file");
	return (point);
}

double		ft_3_point_point_dist(t_point3 pnt_0, t_point3 pnt_1)
{
	return (sqrt(pow(pnt_1.x - pnt_0.x, 2) +
				pow(pnt_1.y - pnt_0.y, 2) +
				pow(pnt_1.z - pnt_0.z, 2)));
}

double		ft_3_line_point_dist
				(t_point3 origin, t_point3 direct, t_point3 point)
{
	t_point3		po;

	po = ft_point3new(origin.x - point.x, origin.y - point.y,
					  origin.z - point.z);
	return (ft_vector_len(ft_3_vector_cross(direct, po)) / ft_vector_len(direct));
}

double		ft_3_plane_point_dist
				(t_point3 origin, t_point3 norm, t_point3 point)
{
	return (norm.x * (point.x - origin.x) + norm.y * (point.y - origin.y) +
		norm.z * (point.z - origin.z)) / ft_vector_len(norm);
}

double		ft_3_line_line_dist
				(t_point3 o1, t_point3 d1, t_point3 o2, t_point3 d2)
{
	t_point3	axb;

	axb = ft_3_vector_cross(d1, d2);
	return (fabs(ft_3_vector_dot(ft_3_add_vector(o2, ft_3_vector_scale(o1, -1)),
								 axb)) / ft_vector_len(axb));
}

t_point3	ft_3_line_line_inter
				(t_point3 o1, t_point3 d1, t_point3 o2, t_point3 d2)
{
	double	t;
	t_point3	den;
	double	len;

	den = ft_3_vector_cross(d1, d2);
	if ((len = ft_vector_len(den)) == 0.0)
		return (ft_null_point3new());
	t = ft_3_vector_dot(ft_3_vector_cross(ft_vector3new(o1, o2), d2), den) /
		pow(len, 2);

//	printf("t = %f;\n", t);

	return (ft_3_add_vector(o1, ft_3_vector_scale(d1, t)));
}

t_point3	ft_3_line_point_proj
				(t_point3 origin, t_point3 direct, t_point3 point)
{
	t_plane		*pln;
	t_point3		res;

	pln = ft_planenew();
	pln->origin = point;
	pln->norm = direct;
	res = ft_collide_plane((void *)pln, origin, direct);
	if (ft_isnullpoint3(res))
		res = ft_collide_plane((void *)pln, origin,
							   ft_3_vector_scale(direct, -1.0));
	return ((ft_isnullpoint3(res)) ? origin : res);
}

int			ft_point3cmp(t_point3 pnt_0, t_point3 pnt_1, double prec)
{
	return (ft_3_point_point_dist(pnt_0, pnt_1) < prec);
}
