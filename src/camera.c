//
// Created by Dimon on 12.07.2018.
//

#include "../rtv1.h"

t_camera	*ft_cameranew(void)
{
	t_camera	*cam;

	cam = ft_smemalloc(sizeof(t_camera), "ft_cameranew");
	cam->origin = ft_pointnew(-500.0, 0.0, 0.0);
	cam->fov = ft_torad(100.0);
	return (cam);
}

void		ft_parse_camera(char *attr, t_scene *scn)
{
	char	*ptr;

	attr = ft_get_curve(attr);
	if ((ptr = ft_search_attr(attr, "origin:", FTSA_IN_SCOPE)))
		ft_read_attr((void *)&(scn->cam->origin), ptr, POINT);
	if ((ptr = ft_search_attr(attr, "alpha:", FTSA_IN_SCOPE)))
		ft_read_attr((void *)&(scn->cam->alpha), ptr, DOUBLE);
	if ((ptr = ft_search_attr(attr, "beta:", FTSA_IN_SCOPE)))
		ft_read_attr((void *)&(scn->cam->beta), ptr, DOUBLE);
	if ((ptr = ft_search_attr(attr, "gamma:", FTSA_IN_SCOPE)))
		ft_read_attr((void *)&(scn->cam->gamma), ptr, DOUBLE);
	if ((ptr = ft_search_attr(attr, "fov:", FTSA_IN_SCOPE)))
		ft_read_attr((void *)&(scn->cam->fov), ptr, DOUBLE);
	if (scn->cam->fov < FOV_MIN)
		scn->cam->fov = FOV_MIN;
	else if (scn->cam->fov > FOV_MAX)
		scn->cam->fov = FOV_MAX;
}
