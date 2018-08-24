//
// Created by Dimon on 24.08.2018.
//

#include "../rtv1.h"

t_light_node	ft_light_node_new(t_light *light)
{
	t_light_node	lnode;

	lnode.light = light;
	lnode.is_visible = 0;
	return (lnode);
}
