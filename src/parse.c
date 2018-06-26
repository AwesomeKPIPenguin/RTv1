
#include "../rtv1.h"


void		ft_parse(char *content, t_scene *scn)
{
	char	*attr;

	if ((attr = ft_search_attr(content, "scene")))
		ft_parse_scene(attr, scn);
	else if ((attr = ft_search_attr(content, "light")))
		ft_parse_light(attr, scn);
}

