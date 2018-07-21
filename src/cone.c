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

char		*ft_parse_cone(char *attr, t_scene *scn)
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
	obj->cam_dist = ft_get_dist(scn->cam->origin,
		ft_add_vector(cone->base, ft_scale_vector(
				ft_vectornew(cone->base, cone->vert), 0.5)));
	ft_lstpush_sort(scn, obj);
	return (ft_get_curve(attr, '}'));
}

int		ft_is_reachable_cone(void *fig, t_point origin, t_point direct)
{
	t_cone		*cone;
	t_point		proj;
	int			is_between;
	double		bv_dist;

	cone = (t_cone *)fig;
	if (ft_vectors_cos(direct, ft_vectornew(origin, cone->base)) > 0 ||
		ft_vectors_cos(direct, ft_vectornew(origin, cone->vert)) > 0)
		return (1);
	proj = ft_project_point(cone->base,
		ft_unitvectornew(cone->base, cone->vert), origin);
	bv_dist = ft_get_dist(cone->base, cone->vert);
	is_between = ft_get_dist(proj, cone->base) +
		ft_get_dist(proj, cone->vert) == bv_dist;
	if (is_between && ft_linetopoint_dist(cone->base, cone->vert, origin) <
			cone->base_rad * ((ft_get_dist(cone->base, origin) *
			ft_vectors_cos(ft_vectornew(cone->base, origin),
			ft_vectornew(cone->base, cone->vert))) / bv_dist))
		return (1);
	return (0);
}

t_point		ft_collide_cone(void *fig, t_point origin, t_point direct)
{
	t_cone	*cone;
	t_point	pnt[4];
	double	ang[2];
	double	t[3];

	cone = (t_cone *)fig;
	pnt[0] = origin;
	pnt[1] = direct;
	ft_get_angles(cone, &ang);
	ft_get_t(cone, ang, pnt, &t);
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
	t_point		norm;
	t_plane		*pln;

	cone = (t_cone *)fig;
	proj = ft_project_point(cone->base, cone->vert, coll);
	if (ft_pointcmp(proj, cone->base))
		return (ft_unitvectornew(cone->base, coll));
	if (ft_pointcmp(proj, cone->vert))
		return (ft_unitvectornew(cone->vert, coll));
	proj = ft_tounitvector(proj);
	norm = ft_unitvectornew(
		ft_add_vector(cone->base, ft_scale_vector(proj, cone->base_rad)),
		ft_add_vector(cone->vert, ft_scale_vector(proj, cone->vert_rad)));
	pln = ft_planenew();
	pln->origin = coll;
	pln->norm = norm;
	return (ft_unitvectornew(
		ft_collide_plane((void *)pln, cone->base,
			ft_unitvectornew(cone->base, cone->vert)), coll));
}
