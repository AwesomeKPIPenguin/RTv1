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

//	printf("                     vec = (%f, %f, %f), len = %f;\n",
//		vec.x, vec.y, vec.z, len);

	vec = ft_scale_vector(vec, 1.0 / len);

//	printf("after scale: (%f, %f, %f);\n", vec.x, vec.y, vec.z);

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
	double	len_1;
	double	len_2;

	len_1 = ft_vector_len(vec_1);
	len_2 = ft_vector_len(vec_2);

//	printf("cosine: len_1 = %f, len_2 = %f;\n", len_1, len_2);

	return ((vec_1.x * vec_2.x + vec_1.y * vec_2.y + vec_1.z * vec_2.z) /
		  (len_1 * len_2));
}

t_point		ft_reflect_vector(t_point origin, t_point coll, t_point norm)
{
	t_point		oc;
	t_point		on;
	double		cos;

	t_point res;

	oc = ft_vectornew(origin, coll);
	cos = -ft_vectors_cos(oc, norm);
	on = ft_vectornew(origin,
		ft_add_vector(coll, ft_scale_vector(norm, (ft_vector_len(oc) * cos))));

	res = ft_unitvectornew(coll, ft_add_vector(origin, ft_scale_vector(on, 2.0)));
//	if (coll.x >= -100 && coll.x <= 100 && coll.z >= -100 && coll.z <= 100)
//		printf("in ft_reflect_vector (%12.6f, %12.6f, %12.6f) -> (%12.6f, %12.6f, %12.6f), norm = (%5.4f, %5.4f, %5.4f);\nres: (%12.6f, %12.6f, %12.6f);\n\n",
//			origin.x, origin.y, origin.z, coll.x, coll.y, coll.z, norm.x, norm.y, norm.z, res.x, res.y, res.z);

	return(res);
}

t_point		ft_turn_vector(t_point proj, t_point norm, double angle)
{
	return (ft_add_vector(
		ft_scale_vector(proj, sin(angle)), ft_scale_vector(norm, cos(angle))));
}

t_point		ft_project_vector(t_point norm, t_point vec)
{
	return (ft_add_vector(vec, ft_scale_vector(norm,
		-ft_vectors_cos(norm, vec))));
}

t_point		ft_rotate_vector(t_point vec,
								double alpha, double beta, double gamma)
{
	t_point		rotated;
	double		sins[3];
	double		coss[3];

	sins[0] = sin(alpha);
	sins[1] = sin(beta);
	sins[2] = sin(gamma);
	coss[0] = cos(alpha);
	coss[1] = cos(beta);
	coss[2] = cos(gamma);
	rotated.x = vec.x * coss[2] * coss[1] +
				vec.y * (coss[2] * sins[1] * sins[0] - sins[2] * coss[0]) +
				vec.z * (sins[2] * sins[0] + coss[0] * coss[2] * sins[1]);
	rotated.y = vec.x * coss[1] * sins[2] +
				vec.y * (coss[0] * coss[2] + sins[0] * sins[1] * sins[2]) +
				vec.z * (coss[0] * sins[1] * sins[2] - sins[0] * coss[2]);
	rotated.z = vec.x * -(sins[1]) +
				vec.y * sins[0] * coss[1] +
				vec.z * coss[0] * coss[1];
	return (rotated);
}

t_point		ft_turn_vector_near(t_point vec, t_point axis, double angle)
{
	t_point		rotated;
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
