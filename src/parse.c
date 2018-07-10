
#include "../rtv1.h"


void		ft_parse(char *content, t_scene *scn)
{
	char	*attr;

	if ((attr = ft_search_attr(content, "scene", FTSA_GLOBALLY)))
		ft_parse_scene(attr, scn);
	if ((attr = ft_search_attr(content, "light", FTSA_GLOBALLY)))
		ft_parse_light(attr, scn);
	if ((attr = ft_search_attr(content, "sphere", FTSA_GLOBALLY)))
		ft_parse_sphere(attr, scn);
}

void		ft_lstpush_sort(t_scene *scn, t_object *obj)
{
	t_list	*prev;
	t_list	*curr;
	t_list	*node;

	prev = NULL;
	curr = scn->objs;
	node = ft_nodenew((void *)obj, sizeof(t_object));
	while (curr)
	{
		if (obj->cam_dist < ((t_object *)(curr->content))->cam_dist)
		{
			if (prev)
				prev->next = node;
			else
				scn->objs = node;
			node->next = curr;
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
	if (prev)
		prev->next = node;
	else
		ft_lstpush(&(scn->objs), node);
}

char		*ft_get_curve(char *attr)
{
	while (*attr && *attr != '{')
		++attr;
	if (!*attr)
		ft_error("invalid scene file");
	return (attr + 1);
}
