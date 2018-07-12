//
// Created by Dimon on 12.07.2018.
//

#include "../rtv1.h"

t_point		ft_vectornew(double x, double y, double z)
{
	t_point	vec;
	double	len;

	len = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	vec = ft_pointnew(x / len, y / len, z / len);
	return (vec);
}

t_point		ft_add_vector(t_point vec_1, t_point vec_2)
{
	vec_1.x += vec_2.x;
	vec_1.y += vec_2.y;
	vec_1.z += vec_2.z;
	return (vec_1);
}

t_point		ft_mul_vector(t_point vec, double k)
{
	vec.x *= k;
	vec.y *= k;
	vec.z *= k;
	return (vec);
}
