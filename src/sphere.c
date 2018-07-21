//
// Created by Dimon on 10.07.2018.
//

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
	char		*ptr;

	ft_parse_object(attr, obj);
	obj->ft_collide = ft_collide_sphere;
	obj->ft_is_reachable = ft_is_reachable_sphere;
	obj->ft_get_norm = ft_get_norm_sphere;
	sph = ft_spherenew();
	attr = ft_get_curve(attr, '{');
	if ((ptr = ft_search_attr(attr, "origin:", FTSA_IN_SCOPE)))
		ft_read_attr((void *)(&(sph->origin)), ptr, POINT);
	if ((ptr = ft_search_attr(attr, "radius:", FTSA_IN_SCOPE)))
		ft_read_attr((void *)(&(sph->radius)), ptr, DOUBLE);
	obj->fig = sph;
	obj->cam_dist = ft_get_dist(scn->cam->origin, sph->origin) - sph->radius;
	ft_lstpush_sort(scn, obj);
	return (ft_get_curve(attr, '}'));
}

int			ft_is_reachable_sphere(void *fig, t_point origin, t_point direct)
{
	t_sphere	*sph;
	double		cos;

	sph = (t_sphere *)fig;
	if (ft_get_dist(origin, sph->origin) <= sph->radius)
		return (1);
	cos = ft_vectors_cos(direct, ft_vectornew(origin, sph->origin));
	return ((cos > 0) ? 1 : 0);
}

t_point		ft_collide_sphere(void *fig, t_point origin, t_point direct)
{
	t_sphere	*sph;
	double		dist;
	double		sqr_res[3];
	t_point		coll_points[2];

	sph = (t_sphere *)fig;
	dist = ft_linetopoint_dist(origin, direct, sph->origin);
	if (dist > sph->radius)
		return (ft_null_pointnew());
	ft_solve_sqr((pow(direct.x, 2) + pow(direct.y, 2) + pow(direct.z, 2)),
		(origin.x * direct.x + origin.y * direct.y + origin.z * direct.z),
		(pow(origin.x, 2) + pow(origin.y, 2) + pow(origin.z, 2) -
			pow(sph->radius, 2)), &sqr_res);
	if (!sqr_res[0])
		return (ft_null_pointnew());
	coll_points[0] = ft_pointnew(direct.x * sqr_res[0] + origin.x,
		direct.y * sqr_res[0] + origin.y, direct.z * sqr_res[0] + origin.z);
	coll_points[1] = ft_pointnew(direct.x * sqr_res[1] + origin.x,
		direct.y * sqr_res[1] + origin.y, direct.z * sqr_res[1] + origin.z);
	return ((ft_get_dist(origin, coll_points[0]) >
				ft_get_dist(origin, coll_points[1])) ?
			coll_points[0] : coll_points[1]);
}

t_point		ft_get_norm_sphere(void *fig, t_point coll)
{
	return (ft_unitvectornew(((t_sphere *)fig)->origin, coll));
}
