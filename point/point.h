#ifndef POINT_H

#define POINT_H

typedef struct			s_point3
{
	double				x;
	double				y;
	double				z;
}						t_point3;

/*
**	point
*/

t_point3				ft_point3new(double x, double y, double z);
t_point3				ft_null_point3new(void);
int						ft_isnullpoint3(t_point3 point);
t_point3				ft_atopoint3(char *str);
double					ft_3_point_point_dist(t_point3 pnt_0, t_point3 pnt_1);
double					ft_3_line_point_dist
							(t_point3 origin, t_point3 direct, t_point3 point);
double					ft_3_plane_point_dist
							(t_point3 origin, t_point3 norm, t_point3 point);
double					ft_3_line_line_dist
							(t_point3 o1, t_point3 d1,
							t_point3 o2, t_point3 d2);
t_point3				ft_3_line_line_inter
							(t_point3 o1, t_point3 d1,
							t_point3 o2, t_point3 d2);
t_point3				ft_3_line_point_proj
							(t_point3 origin, t_point3 direct, t_point3 point);
int						ft_point3cmp
							(t_point3 pnt_0, t_point3 pnt_1, double prec);

/*
**	vector
*/

t_point3				ft_vector3new(t_point3 origin, t_point3 direct);
t_point3				ft_unitvector3new(t_point3 origin, t_point3 direct);
t_point3				ft_tounitvector3(t_point3 vec);
t_point3				ft_3_add_vector(t_point3 vec_1, t_point3 vec_2);
t_point3				ft_3_vector_scale(t_point3 vec, double k);
double					ft_3_vector_dot(t_point3 vec_1, t_point3 vec_2);
t_point3				ft_3_vector_cross(t_point3 vec_1, t_point3 vec_2);
double					ft_vector_len(t_point3 vec);
double					ft_3_vector_cos(t_point3 vec_1, t_point3 vec_2);
t_point3				ft_3_reflect_vector
							(t_point3 origin, t_point3 coll, t_point3 norm);
t_point3				ft_3_turn_vector
							(t_point3 proj, t_point3 norm, double angle);
t_point3				ft_3_project_vector(t_point3 norm, t_point3 vec);
t_point3				ft_3_rotate_vector
							(t_point3 vec, double alpha,
							double beta, double gamma);
t_point3				ft_3_turn_vector_near
							(t_point3 vec, t_point3 axis, double angle);

#endif
