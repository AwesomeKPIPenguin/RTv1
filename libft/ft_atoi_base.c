//
// Created by Dimon on 25.06.2018.
//

#include "libft.h"
#include "atoi_basic.h"

long long	ft_atoi_base(const char *str, int base)
{
	if (!str || base < 2 || base > 16)
		return (0);
	return (ft_atoi_basic(str, base));
}
