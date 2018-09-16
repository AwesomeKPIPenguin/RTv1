/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 13:25:05 by domelche          #+#    #+#             */
/*   Updated: 2018/08/23 13:25:05 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

t_point3		ft_vector3new(t_point3 origin, t_point3 direct)
{
	return (ft_point3new(direct.x - origin.x, direct.y - origin.y,
						 direct.z - origin.z));
}

t_point3		ft_unitvector3new(t_point3 origin, t_point3 direct)
{
	t_point3	vec;
	double		len;

	vec = ft_vector3new(origin, direct);
	len = ft_vector_len(vec);
	vec = ft_3_vector_scale(vec, 1.0 / len);
	return (vec);
}

double			ft_vector_len(t_point3 vec)
{
	return (sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2)));
}

t_point3		ft_tounitvector3(t_point3 vec)
{
	double	len;

	len = ft_vector_len(vec);
	return (ft_point3new(vec.x / len, vec.y / len, vec.z / len));
}

t_point3		ft_3_add_vector(t_point3 vec_1, t_point3 vec_2)
{
	vec_1.x += vec_2.x;
	vec_1.y += vec_2.y;
	vec_1.z += vec_2.z;
	return (vec_1);
}

double			ft_3_vector_dot(t_point3 vec_1, t_point3 vec_2)
{
	return (vec_1.x * vec_2.x + vec_1.y * vec_2.y + vec_1.z * vec_2.z);
}

t_point3		ft_3_vector_cross(t_point3 vec_1, t_point3 vec_2)
{
	return (ft_point3new(vec_1.y * vec_2.z - vec_1.z * vec_2.y,
						 vec_1.z * vec_2.x - vec_1.x * vec_2.z,
						 vec_1.x * vec_2.y - vec_1.y * vec_2.x));
}

t_point3		ft_3_vector_scale(t_point3 vec, double k)
{
	vec.x *= k;
	vec.y *= k;
	vec.z *= k;
	return (vec);
}

double			ft_3_vector_cos(t_point3 vec_1, t_point3 vec_2)
{
	return ((vec_1.x * vec_2.x + vec_1.y * vec_2.y + vec_1.z * vec_2.z) /
		  (ft_vector_len(vec_1) * ft_vector_len(vec_2)));
}

t_point3		ft_3_reflect_vector
					(t_point3 origin, t_point3 coll, t_point3 norm)
{
	t_point3		oc;

	oc = ft_vector3new(origin, coll);
	return(ft_unitvector3new(coll, ft_3_add_vector(origin,
		ft_3_vector_scale(ft_vector3new(origin,	ft_3_add_vector(coll,
			ft_3_vector_scale(norm, (ft_vector_len(oc) *
				-ft_3_vector_cos(oc, norm))))), 2.0))));
}

t_point3		ft_3_turn_vector(t_point3 proj, t_point3 norm, double angle)
{
	return (ft_3_add_vector(
			ft_3_vector_scale(proj, sin(angle)),
			ft_3_vector_scale(norm, cos(angle))));
}

t_point3		ft_3_project_vector(t_point3 norm, t_point3 vec)
{
	return (ft_3_add_vector(vec, ft_3_vector_scale(norm, (ft_vector_len(vec) *
		-ft_3_vector_cos(norm, vec)) / ft_vector_len(norm))));
}

t_point3		ft_3_rotate_vector
					(t_point3 vec, double alpha, double beta, double gamma)
{
	t_point3		rotated;
	double		sin_[3];
	double		cos_[3];

	sin_[0] = sin(alpha);
	sin_[1] = sin(beta);
	sin_[2] = sin(gamma);
	cos_[0] = cos(alpha);
	cos_[1] = cos(beta);
	cos_[2] = cos(gamma);
	rotated.x = vec.x * cos_[2] * cos_[1] +
				vec.y * (cos_[2] * sin_[1] * sin_[0] - sin_[2] * cos_[0]) +
				vec.z * (sin_[2] * sin_[0] + cos_[0] * cos_[2] * sin_[1]);
	rotated.y = vec.x * cos_[1] * sin_[2] +
				vec.y * (cos_[0] * cos_[2] + sin_[0] * sin_[1] * sin_[2]) +
				vec.z * (cos_[0] * sin_[1] * sin_[2] - sin_[0] * cos_[2]);
	rotated.z = vec.x * -(sin_[1]) +
				vec.y * sin_[0] * cos_[1] +
				vec.z * cos_[0] * cos_[1];
	return (rotated);
}

t_point3		ft_3_turn_vector_near(t_point3 vec, t_point3 axis, double angle)
{
	t_point3		rotated;
	double		sin_a;
	double		cos_a;
	double		va;

	sin_a = sin(angle);
	cos_a = cos(angle);
	va = 1 - cos_a;
	rotated.x = vec.x * (axis.x * axis.x * va + cos_a) +
				vec.y * (axis.x * axis.y * va - axis.z * sin_a) +
				vec.z * (axis.x * axis.z * va + axis.y * sin_a);
	rotated.y = vec.x * (axis.x * axis.y * va + axis.z * sin_a) +
				vec.y * (axis.y * axis.y * va + cos_a) +
				vec.z * (axis.y * axis.z * va - axis.x * sin_a);
	rotated.z = vec.x * (axis.x * axis.z * va - axis.y * sin_a) +
				vec.y * (axis.y * axis.z * va + axis.x * sin_a) +
				vec.z * (axis.z * axis.z * va + cos_a);
	return (rotated);
}
