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

t_point		ft_pointnew(double x, double y, double z)
{
	t_point	point;
	
	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

t_point		ft_null_pointnew(void)
{
	return (ft_pointnew(DBL_MIN, DBL_MIN, DBL_MIN));
}

int			ft_isnullpoint(t_point point)
{
	return ((point.x == DBL_MIN && point.y == DBL_MIN && point.z == DBL_MIN) ?
		1 : 0);
}

t_point		ft_atopoint(char *str)
{
	t_point		point;
	
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

double		ft_get_dist(t_point pnt_0, t_point pnt_1)
{
	return (sqrt(pow(pnt_1.x - pnt_0.x, 2) +
				pow(pnt_1.y - pnt_0.y, 2) +
				pow(pnt_1.z - pnt_0.z, 2)));
}

double		ft_linetopoint_dist(t_point origin, t_point direct, t_point point)
{
	t_point		po;

	po = ft_pointnew(origin.x - point.x, origin.y - point.y,
					 origin.z - point.z);
	return (ft_vector_len(ft_mul_vector_v(direct, po)) / ft_vector_len(direct));
}

double		ft_planetopoint_dist(t_point origin, t_point norm, t_point point)
{
	return (norm.x * (point.x - origin.x) + norm.y * (point.y - origin.y) +
		norm.z * (point.z - origin.z)) / ft_vector_len(norm);
}

t_point		ft_project_point(t_point origin, t_point direct, t_point point)
{
	t_plane		*pln;

	pln = ft_planenew();
	pln->origin = point;
	pln->norm = direct;
	return (ft_collide_plane((void *)pln, origin, direct));
}

int			ft_pointcmp(t_point pnt_0, t_point pnt_1)
{
	return (fabs(pnt_0.x - pnt_1.x) < PRECISION &&
			fabs(pnt_0.y - pnt_1.y) < PRECISION &&
			fabs(pnt_0.z - pnt_1.z) < PRECISION);
}
