
#include "../rtv1.h"

static void	ft_get_vs_params(t_camera *cam)
{
	cam->vs_start_vec = ft_rotate_vector(
		ft_vectornew(0.0, WIN_HEIGHT / 2.0, -WIN_WIDTH / 2.0),
		cam->alpha, cam->beta, cam->gamma);
	cam->vs_x_step_vec = ft_rotate_vector(
		ft_vectornew(0.0, 0.0, WIN_WIDTH),
		cam->alpha, cam->beta, cam->gamma);
	cam->vs_y_step_vec = ft_rotate_vector(
		ft_vectornew(0.0, -WIN_HEIGHT, 0.0),
		cam->alpha, cam->beta, cam->gamma);
	cam->vs_start_point = ft_add_vector(cam->vs_start_vec,
		ft_add_vector(cam->origin,
			ft_rotate_vector(
				ft_pointnew(WIN_WIDTH / (2 * tan(cam->fov)), 0.0, 0.0),
				cam->alpha, cam->beta, cam->gamma)));
}

void		ft_parse(char *content, t_scene *scn)
{
	char	*attr;

	if ((attr = ft_search_attr(content, "scene", FTSA_GLOBALLY)))
		ft_parse_scene(attr, scn);
	if ((attr = ft_search_attr(content, "camera", FTSA_GLOBALLY)))
		ft_parse_camera(attr, scn);
	ft_get_vs_params(scn->cam);
	if ((attr = ft_search_attr(content, "light", FTSA_GLOBALLY)))
		ft_parse_light(attr, scn);
	if ((attr = ft_search_attr(content, "sphere", FTSA_GLOBALLY)))
		ft_parse_sphere(attr, scn);
}

char		*ft_get_curve(char *attr)
{
	while (*attr && *attr != '{')
		++attr;
	if (!*attr)
		ft_error("invalid scene file");
	return (attr + 1);
}
