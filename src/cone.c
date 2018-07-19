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
	obj->cam_dist = ft_get_dist(scn->cam->origin,
		ft_add_vector(cone->base, ft_scale_vector(
				ft_vectornew(cone->base, cone->vert), 0.5)));
	ft_lstpush_sort(scn, obj);
}

int			ft_is_inside_cone(t_cone *cone, t_point point)
{
	if (ft_linetopoint_dist(cone->base, cone->vert, point) <
		cone->base_rad * ((ft_get_dist(cone->base, point) * ft_vectors_cos(
			ft_vectornew(cone->base, point),
			ft_vectornew(cone->base, cone->vert))) /
		ft_get_dist(cone->base, cone->vert)))
		return (1);
	return (0);
}

int			ft_is_reachable_cone(void *fig, t_point origin, t_point direct)
{
	t_cone		*cone;

	cone = (t_cone *)fig;
	if (ft_vectors_cos(direct, ft_vectornew(origin, cone->base)) > 0 ||
		ft_vectors_cos(direct, ft_vectornew(origin, cone->vert)) > 0 ||
		ft_is_inside_cone(cone, origin))
		return (1);
	return (0);
}

static void	ft_get_angles(t_cone *cone, double (*ang)[2])
{
	t_point		vec;

	vec = ft_vectornew(cone->base, cone->vert);
	*ang[0] = acos(ft_vectors_cos(ft_pointnew(vec.x, 0, vec.z),
		ft_pointnew(1.0, 0.0, 0.0)));
	*ang[1] = acos(ft_vectors_cos(ft_pointnew(0, vec.y, vec.z),
		ft_pointnew(0.0, 1.0, 0.0)));
}

static double	ft_get_t(t_cone *cone, double ang[2],
						t_point pnt[4], double (*t)[3])
{
	double	ctg;
	double	a[3];
	double	b[3];

	ctg = ft_get_dist(cone->base, cone->vert) /
		(cone->base_rad - cone->vert_rad);
	a[0] = pnt[1].x * cos(ang[1]) + pnt[1].y * sin(ang[0]) * sin(ang[1]) +
		pnt[1].z * cos(ang[0]) * sin(ang[1]);
	a[1] = -pnt[1].x * sin(ang[1]) + pnt[1].y * sin(ang[0]) * cos(ang[1]) +
		pnt[1].z * cos(ang[0]) * cos(ang[1]);
	a[2] = (pnt[1].y * cos(ang[0]) - pnt[1].z * sin(ang[0])) / ctg;
	b[0] = pnt[0].x * cos(ang[1]) + pnt[0].y * sin(ang[0]) * sin(ang[1]) +
		pnt[0].z * cos(ang[0]) * sin(ang[1]);
	b[1] = -pnt[0].x * sin(ang[1]) + pnt[0].y * sin(ang[0]) * cos(ang[1]) +
		pnt[0].z * cos(ang[0]) * cos(ang[1]);
	b[2] = (pnt[0].y * cos(ang[0]) - pnt[0].z * sin(ang[0])) / ctg;
	ft_solve_sqr(pow(a[0], 2) + pow(a[1], 2) + pow(a[2], 2),
		a[0] * b[0] + a[1] * b[1] + a[2] * b[2],
		pow(b[0], 2) + pow(b[1], 2) + pow(b[2], 2), t);
}

void		ft_is_between_planes(t_point (*pnt)[4], t_point base, t_point vert)
{
	t_point	bv;
	t_point	vb;

	bv = ft_vectornew(base, vert);
	vb = ft_scale_vector(bv, -1);
	if (ft_vectors_cos(bv, ft_vectornew(base, *pnt[0])) < 0 ||
		ft_vectors_cos(vb, ft_vectornew(vert, *pnt[0])) < 0)
		*pnt[0] = ft_null_pointnew();
	if (ft_vectors_cos(bv, ft_vectornew(base, *pnt[1])) < 0 ||
		ft_vectors_cos(vb, ft_vectornew(vert, *pnt[1])) < 0)
		*pnt[1] = ft_null_pointnew();
}

void		ft_collide_planes(t_cone *cone, t_point origin, t_point direct,
								t_point (*pnt)[4])
{

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
	pnt[0] = ft_pointnew(direct.x * t[0] + origin.x,
		direct.y * t[0] + origin.y, direct.z * t[0] + origin.z);
	pnt[1] = ft_pointnew(direct.x * t[1] + origin.x,
		direct.y * t[1] + origin.y, direct.z * t[1] + origin.z);
	ft_is_between_planes(&pnt, cone->base, cone->vert);

}

t_point		ft_get_norm_sphere(void *fig, t_point coll)
{
	return (ft_vectornew(((t_sphere *)fig)->origin, coll));
}
