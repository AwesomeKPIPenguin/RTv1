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

void		ft_parse_sphere(char *attr, t_scene *scn)
{
	t_object	*obj;
	t_sphere	*sph;
	char		*ptr;

	obj = ft_objectnew();
	obj->ft_collide = ft_collide_sphere;
	obj->ft_is_reachable = ft_is_reachable_sphere;
	sph = ft_spherenew();
	attr = ft_get_curve(attr);
	if ((ptr = ft_search_attr(attr, "origin:", FTSA_IN_SCOPE)))
		ft_read_attr((void *)(&(sph->origin)), ptr, POINT);
	if ((ptr = ft_search_attr(attr, "radius:", FTSA_IN_SCOPE)))
		ft_read_attr((void *)(&(sph->radius)), ptr, DOUBLE);
	if ((ptr = ft_search_attr(attr, "color:", FTSA_IN_SCOPE)))
		ft_read_attr((void *)(&(obj->color)), ptr, COLOR);
	if ((ptr = ft_search_attr(attr, "spclr:", FTSA_IN_SCOPE)))
		ft_read_attr((void *)(&(obj->spclr)), ptr, BYTE);
	if ((ptr = ft_search_attr(attr, "trans:", FTSA_IN_SCOPE)))
		ft_read_attr((void *)(&(obj->trans)), ptr, BYTE);
	obj->fig = sph;
	obj->cam_dist = ft_get_dist(scn->cam->origin, sph->origin) - sph->radius;
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
	cos = (od.x * os.x + od.y * os.y + od.z * os.z) /
			(ft_vector_len(od) * ft_vector_len(os));
	return ((cos > -0.5 && cos < 0.5) ? 1 : 0);
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
