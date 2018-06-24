//
// Created by Dimon on 22.06.2018.
//

#include "libft.h"

int		ft_isspace(int c)
{
	return (((c >= 9 && c <= 13) || c == 32) ? 1 : 0);
}
