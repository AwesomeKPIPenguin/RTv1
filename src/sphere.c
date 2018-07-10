//
// Created by Dimon on 10.07.2018.
//

#include "../rtv1.h"

t_sphere	*ft_spherenew()
{
	t_sphere	*sph;

	sph = ft_smemalloc(sizeof(t_sphere), "ft_spherenew");
	return (sph);
}

void		ft_parse_sphere(char *attr, t_scene *scn)
{
	t_object	*obj;
	t_sphere	*sph;
	char		*ptr;

	obj = ft_objectnew();
	sph = ft_spherenew();
	attr = ft_get_curve(attr);
	if ((ptr = ft_search_attr(attr, "origin:", FTSA_IN_SCOPE)))
		ft_read_attr((void *)(&(sph->origin)), ptr, POINT);
	if ((ptr = ft_search_attr(attr, "radius:", FTSA_IN_SCOPE)))
		ft_read_attr((void *)(&(sph->radius)), ptr, DOUBLE);
	if ((ptr = ft_search_attr(attr, "color:", FTSA_IN_SCOPE)))
		ft_read_attr((void *)(&(obj->color)), ptr, COLOR);
	if ((ptr = ft_search_attr(attr, "spclr:", FTSA_IN_SCOPE)))
		ft_read_attr((void *)(&(obj->spclr)), ptr, BYTE);
	if ((ptr = ft_search_attr(attr, "trans:", FTSA_IN_SCOPE)))
		ft_read_attr((void *)(&(obj->trans)), ptr, BYTE);
	obj->fig = sph;
	obj->cam_dist = ft_get_dist(scn->cam->origin, sph->origin) - sph->radius;
	ft_lstpush_sort(scn, obj);
}
