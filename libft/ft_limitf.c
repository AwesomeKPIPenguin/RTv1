//
// Created by Dmytro OMELCHENKO on 7/27/18.
//

double	ft_limitf(double min, double max, double num)
{
	if (num < min)
		return (min);
	if (num > max)
		return (max);
	return (num);
}
