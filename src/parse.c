
#include "../rtv1.h"

static void	ft_get_vs_params(t_camera *cam)
{
	cam->vs_start_vec = ft_rotate_vector(
		ft_vectornew(ft_pointnew(0.0, 0.0, 0.0),
			ft_pointnew(0.0, WIN_HEIGHT / 2.0, -WIN_WIDTH / 2.0)),
		cam->alpha, cam->beta, cam->gamma);
	cam->vs_x_step_vec = ft_rotate_vector(
		ft_pointnew(0.0, 0.0, 1.0), cam->alpha, cam->beta, cam->gamma);
	cam->vs_y_step_vec = ft_rotate_vector(
		ft_pointnew(0.0, -1.0, 0.0), cam->alpha, cam->beta, cam->gamma);
	cam->vs_start_point = ft_add_vector(cam->vs_start_vec,
		ft_add_vector(cam->origin,
			ft_rotate_vector(
				ft_pointnew((WIN_WIDTH / 2.0) / tan(cam->fov / 2.0), 0.0, 0.0),
				cam->alpha, cam->beta, cam->gamma)));
}

void		ft_parse(char *content, t_scene *scn)
{
	char	*attr;
	char	*tmp;

	t_light		*debug_light;
	t_plane		*debug_plane;
	t_sphere	*debug_sphere;
	t_point		debug_point;

	if ((attr = ft_search_attr(content, "scene", FTSA_GLOBALLY)))
		ft_parse_scene(attr, scn);
	if ((attr = ft_search_attr(content, "camera", FTSA_GLOBALLY)))
		ft_parse_camera(attr, scn);
	ft_get_vs_params(scn->cam);
	tmp = content;
	while ((attr = ft_search_attr(tmp, "light", FTSA_GLOBALLY)))
		tmp = ft_parse_light(attr, scn);

	debug_light = (t_light *)(scn->lights->content);

	tmp = content;
	while ((attr = ft_search_attr(tmp, "plane", FTSA_GLOBALLY)))
		tmp = ft_parse_plane(attr, scn);

	debug_plane = (t_plane *)(((t_object *)(scn->objs->content))->fig);
	debug_point = debug_plane->origin;

	tmp = content;
	while ((attr = ft_search_attr(tmp, "sphere", FTSA_GLOBALLY)))
		tmp = ft_parse_sphere(attr, scn);

	debug_sphere = (t_sphere *)(((t_object *)scn->objs->next->content)->fig);

	tmp = content;
	while ((attr = ft_search_attr(tmp, "cone", FTSA_GLOBALLY)))
		tmp = ft_parse_cone(attr, scn);
}

char		*ft_get_curve(char *attr, char curve)
{
	while (*attr && *attr != curve)
		++attr;
	if (!*attr)
		ft_error("invalid scene file");
	return (attr + 1);
}
