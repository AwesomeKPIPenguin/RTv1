/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 13:25:05 by domelche          #+#    #+#             */
/*   Updated: 2018/08/23 13:25:05 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

t_sphere	*ft_spherenew()
{
	t_sphere	*sph;

	sph = ft_smemalloc(sizeof(t_sphere), "ft_spherenew");
	return (sph);
}

char		*ft_parse_sphere(char *attr, t_scene *scn)
{
	t_object	*obj;
	t_sphere	*sph;

	obj = ft_parse_object(attr);
	obj->ft_collide = ft_collide_sphere;
	obj->ft_is_reachable = ft_is_reachable_sphere;
	obj->ft_get_norm = ft_get_norm_sphere;
	sph = ft_spherenew();
	attr = ft_get_curve(attr, '{');
	ft_get_attr_in_scope(attr, "origin:", (void *)(&(sph->origin)), PNT);
	ft_get_attr_in_scope(attr, "radius:", (void *)(&(sph->radius)), DBL);
	sph->radius = ft_limitf(0.0, DBL_MAX, sph->radius);
	sph->origin = ft_3_add_vector(sph->origin, obj->translate);
	obj->fig = sph;
	ft_lstpush(&(scn->objs), ft_nodenew((void *)obj, sizeof(obj)));
	return (ft_get_curve(attr, '}'));
}

int			ft_is_reachable_sphere(void *fig, t_point3 origin, t_point3 direct)
{
	t_sphere	*sph;
	double		cos;

	sph = (t_sphere *)fig;
	if (ft_3_point_point_dist(origin, sph->origin) <= sph->radius)
		return (1);
	cos = ft_3_vector_cos(direct, ft_vector3new(origin, sph->origin));
	return ((cos > 0) ? 1 : 0);
}

t_point3		ft_collide_sphere(void *fig, t_point3 origin, t_point3 direct)
{
	t_sphere	*sph;
	double		dist;
	double		sqr_res[3];
	t_point3		coll_points[2];

	sph = (t_sphere *)fig;
	dist = ft_3_line_point_dist(origin, direct, sph->origin);
	if (dist > sph->radius)
		return (ft_null_point3new());
	ft_solve_sqr((pow(direct.x, 2) + pow(direct.y, 2) + pow(direct.z, 2)), 2.0 *
		(direct.x * (origin.x - sph->origin.x) +
		direct.y * (origin.y - sph->origin.y) +
		direct.z * (origin.z - sph->origin.z)),
		(pow(origin.x - sph->origin.x, 2) + pow(origin.y - sph->origin.y, 2) +
			pow(origin.z - sph->origin.z, 2) - pow(sph->radius, 2)),
		&sqr_res);
	if (!sqr_res[0])
		return (ft_null_point3new());
	coll_points[0] = ft_point3new(direct.x * sqr_res[1] + origin.x,
								  direct.y * sqr_res[1] + origin.y,
								  direct.z * sqr_res[1] + origin.z);
	coll_points[0] = (ft_point3cmp(ft_unitvector3new(origin, coll_points[0]),
								   direct, 1e-6)) ? coll_points[0] : ft_null_point3new();
	coll_points[1] = ft_point3new(direct.x * sqr_res[2] + origin.x,
								  direct.y * sqr_res[2] + origin.y,
								  direct.z * sqr_res[2] + origin.z);
	coll_points[1] = (ft_point3cmp(ft_unitvector3new(origin, coll_points[1]),
								   direct, 1e-6)) ? coll_points[1] : ft_null_point3new();
	coll_points[0] = (ft_3_point_point_dist(origin, coll_points[0]) >
			ft_3_point_point_dist(origin, coll_points[1])) ? coll_points[1] : coll_points[0];
	return (coll_points[0]);
}

t_point3		ft_get_norm_sphere(void *fig, t_point3 coll)
{
	return (ft_unitvector3new(((t_sphere *) fig)->origin, coll));
}
