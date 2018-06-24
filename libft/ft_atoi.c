/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 18:49:36 by domelche          #+#    #+#             */
/*   Updated: 2018/03/31 14:14:30 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_getstart(char *str, int *sign)
{
	int		i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	*sign = (str[i] == '-') ? -1 : 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] == '0')
		i++;
	return (&(str[i]));
}

long long	ft_atoi(const char *str)
{
	char				*s;
	int					sign;
	int					str_len;
	unsigned long long	res;
	size_t				i;

	if (!str)
		return (0);
	res = 0;
	s = ft_getstart((char *)str, &sign);
	str_len = 0;
	i = 0;
	while (ft_isdigit(s[i]))
	{
		res = res * 10 + (s[i++] - '0');
		++str_len;
	}
	if ((res > LONG_MAX || str_len > 19) && sign > 0)
		return (-1);
	if ((res - 1 > LONG_MAX || str_len > 19) && sign < 0)
		return (0);
	return ((long long)(res * sign));
}
