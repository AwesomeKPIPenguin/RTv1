//
// Created by Dimon on 10.07.2018.
//

#include	"../rtv1.h"

t_object	*ft_objectnew()
{
	t_object	*obj;

	obj = ft_smemalloc(sizeof(t_object), "ft_objectnew");
	obj->color.val = 0xffff00;
	return (obj);
}
