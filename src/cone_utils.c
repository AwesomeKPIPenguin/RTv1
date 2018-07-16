//
// Created by Dimon on 16.07.2018.
//

#include "../rtv1.h"

double	ft_get_side_dist()
{

}

double	ft_get_cam_dist_cone(t_point cam, t_cone *cone)
{
	t_point		bv;
	t_point		bc;
	t_point		vc;
	double		cos;
	double		dist;

	bv = ft_vectornew(cone->base, cone->vert);
	bc = ft_vectornew(cone->base, cam);
	vc = ft_vectornew(cone->vert, cam);
	dist = ft_linetopoint_dist(cone->base, bv, cam);
	if ((cos = ft_vectors_cos(bv, vc)) > 0 && (dist < cone->vert_rad))
		return (ft_planetopoint_dist(cone->vert, bv, cam));
	else if ((cos = ft_vectors_cos(bv, bc)) < 0 && (dist < cone->base_rad))
		return (ft_planetopoint_dist(cone->base, bv, cam));
}
