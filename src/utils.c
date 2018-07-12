//
// Created by Dimon on 12.07.2018.
//

#include "../rtv1.h"

t_point		ft_rotate_vector(t_point vec,
								double alpha, double beta, double gamma)
{
	t_point		rotated;
	double		sins[3];
	double		coss[3];

	sins[0] = sin(alpha);
	sins[1] = sin(beta);
	sins[2] = sin(gamma);
	coss[0] = cos(alpha);
	coss[1] = cos(beta);
	coss[2] = cos(gamma);
	rotated.x = vec.x * coss[2] * coss[1] +
				vec.y * (coss[2] * sins[1] * sins[0] - sins[2] * coss[0]) +
				vec.z * (sins[2] * sins[0] + coss[0] * coss[2] * sins[1]);
	rotated.y = vec.x * coss[1] * sins[2] +
				vec.y * (coss[0] * coss[2] + sins[0] * sins[1] * sins[2]) +
				vec.z * (coss[0] * sins[1] * sins[2] - sins[0] * coss[2]);
	rotated.z = vec.x * -(sins[1]) +
				vec.y * sins[0] * coss[1] +
				vec.z * coss[0] * coss[1];
	return (rotated);
}

double		ft_torad(double degrees)
{
	return (degrees * M_PI / 180.0);
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
