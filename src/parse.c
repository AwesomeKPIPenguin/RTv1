
#include "../rtv1.h"

char			*ft_search_attr_in_scope(char *content, char *attr)
{
	int		curve_count;

	if (!ft_strcmp(attr, ""))
		return (content);
	curve_count = 1;
	while (*content)
	{
		if (*content == '{')
			++curve_count;
		else if (*content == '}')
			--curve_count;
		if (!curve_count)
			return (NULL);
		if (curve_count == 1 && *content == *attr)
			if (!ft_strncmp(content, attr, ft_strlen(attr)))
				return (content);
		content++;
	}
	return (NULL);
}

char			*ft_search_attr(char *content, char *attr)
{
	int		curve_count;

	if (!ft_strcmp(attr, ""))
		return (content);
	curve_count = 0;
	while (*content)
	{
		if (*content == '{')
			++curve_count;
		else if (*content == '}')
			--curve_count;
		if (!curve_count && *content == *attr)
			if (!ft_strncmp(content, attr, ft_strlen(attr)))
				return (content);
		content++;
	}
	return (NULL);
}

static void		ft_parse(char *content, t_scene *scn)
{
	char	*attr;

	if ((attr = ft_search_attr(content, "scene")))
		ft_parse_scene(attr, scn);
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
