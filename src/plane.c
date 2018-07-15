//
// Created by Dimon on 15.07.2018.
//

#include "../rtv1.h"

t_plane		*ft_planenew(void)
{
	t_plane	*pln;

	pln = ft_smemalloc(sizeof(t_plane), "ft_planenew");
	pln->origin = ft_pointnew(0.0, -1000.0, 0.0);
	pln->norm = ft_pointnew(0.0, 1.0, 0.0);
	return (pln);
}


