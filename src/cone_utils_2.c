#include "rtv1.h"

void		ft_set_coll_pnts_null(t_point3 (*pnt)[4])
{
	(*pnt)[0] = ft_3_nullpointnew();
	(*pnt)[1] = (*pnt)[0];
}

void		ft_cone_init(t_object *obj, t_cone *cone)
{
	obj->fig = cone;
	cone->bv_dist = ft_3_point_point_dist(cone->base, cone->vert);
	cone->base = ft_3_add_vector(cone->base, obj->translate);
	cone->bv = ft_3_rotate_vector(ft_3_unitvectornew(cone->base, cone->vert),
		obj->rotate.x, obj->rotate.y, obj->rotate.z);
	cone->vert = ft_3_add_vector(cone->base,
		ft_3_vector_scale(cone->bv, cone->bv_dist));
	cone->side_norm_angle = acos((cone->bv_dist * sin(atan((cone->base_rad -
		cone->vert_rad) / cone->bv_dist))) / (cone->base_rad - cone->vert_rad));
	cone->main_vert = ft_3_add_vector(cone->base, ft_3_vector_scale(cone->bv,
		cone->base_rad * cone->bv_dist / (cone->base_rad - cone->vert_rad)));
}
