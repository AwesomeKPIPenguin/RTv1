
#include "../rtv1.h"

t_scene		*ft_scenenew(void)
{
	t_scene	*scn;

	scn = ft_smemalloc(sizeof(t_scene), "ft_scenenew");
	scn->bg_color.val = 0;
	scn->name = ft_strdup("New Scene");
	scn->cam = ft_cameranew();
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
	if ((ptr = ft_search_attr(attr, "world_color:", FTSA_IN_SCOPE)))
		ft_read_attr((void *)&(scn->bg_color), ptr, COLOR);
}


