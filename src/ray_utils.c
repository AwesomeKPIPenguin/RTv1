//
// Created by Dimon on 31.07.2018.
//

#include "../rtv1.h"

t_point		ft_change_blur_vec(t_point norm, t_point vec, double angle)
{
	t_point	proj;

	proj = ft_project_vector(norm, vec);
	if (acos(ft_vectors_cos(norm, vec)) + angle <= M_PI_2)
		return (vec);
	return (ft_turn_vector(proj, norm, M_PI_2 - angle));
}

t_point		ft_get_blur_proj(t_point origin, t_point norm)
{
	t_point		zero_proj;
	double		angle;

	zero_proj = ft_project_vector(norm,
		ft_vectornew(origin, ft_pointnew(0.0, 0.0, 0.0)));
	if (ft_vector_len(zero_proj) == 0.0)
		zero_proj = ft_project_vector(norm,
			ft_vectornew(origin, ft_pointnew(42.0, 0.0, 0.0)));
	if (ft_vector_len(zero_proj) == 0.0)
		zero_proj = ft_project_vector(norm,
			ft_vectornew(origin, ft_pointnew(0.0, 42.0, 0.0)));
	zero_proj = ft_tounitvector(zero_proj);
	angle = (double)rand() / (double)RAND_MAX * M_2_PI;
	return (ft_turn_vector_near(zero_proj, norm, angle));
}
