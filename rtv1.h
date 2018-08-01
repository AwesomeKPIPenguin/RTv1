
#ifndef RTV1_H

# define RTV1_H


#include <stdio.h>


# include <fcntl.h>
# include <math.h>
# include <limits.h>
# include <float.h>
# include <pthread.h>
# include <stdint.h>
# include <time.h>
# include "libft/libft.h"
# include "minilibx/mlx.h"

# define WIN_WIDTH		1200.0
# define WIN_HEIGHT		700.0

# define FOV_MIN		60.0
# define FOV_MAX		120.0

# define BRIGHT_UNIT	5000.0

# define THREADS		8

# define PRECISION		1e-3

# define KOEF			0
# define DOUBLE			1
# define STRING			2
# define POINT			3
# define COLOR			4

# define FTSA_GLOBALLY	0
# define FTSA_IN_SCOPE	1

typedef uint8_t			t_byte;

typedef union			u_color
{
	int					val;
	unsigned char		argb[4];
}						t_color;

typedef struct			s_img
{
	void				*ptr;
	int					width;
	int					height;
	char				*data;
	int					bpp;
	int					size_line;
	int					endian;
}						t_img;

typedef struct			s_point
{
	double				x;
	double				y;
	double				z;
}						t_point;

typedef struct			s_light
{
	t_color				color;
	double				bright;
	t_point				origin;
	t_point				direct;
}						t_light;

typedef struct			s_camera
{
	double				alpha;
	double				beta;
	double				gamma;
	double				fov;
	t_point				origin;
	t_point				direct;
	t_point				vs_start_point;
	t_point				vs_start_vec;
	t_point				vs_x_step_vec;
	t_point				vs_y_step_vec;
}						t_camera;

typedef struct			s_scene
{
	t_color				bg_color;
	char				*name;
	t_list				*lights;
	t_list				*objs;
	t_camera			*cam;
}						t_scene;

typedef struct			s_env
{
	void				*mlx;
	void				*win;
	t_img				*img;
	t_img				*smooth_img;
	t_scene				*scn;
}						t_env;

typedef struct			s_parg
{
	int					section;
	t_env				*e;
}						t_parg;

/*
**	--------------------------------- objects ----------------------------------
*/

typedef struct			s_object
{
	t_color				color;
	double				ambnt;
	double				diff;
	double				spclr;
	double				s_blur;
	double				trans;
	double				t_blur;
	double				phong;
	void				*fig;
	int					(*ft_is_reachable)
							(void *fig, t_point origin, t_point direct);
	t_point				(*ft_collide)
							(void *fig, t_point origin, t_point direct);
	t_point				(*ft_get_norm)(void *fig, t_point coll);
}						t_object;

typedef struct			s_plane
{
	t_point				origin;
	t_point				norm;
}						t_plane;

typedef struct			s_sphere
{
	double				radius;
	t_point				origin;
}						t_sphere;

typedef struct			s_cone
{
	double				base_rad;
	double				vert_rad;
	t_point				base;
	t_point				vert;
}						t_cone;

/*
**	----------------------------------------------------------------------------
*/

typedef struct			s_collision
{
	double				illum;
	t_object			*o;
	t_point				coll_pnt;
	t_point				norm;
	t_point				spclr_vec;
	t_point				trans_vec;
}						t_coll;

/*
**	point.c
*/

t_point					ft_pointnew(double x, double y, double z);
t_point					ft_null_pointnew(void);
int						ft_isnullpoint(t_point point);
t_point					ft_atopoint(char *str);
double					ft_get_dist(t_point pnt_0, t_point pnt_1);
double					ft_linetopoint_dist
							(t_point origin, t_point direct, t_point point);
double					ft_planetopoint_dist
							(t_point origin, t_point norm, t_point point);
t_point					ft_project_point
							(t_point origin, t_point direct, t_point point);
int						ft_pointcmp(t_point pnt_0, t_point pnt_1);

/*
**	vector.c
*/

t_point					ft_vectornew(t_point origin, t_point direct);
t_point					ft_unitvectornew(t_point origin, t_point direct);
t_point					ft_tounitvector(t_point vec);
t_point					ft_add_vector(t_point vec_1, t_point vec_2);
t_point					ft_scale_vector(t_point vec, double k);
double					ft_mul_vector_s(t_point vec_1, t_point vec_2);
t_point					ft_mul_vector_v(t_point vec_1, t_point vec_2);
double					ft_vector_len(t_point vec);
double					ft_vectors_cos(t_point vec_1, t_point vec_2);
t_point					ft_reflect_vector
							(t_point origin, t_point coll, t_point norm);
