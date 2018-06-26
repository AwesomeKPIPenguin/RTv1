
#include "../rtv1.h"

t_scene		*ft_scenenew(void)
{
	t_scene	*scn;

	scn = ft_smemalloc(sizeof(t_scene), "ft_scenenew [for scene]");
	return (scn);
}

t_scene			*ft_get_scene(char *file_name)
{
	t_scene		*scn;
	int			fd;
	char		*content;

	scn = ft_scenenew();
	if ((fd = open(file_name, O_RDONLY)) < 0)
		ft_error("cannot open file");
	if ((read(fd, 0, NULL)) < 0)
		ft_error("cannot read file");
	ft_parse(ft_readfile(file_name), scn);
	return (scn);
}

void		ft_parse_scene(char *attr, t_scene *scn)
{
	char	*ptr;

	while (*attr && *attr != '{')
		++attr;
	if (!*attr)
		ft_error("invalid scene file");
	if ((ptr = ft_search_attr_in_scope(attr, "name:")))
		ft_read_attr((void *)scn->name, ptr, STRING);
	else if ((ptr = ft_search_attr_in_scope(attr, "cam:")))
		ft_read_attr((void *)&(scn->cam), ptr, POINT);
}
