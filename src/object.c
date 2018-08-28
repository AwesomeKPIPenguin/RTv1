/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 13:25:05 by domelche          #+#    #+#             */
/*   Updated: 2018/08/23 13:27:08 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../rtv1.h"

t_object	*ft_objectnew(void)
{
	t_object	*obj;

	obj = ft_smemalloc(sizeof(t_object), "ft_objectnew");
	obj->color.val = 0xffff00;
	obj->ambnt = 0.1;
	obj->diff = 1.0;
	obj->phong = 0.2;
	return (obj);
}

static void	ft_balance_koefs(t_object *o)
{
	double	sum;

	sum = o->diff + o->trans + o->spclr;
	if (sum > 1.0)
	{
		o->diff /= sum;
		o->trans /= sum;
		o->spclr /= sum;
	}
}

t_object	*ft_parse_object(char *attr)
{
	t_object	*o;
	char		*ptr;

	o = ft_objectnew();
	attr = ft_get_curve(attr, '{');
	if ((ptr = ft_search_attr(attr, "color:", FTSA_IN_SCOPE)))
		ft_read_attr((void *)(&(o->color)), ptr, COLOR);
	if ((ptr = ft_search_attr(attr, "ambnt:", FTSA_IN_SCOPE)))
		ft_read_attr((void *)(&(o->ambnt)), ptr, KOEF);
	if ((ptr = ft_search_attr(attr, "diff:", FTSA_IN_SCOPE)))
		ft_read_attr((void *)(&(o->diff)), ptr, KOEF);
	if ((ptr = ft_search_attr(attr, "spclr:", FTSA_IN_SCOPE)))
		ft_read_attr((void *)(&(o->spclr)), ptr, KOEF);
	if ((ptr = ft_search_attr(attr, "s_blur:", FTSA_IN_SCOPE)))
		ft_read_attr((void *)(&(o->s_blur)), ptr, KOEF);
	if ((ptr = ft_search_attr(attr, "trans:", FTSA_IN_SCOPE)))
		ft_read_attr((void *)(&(o->trans)), ptr, KOEF);
	if ((ptr = ft_search_attr(attr, "t_blur:", FTSA_IN_SCOPE)))
		ft_read_attr((void *)(&(o->t_blur)), ptr, KOEF);
	if ((ptr = ft_search_attr(attr, "phong:", FTSA_IN_SCOPE)))
		ft_read_attr((void *)(&(o->phong)), ptr, KOEF);
	ft_balance_koefs(o);
	return (o);
}
