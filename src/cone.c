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

	obj = ft_parse_object(attr);
	obj->ft_collide = ft_collide_cone;
	obj->ft_is_reachable = ft_is_reachable_cone;
	obj->ft_get_norm = ft_get_norm_cone;
	cone = ft_conenew();
	attr = ft_get_curve(attr, '{');
	ft_get_attr_in_scope(attr, "base:", (void *)(&(cone->base)), PNT);
	ft_get_attr_in_scope(attr, "base_rad:", (void *)(&(cone->base_rad)), DBL);
	ft_get_attr_in_scope(attr, "vert:", (void *)(&(cone->vert)), PNT);
	ft_get_attr_in_scope(attr, "vert_rad:", (void *)(&(cone->vert_rad)), DBL);
	obj->fig = cone;
	cone->bv_dist = ft_3_point_point_dist(cone->base, cone->vert);
	cone->base = ft_3_add_vector(cone->base, obj->translate);
	cone->bv = ft_3_rotate_vector(ft_unitvector3new(cone->base, cone->vert),
								  obj->rotate.x, obj->rotate.y, obj->rotate.z);
	cone->vert = ft_3_add_vector(cone->base,
								 ft_3_vector_scale(cone->bv, cone->bv_dist));
	cone->side_norm_angle = acos((cone->bv_dist * sin(atan((cone->base_rad -
		cone->vert_rad) / cone->bv_dist))) / (cone->base_rad - cone->vert_rad));
	cone->main_vert = ft_3_add_vector(cone->base, ft_3_vector_scale(cone->bv,
																	cone->base_rad *
																	cone->bv_dist /
																	(cone->base_rad -
																	 cone->vert_rad)));
	ft_lstpush(&(scn->objs), ft_nodenew((void *)obj, sizeof(obj)));
	return (ft_get_curve(attr, '}'));
}

int		ft_is_reachable_cone(void *fig, t_point3 origin, t_point3 direct)
{
	t_cone		*cone;
	t_point3		proj;
	int			is_between;

	cone = (t_cone *)fig;
	if (ft_3_vector_cos(direct, ft_vector3new(origin, cone->base)) > 0 ||
			ft_3_vector_cos(direct, ft_vector3new(origin, cone->vert)) > 0)
		return (1);
	proj = ft_3_line_point_proj(cone->base, cone->bv, origin);
	is_between = ft_3_point_point_dist(proj, cone->base) +
						 ft_3_point_point_dist(proj, cone->vert) == cone->bv_dist;
	if (is_between && ft_3_line_point_dist(cone->base, cone->vert, origin) <
			cone->base_rad * ((ft_3_point_point_dist(cone->base, origin) *
					ft_3_vector_cos(ft_vector3new(cone->base, origin),
									ft_vector3new(cone->base, cone->vert))) / cone->bv_dist))
		return (1);
	return (0);
}

t_point3		ft_collide_cone(void *fig, t_point3 origin, t_point3 direct)
{
	t_cone	*cone;
	t_point3	pnt[4];

	cone = (t_cone *)fig;
	pnt[0] = origin;
	pnt[1] = direct;
	ft_get_coll_pnts(cone, &pnt, cone->base_rad == cone->vert_rad);
	ft_is_between_planes(&pnt, cone->base, cone->vert);
	ft_collide_cone_planes(cone, origin, direct, &pnt);
	return (ft_get_closest(origin, pnt));
}

t_point3		ft_get_norm_cone(void *fig, t_point3 coll)
{
	t_cone		*cone;
	t_point3		proj;
	double		sign;

	cone = (t_cone *)fig;
	proj = ft_3_line_point_proj(cone->base, cone->bv, coll);
	if (ft_point3cmp(proj, cone->base, 1e-3))
		return (ft_3_vector_scale(cone->bv, -1));
	if (ft_point3cmp(proj, cone->vert, 1e-3))
		return (cone->bv);
	if (cone->base_rad == cone->vert_rad)
		return (ft_unitvector3new(proj, coll));
	sign = (cone->base_rad > cone->vert_rad) ? 1.0 : -1.0;
	sign *= (ft_3_vector_cos(ft_vector3new(cone->main_vert, cone->base),
							 ft_vector3new(cone->main_vert, proj)) < 0) ? -1.0 : 1.0;
	return (ft_tounitvector3(ft_3_turn_vector(cone->bv,
											  ft_unitvector3new(proj, coll),
											  sign * cone->side_norm_angle)));
}
