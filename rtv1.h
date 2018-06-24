
#ifndef RTV1_H

# define RTV1_H

# include <fcntl.h>
# include <math.h>
# include <limits.h>
# include <pthread.h>
# include <stdint.h>
# include "libft/libft.h"
//# include "minilibx/mlx.h"

# define THREADS		8

# define BYTE			0
# define DOUBLE			1
# define STRING			2
# define POINT			3
# define COLOR			4

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

typedef struct			s_scene
{
	char				*name;
	t_point				origin;
	int					width;
	int					height;
	t_list				*objs;
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
**	objects
*/

typedef struct			s_plane
{
	t_byte				spclr;
	t_byte				trans;
	t_color				color;
	t_point				point_0;
	t_point				point_1;
	t_point				point_2;
}						t_plane;

typedef struct			s_sphere
{
	t_byte				spclr;
	t_byte				trans;
	t_color				color;
	double				radius;
	t_point				origin;
}						t_sphere;

typedef struct			s_cone
{
	t_byte				spclr;
	t_byte				trans;
	t_color				color;
	double				base_rad;
	double				vert_rad;
	t_point				base;
	t_point				vert;
}						t_cone;

/*
**	scene.c
*/

t_scene					*ft_scenenew(void);

/*
**	parse.c
*/

char					*ft_search_attr_in_scope(char *content, char *attr);

#endif
