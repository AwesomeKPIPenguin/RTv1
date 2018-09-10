/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 13:25:05 by domelche          #+#    #+#             */
/*   Updated: 2018/08/23 13:26:05 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

t_cone		*ft_conenew()
{
	t_cone	*cone;

	cone = ft_smemalloc(sizeof(t_cone), "ft_conenew");
	return (cone);
}

char		*ft_parse_cone(char *attr, t_scene *scn)
{
	t_object	*obj;
	t_cone		*cone;
	char		*ptr;

	obj = ft_parse_object(attr);
	obj->ft_collide = ft_collide_cone;
	obj->ft_is_reachable = ft_is_reachable_cone;
	obj->ft_get_norm = ft_get_norm_cone;
	cone = ft_conenew();
	attr = ft_get_curve(attr, '{');
	if ((ptr = ft_search_attr(attr, "base:", FTSA_IN_SCOPE)))
		ft_read_attr((void *)(&(cone->base)), ptr, POINT);
	if ((ptr = ft_search_attr(attr, "base_rad:", FTSA_IN_SCOPE)))
		ft_read_attr((void *)(&(cone->base_rad)), ptr, DOUBLE);
	if ((ptr = ft_search_attr(attr, "vert:", FTSA_IN_SCOPE)))
		ft_read_attr((void *)(&(cone->vert)), ptr, POINT);
	if ((ptr = ft_search_attr(attr, "vert_rad:", FTSA_IN_SCOPE)))
		ft_read_attr((void *)(&(cone->vert_rad)), ptr, DOUBLE);
	obj->fig = cone;
	cone->bv = ft_unitvectornew(cone->base, cone->vert);
	cone->bv_dist = ft_get_dist(cone->base, cone->vert);
	ft_lstpush(&(scn->objs), ft_nodenew((void *)obj, sizeof(obj)));
	return (ft_get_curve(attr, '}'));
}

int		ft_is_reachable_cone(void *fig, t_point origin, t_point direct)
{
	t_cone		*cone;
	t_point		proj;
	int			is_between;

	cone = (t_cone *)fig;
	if (ft_vectors_cos(direct, ft_vectornew(origin, cone->base)) > 0 ||
		ft_vectors_cos(direct, ft_vectornew(origin, cone->vert)) > 0)
		return (1);
	proj = ft_project_point(cone->base, cone->bv, origin);
	is_between = ft_get_dist(proj, cone->base) +
		ft_get_dist(proj, cone->vert) == cone->bv_dist;
	if (is_between && ft_linetopoint_dist(cone->base, cone->vert, origin) <
			cone->base_rad * ((ft_get_dist(cone->base, origin) *
			ft_vectors_cos(ft_vectornew(cone->base, origin),
			ft_vectornew(cone->base, cone->vert))) / cone->bv_dist))
		return (1);
	return (0);
}

t_point		ft_collide_cone(void *fig, t_point origin, t_point direct)
{
	t_cone	*cone;
	t_point	pnt[4];
	double	t[3];

	cone = (t_cone *)fig;
	pnt[0] = origin;
	pnt[1] = direct;
	ft_get_t(cone, pnt, &t, cone->base_rad == cone->vert_rad);
	if (!t[0])
		return (ft_null_pointnew());
	pnt[0] = ft_add_vector(origin, ft_scale_vector(direct, t[1]));
	pnt[1] = ft_add_vector(origin, ft_scale_vector(direct, t[2]));
	ft_is_between_planes(&pnt, cone->base, cone->vert);
	ft_collide_cone_planes(cone, origin, direct, &pnt);
	return (ft_get_closest(origin, pnt));
}

t_point		ft_get_norm_cone(void *fig, t_point coll)
{
	t_cone		*cone;
	t_point		proj;
	double		angle;

	cone = (t_cone *)fig;
	proj = ft_project_point(cone->base, cone->bv, coll);
	if (ft_pointcmp(proj, cone->base, 1e-3))
		return (ft_scale_vector(cone->bv, -1));
	if (ft_pointcmp(proj, cone->vert, 1e-3))
		return (cone->bv);
	if (cone->base_rad == cone->vert_rad)
		return (ft_unitvectornew(proj, coll));
	angle = atan(cone->bv_dist /
		(cone->vert_rad * (1 - cone->base_rad / cone->vert_rad)));
	return (ft_turn_vector(cone->bv, ft_unitvectornew(proj, coll), -angle));
}
