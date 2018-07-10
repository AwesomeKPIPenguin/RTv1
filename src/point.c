//
// Created by Dimon on 26.06.2018.
//

#include "../rtv1.h"

t_point		ft_pointnew(double x, double y, double z)
{
	t_point	point;
	
	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

t_point		ft_atopoint(char *str)
{
	t_point		point;
	
	while (*str && *str != '(')
		++str;
	if (!*str)
		ft_error("invalid scene file");
	point.x = ft_atod(++str);
	while (*str && *str != ',')
		++str;
	if (!*str)
		ft_error("invalid scene file");
	point.y = ft_atod(++str);
	while (*str && *str != ',')
		++str;
	if (!*str)
		ft_error("invalid scene file");
	point.z = ft_atod(++str);
	while (*str && *str != ')')
		++str;
	if (!*str)
		ft_error("invalid scene file");
	return (point);
}

double		ft_get_dist(t_point pnt_0, t_point pnt_1)
{
	return (sqrt(pow(pnt_1.x - pnt_0.x, 2) +
				pow(pnt_1.y - pnt_0.y, 2) +
				pow(pnt_1.z - pnt_0.z, 2)));
}
