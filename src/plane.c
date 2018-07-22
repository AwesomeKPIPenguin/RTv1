//
// Created by Dimon on 15.07.2018.
//

#include "../rtv1.h"

t_plane		*ft_planenew(void)
{
	t_plane	*pln;

	pln = ft_smemalloc(sizeof(t_plane), "ft_planenew");
	pln->origin = ft_pointnew(0.0, -1000.0, 0.0);
	pln->norm = ft_pointnew(0.0, 1.0, 0.0);
	return (pln);
}

int			ft_is_reachable_plane(void *fig, t_point origin, t_point direct)
{
	(void)fig;
	(void)origin;
	(void)direct;
	return (1);
}

t_point		ft_collide_plane(void *fig, t_point origin, t_point direct)
{
	t_plane		*pln;
	t_point		coll;
	double		t;
	double		dev;

	pln = (t_plane *)fig;
	if (!ft_vectors_cos(direct, pln->norm))
		return (ft_null_pointnew());
	dev = ft_mul_vector_s(pln->norm, direct);
	if (!dev)
		return (ft_null_pointnew());
	t = ft_mul_vector_s(pln->norm, pln->origin) -
		ft_mul_vector_s(pln->norm, origin) / dev;
	coll = ft_add_vector(origin, ft_scale_vector(direct, t));
	return ((ft_vectornew(origin, coll).x * direct.x < 0) ?
			ft_null_pointnew() : coll);
}

t_point		ft_get_norm_plane(void *fig, t_point coll)
{
	(void)coll;
	return (((t_plane *)fig)->norm);
}

char		*ft_parse_plane(char *attr, t_scene *scn)
{
	t_object	*obj;
	t_plane		*pln;
	char		*ptr;

	obj = ft_parse_object(attr);
	obj->ft_collide = ft_collide_plane;
	obj->ft_is_reachable = ft_is_reachable_plane;
	obj->ft_get_norm = ft_get_norm_plane;
	pln = ft_planenew();
	attr = ft_get_curve(attr, '{');
	if ((ptr = ft_search_attr(attr, "origin:", FTSA_IN_SCOPE)))
		ft_read_attr((void *)(&(pln->origin)), ptr, POINT);
	if ((ptr = ft_search_attr(attr, "norm:", FTSA_IN_SCOPE)))
		ft_read_attr((void *)(&(pln->norm)), ptr, POINT);
	pln->norm = ft_tounitvector(pln->norm);
	obj->fig = obj;
	obj->cam_dist =
			ft_planetopoint_dist(pln->origin, pln->norm, scn->cam->origin);
	ft_lstpush_sort(scn, obj);
	return (ft_get_curve(attr, '}'));
}
