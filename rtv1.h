
#ifndef RTV1_H

# define RTV1_H

# include <fcntl.h>
# include <math.h>
# include <limits.h>
# include <pthread.h>
# include <stdint.h>
# include "libft/libft.h"
//# include "minilibx/mlx.h"

# define WIN_WIDTH		1200.0
# define WIN_HEIGHT		700.0

# define FOV_MIN		60.0
# define FOV_MAX		120.0

# define THREADS		8

# define BYTE			0
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
	t_byte				bright;
	t_point				origin;
}						t_light;

typedef struct			s_camera
{
	double				alpha;
	double				beta;
	double				gamma;
	double				fov;
	t_point				origin;
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
	t_byte				spclr;
	t_byte				trans;
	t_color				color;
	double				cam_dist;
	void				*fig;
	t_point				*(*ft_get_collision_point)(
							struct s_object *o, t_point origin, t_point direct);
}						t_object;

typedef struct			s_plane
{
	t_point				point_0;
	t_point				point_1;
	t_point				point_2;
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

/*
**	point.c
*/

t_point					ft_pointnew(double x, double y, double z);
t_point					ft_atopoint(char *str);
double					ft_get_dist(t_point pnt_0, t_point pnt_1);

/*
**	vector.c
*/

t_point					ft_vectornew(double x, double y, double z);
t_point					ft_add_vector(t_point vec_1, t_point vec_2);
t_point					ft_mul_vector(t_point vec, double k);

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
void					ft_parse_camera(char *attr, t_scene *scn);

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
char					*ft_get_curve(char *attr);

/*
**	attribute.c
*/

char					*ft_search_attr(
							char *content, char *attr, int ftsa_mode);
void					ft_read_attr(void *dst, char *attr, int type);

/*
**	light.c
*/

t_light					*ft_lightnew();
void					ft_parse_light(char *attr, t_scene *scn);

/*
**	object.c
*/

t_object				*ft_objectnew();

/*
**	sphere.c
*/

void					ft_parse_sphere(char *attr, t_scene *scn);

/*
**	ray.c
*/

t_color					ft_cast_ray(t_env *e, int x, int y);

/*
**	utils.c
*/

t_point					ft_rotate_vector(t_point vec,
								double alpha, double beta, double gamma);
double					ft_torad(double degrees);
void					ft_lstpush_sort(t_scene *scn, t_object *obj);

#endif