t_point					ft_turn_vector
							(t_point proj, t_point norm, double angle);
t_point					ft_project_vector(t_point norm, t_point vec);
t_point					ft_rotate_vector
							(t_point vec,
							double alpha, double beta, double gamma);
t_point					ft_turn_vector_near
							(t_point vec, t_point axis, double angle);

/*
**	scene.c
*/

t_scene					*ft_scenenew(void);
t_scene					*ft_get_scene(char *file_name);
void					ft_parse_scene(char *attr, t_scene *scn);

/*
**	camera.c
*/

t_camera				*ft_cameranew(void);
char					*ft_parse_camera(char *attr, t_scene *scn);

/*
**	image.c
*/

t_img					*ft_imgnew(t_env *e);
void					ft_pixel_put_image(t_env *e, int x, int y, int colour);

/*
**	environment.c
*/

t_env					*ft_envnew(char *file_name);

/*
**	parse.c
*/

void					ft_parse(char *content, t_scene *scn);
char					*ft_get_curve(char *attr, char curve);

/*
**	render.c
*/

void					ft_render(t_env *e);

/*
**	attribute.c
*/

char					*ft_search_attr
							(char *content, char *attr, int ftsa_mode);
void					ft_read_attr(void *dst, char *attr, int type);

/*
**	light.c
*/

t_light					*ft_lightnew();
char					*ft_parse_light(char *attr, t_scene *scn);

/*
**	object.c
*/

t_object				*ft_objectnew();
t_object				*ft_parse_object(char *attr);

/*
**	plane.c
*/

t_plane					*ft_planenew(void);
char					*ft_parse_plane(char *attr, t_scene *scn);
int						ft_is_reachable_plane
							(void *fig, t_point origin, t_point direct);
t_point					ft_collide_plane
							(void *fig, t_point origin, t_point direct);
t_point					ft_get_norm_plane(void *fig, t_point coll);

/*
**	sphere.c
*/

char					*ft_parse_sphere(char *attr, t_scene *scn);
int						ft_is_reachable_sphere
							(void *fig, t_point origin, t_point direct);
t_point					ft_collide_sphere
							(void *fig, t_point origin, t_point direct);
t_point					ft_get_norm_sphere(void *fig, t_point coll);

/*
**	cone.c
*/

char					*ft_parse_cone(char *attr, t_scene *scn);
int						ft_is_reachable_cone
							(void *fig, t_point origin, t_point direct);
t_point					ft_collide_cone
							(void *fig, t_point origin, t_point direct);
t_point					ft_get_norm_cone(void *fig, t_point coll);

/*
**	cone_utils.c
*/

void					ft_get_angles(t_cone *cone, double (*ang)[2]);
void					ft_get_t
							(t_cone *cone, double ang[2],
							t_point pnt[4], double (*t)[3]);
void					ft_is_between_planes
							(t_point (*pnt)[4], t_point base, t_point vert);
void					ft_collide_cone_planes
							(t_cone *cone, t_point origin,
							t_point direct, t_point (*pnt)[4]);
t_point					ft_get_closest(t_point cam, t_point pnt[4]);

/*
**	ray.c
*/

t_color					ft_throw_rays
							(t_env *e, t_coll coll, t_point *vec, double k);
t_color					ft_trace_ray(t_env *e, int x, int y);

/*
**	ray_utils.c
*/

t_point					ft_change_blur_vec
							(t_point norm, t_point vec, double angle);
t_point					ft_get_blur_proj(t_point origin, t_point norm);
t_color					ft_sum_colors
							(t_coll coll, t_color color_s, t_color color_t);

/*
**	illumination.c
*/

double					ft_illuminate(t_scene *scn, t_point coll, t_point norm);

/*
**	collision.c
*/

t_coll					ft_get_collision
							(t_scene *scn, t_point origin, t_point direct,
							t_object *except);

/*
**	utils.c
*/

double					ft_torad(double degrees);
void					ft_solve_sqr
							(double a, double b, double c, double (*res)[3]);
t_color					ft_apply_a(t_color color, double bright);
t_color					ft_add_color(t_color c_1, t_color c_2);

#endif
