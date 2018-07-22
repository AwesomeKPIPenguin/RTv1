//
// Created by Dimon on 10.07.2018.
//

#include	"../rtv1.h"

t_object	*ft_objectnew(void)
{
	t_object	*obj;

	obj = ft_smemalloc(sizeof(t_object), "ft_objectnew");
	obj->color.val = 0xffff00;
	return (obj);
}

t_object	*ft_parse_object(char *attr)
{
	t_object	*o;
	char		*ptr;

	o = ft_objectnew();
	attr = ft_get_curve(attr, '{');
	if ((ptr = ft_search_attr(attr, "color:", FTSA_IN_SCOPE)))
		ft_read_attr((void *)(&(o->color)), ptr, COLOR);
	if ((ptr = ft_search_attr(attr, "spclr:", FTSA_IN_SCOPE)))
		ft_read_attr((void *)(&(o->spclr)), ptr, BYTE);
	if ((ptr = ft_search_attr(attr, "trans:", FTSA_IN_SCOPE)))
		ft_read_attr((void *)(&(o->trans)), ptr, BYTE);
	return (o);
}
