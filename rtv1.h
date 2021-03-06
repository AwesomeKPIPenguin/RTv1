/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 11:57:36 by domelche          #+#    #+#             */
/*   Updated: 2018/09/19 11:57:39 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H

# define RTV1_H

# include <stdio.h>

# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <stdint.h>
# include <time.h>
# include "libft.h"
# include "libpnt.h"
# include "mlx.h"

# define WIN_WIDTH		1200.0
# define WIN_HEIGHT		700.0

# define FOV_MIN		60.0
# define FOV_MAX		120.0

# define BRIGHT_UNIT	20000.0

# define DEPTH			10

# define THREADS		8

# define KOEF			0
# define DBL			1
# define STR			2
# define PNT			3
# define COLOR			4

# define FTSA_GLOBALLY	0
# define FTSA_IN_SCOPE	1

# define ESC            0X35
# define ARR_UP         0X7E
# define ARR_DOWN       0X7D
# define ARR_RIGHT      0X7C
# define ARR_LEFT       0X7B
# define R              0X0F
# define PLUS           0X45
# define MINUS          0X4E
# define C              0X08

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

typedef struct			s_light
{
	t_color				color;
	double				bright;
	t_point3			origin;
	t_point3			direct;
}						t_light;

typedef struct			s_camera
{
	double				alpha;
	double				beta;
	double				gamma;
	double				fov;
	t_point3			origin;
	t_point3			direct;
	t_point3			vs_start_point;
	t_point3			vs_start_vec;
	t_point3			vs_x_step_vec;
	t_point3			vs_y_step_vec;
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
							(void *fig, t_point3 origin, t_point3 direct);
	t_point3			(*ft_collide)
							(void *fig, t_point3 origin, t_point3 direct);
	t_point3			(*ft_get_norm)(void *fig, t_point3 coll);
	t_point3			translate;
	t_point3			rotate;
}						t_object;

typedef struct			s_plane
{
	t_point3			origin;
	t_point3			norm;
}						t_plane;

typedef struct			s_sphere
{
	double				radius;
	t_point3			origin;
}						t_sphere;

typedef struct			s_cone
{
	double				base_rad;
	double				vert_rad;
	double				bv_dist;
	double				side_norm_angle;
	t_point3			base;
	t_point3			vert;
	t_point3			bv;
	t_point3			main_vert;
}						t_cone;

/*
**	----------------------------------------------------------------------------
*/

typedef struct			s_collision
{
	double				illum;
	double				phong;
	t_object			*o;
	t_point3			coll_pnt;
	t_point3			norm;
	t_point3			spclr_vec;
	t_point3			trans_vec;
}						t_coll;

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
void					ft_get_attr_in_scope
							(char *start, char *name, void *where, int what);

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
							(void *fig, t_point3 origin, t_point3 direct);
t_point3				ft_collide_plane
							(void *fig, t_point3 origin, t_point3 direct);
t_point3				ft_get_norm_plane(void *fig, t_point3 coll);

/*
**	sphere.c
*/

char					*ft_parse_sphere(char *attr, t_scene *scn);
int						ft_is_reachable_sphere
							(void *fig, t_point3 origin, t_point3 direct);
t_point3				ft_collide_sphere
							(void *fig, t_point3 origin, t_point3 direct);
t_point3				ft_get_norm_sphere(void *fig, t_point3 coll);

/*
**	cone.c
*/

char					*ft_parse_cone(char *attr, t_scene *scn);
int						ft_is_reachable_cone
							(void *fig, t_point3 origin, t_point3 direct);
t_point3				ft_collide_cone
							(void *fig, t_point3 origin, t_point3 direct);
t_point3				ft_get_norm_cone(void *fig, t_point3 coll);

/*
**	cone_utils.c
*/

void					ft_get_coll_pnts
							(t_cone *cone, t_point3 (*pnt)[4], int is_cyl);
void					ft_is_between_planes
							(t_point3 (*pnt)[4], t_point3 base, t_point3 vert);
void					ft_collide_cone_planes
							(t_cone *cone, t_point3 origin,
							t_point3 direct, t_point3 (*pnt)[4]);
t_point3				ft_get_closest(t_point3 cam, t_point3 pnt[4]);

/*
**	cone_utils_2.c
*/

void					ft_set_coll_pnts_null(t_point3 *pnt1, t_point3 *pnt2);
void					ft_cone_init(t_object *obj, t_cone *cone);

/*
**	ray.c
*/

t_color					ft_throw_rays
							(t_parg *parg, t_coll coll, t_point3 *vec,
							double num[2]);
t_color					ft_trace_ray(t_parg *parg, int x, int y);

/*
**	ray_utils.c
*/

t_point3				ft_change_blur_vec
							(t_point3 norm, t_point3 vec, double angle);
t_point3				ft_get_blur_proj(t_point3 origin, t_point3 norm);
t_color					ft_sum_colors
							(t_coll coll, t_color color_s, t_color color_t);

/*
**	illumination.c
*/

void					ft_illuminate(t_parg *parg, t_coll *coll);

/*
**	collision.c
*/

t_coll					ft_get_collision
							(t_parg *parg, t_point3 origin, t_point3 direct);

/*
**	utils.c
*/

t_color					ft_apply_a(t_color color, double bright);

/*
**	key_hooks.c
*/

int						ft_key_hook(int key, void *p);

#endif
