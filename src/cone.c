//
// Created by Dimon on 16.07.2018.
//

#include "../rtv1.h"

t_cone		*ft_conenew()
{
	t_cone	*cone;

	cone = ft_smemalloc(sizeof(t_cone), "ft_conenew");
	return (cone);
}

void		ft_parse_cone(char *attr, t_scene *scn)
{
	t_object	*obj;
	t_cone		*cone;
	char		*ptr;

	ft_parse_object(attr, obj);
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
	obj->cam_dist = ;
	ft_lstpush_sort(scn, obj);
}

int			ft_is_reachable_sphere(void *fig, t_point origin, t_point direct)
{
	t_sphere	*sph;
	t_point		od;
	t_point		os;
	double		cos;

	sph = (t_sphere *)fig;
	if (ft_get_dist(origin, sph->origin) <= sph->radius)
		return (1);
	od = ft_vectornew(origin, direct);
	os = ft_vectornew(origin, sph->origin);
	cos = ft_vectors_cos(od, os);
	return ((cos > 0) ? 1 : 0);
}

t_point		ft_collide_sphere(void *fig, t_point origin, t_point direct)
{
	t_sphere	*sph;
	double		dist;
	t_point		od;
	double		sqr_res[2];
	t_point		coll_points[2];

	sph = (t_sphere *)fig;
	dist = ft_linetopoint_dist(origin, direct, sph->origin);
	if (dist > sph->radius)
		return (ft_null_pointnew());
	od = ft_vectornew(origin, direct);
	ft_solve_sqr((pow(od.x, 2) + pow(od.y, 2) + pow(od.z, 2)),
				 (origin.x * od.x + origin.y * od.y + origin.z * od.z),
				 (pow(origin.x, 2) + pow(origin.y, 2) + pow(origin.z, 2) -
				  pow(sph->radius, 2)), sqr_res);
	coll_points[0] = ft_pointnew(od.x * sqr_res[0] + origin.x,
								 od.y * sqr_res[0] + origin.y, od.z * sqr_res[0] + origin.z);
	coll_points[1] = ft_pointnew(od.x * sqr_res[1] + origin.x,
								 od.y * sqr_res[1] + origin.y, od.z * sqr_res[1] + origin.z);
	return ((ft_get_dist(origin, coll_points[0]) >
			 ft_get_dist(origin, coll_points[1])) ?
			coll_points[0] : coll_points[1]);
}

t_point		ft_get_norm_sphere(void *fig, t_point coll)
{
	return (ft_vectornew(((t_sphere *)fig)->origin, coll));
}
