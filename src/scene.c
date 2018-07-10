
#include "../rtv1.h"

t_scene		*ft_scenenew(void)
{
	t_scene	*scn;

	scn = ft_smemalloc(sizeof(t_scene), "ft_scenenew [for scene]");
	scn->dist = ft_smemalloc(1024 * sizeof(double), "ft_scenenew [for dist]");
	scn->name = "New Scene";
	scn->cam = ft_smemalloc(sizeof(t_camera), "ft_scenenew [for camera]");
	return (scn);
}

t_scene			*ft_get_scene(char *file_name)
{
	t_scene		*scn;
	int			fd;

	scn = ft_scenenew();
	if ((fd = open(file_name, O_RDONLY)) < 0)
		ft_error("cannot open file");
	if ((read(fd, NULL, 0)) < 0)
		ft_error("cannot read file");
	ft_parse(ft_readfile(file_name), scn);
	return (scn);
}

void		ft_parse_scene(char *attr, t_scene *scn)
{
	char	*ptr;

	attr = ft_get_curve(attr);
	if ((ptr = ft_search_attr(attr, "name:", FTSA_IN_SCOPE)))
		ft_read_attr((void *)&(scn->name), ptr, STRING);
	if ((ptr = ft_search_attr(attr, "cam:", FTSA_IN_SCOPE)))
		ft_read_attr((void *)&(scn->cam->origin), ptr, POINT);
	if ((ptr = ft_search_attr(attr, "cam_alpha:", FTSA_IN_SCOPE)))
		ft_read_attr((void *)&(scn->cam->alpha), ptr, DOUBLE);
	if ((ptr = ft_search_attr(attr, "cam_beta:", FTSA_IN_SCOPE)))
		ft_read_attr((void *)&(scn->cam->beta), ptr, DOUBLE);
	if ((ptr = ft_search_attr(attr, "cam_gamma:", FTSA_IN_SCOPE)))
		ft_read_attr((void *)&(scn->cam->gamma), ptr, DOUBLE);
}


