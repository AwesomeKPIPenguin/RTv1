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
	point.x = ft_atod(&(++str));
	while (*str && *str != ',')
		++str;
	if (!*str)
		ft_error("invalid scene file");
	point.y = ft_atod(&(++str));
	while (*str && *str != ',')
		++str;
	if (!*str)
		ft_error("invalid scene file");
	point.z = ft_atod(&(++str));
	while (*str && *str != ')')
		++str;
	if (!*str)
		ft_error("invalid scene file");
	return (point);
}
