//
// Created by Dimon on 12.07.2018.
//

#include "../rtv1.h"

t_point		ft_vectornew(t_point origin, t_point direct)
{
	return (ft_pointnew(direct.x - origin.x, direct.y - origin.y,
						direct.z - origin.z));
}

t_point		ft_unitvectornew(t_point origin, t_point direct)
{
	t_point	vec;
	double	len;

	vec = ft_vectornew(origin, direct);
	len = ft_vector_len(vec);
	ft_scale_vector(vec, 1.0 / len);
	return (vec);
}

t_point		ft_tounitvector(t_point vec)
{
	double	len;

	len = ft_vector_len(vec);
	return (ft_pointnew(vec.x / len, vec.y / len, vec.z / len));
}

t_point		ft_add_vector(t_point vec_1, t_point vec_2)
{
	vec_1.x += vec_2.x;
	vec_1.y += vec_2.y;
	vec_1.z += vec_2.z;
	return (vec_1);
}

double		ft_mul_vector_s(t_point vec_1, t_point vec_2)
{
	return (vec_1.x * vec_2.x + vec_1.y * vec_2.y + vec_1.z * vec_2.z);
}

t_point		ft_mul_vector_v(t_point vec_1, t_point vec_2)
{
	return (ft_pointnew(vec_1.y * vec_2.z - vec_1.z * vec_2.y,
						-(vec_1.x * vec_2.z - vec_1.z * vec_2.x),
						vec_1.y * vec_2.x - vec_1.x * vec_2.y));
}

t_point		ft_scale_vector(t_point vec, double k)
{
	vec.x *= k;
	vec.y *= k;
	vec.z *= k;
	return (vec);
}

double		ft_vector_len(t_point vec)
{
	return (sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2)));
}

double		ft_vectors_cos(t_point vec_1, t_point vec_2)
{
	return ((vec_1.x * vec_2.x + vec_1.y * vec_2.y + vec_1.z * vec_2.z) /
		  (ft_vector_len(vec_1) * ft_vector_len(vec_2)));
}

t_point		ft_reflect_vector(t_point origin, t_point coll, t_point norm)
{
	t_point		oc;
	t_point		on;
	double		cos;

	oc = ft_vectornew(origin, coll);
	cos = -ft_vectors_cos(oc, norm);
	on = ft_vectornew(origin, ft_scale_vector(norm, (ft_vector_len(oc) * cos)));
	return (
		ft_unitvectornew(coll, ft_add_vector(origin, ft_scale_vector(on, 2))));
}
