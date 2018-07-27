//
// Created by Dmytro OMELCHENKO on 7/27/18.
//

int		ft_limit(int min, int max, int num)
{
	if (num < min)
		return (min);
	if (num > max)
		return (max);
	return (num);
}
