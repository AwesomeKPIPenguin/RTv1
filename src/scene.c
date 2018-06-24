
#include "../rtv1.h"

t_scene		*ft_scenenew(void)
{
	t_scene	*scn;

	scn = ft_smemalloc(sizeof(t_scene), "ft_scenenew [for scene]");
	return (scn);
}

void		ft_parse_scene(char *attr, t_scene *scn)
{
	while (*attr && *attr != '{')
		++attr;
	if (!*attr)
		ft_error("invalid scene file");
	if (ft_search_attr_in_scope(attr, "name:"))

}
