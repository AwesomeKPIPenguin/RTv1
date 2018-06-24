//
// Created by Dimon on 23.06.2018.
//

#include "../rtv1.h"

void		ft_read_attr(void *dst, char *attr, int type)
{
	char			*data;
	char			*to_free;
	unsigned long	i;

	while (*attr && *attr != ':')
		++attr;
	++attr;
	if ((i = ft_strchr(attr, ';') - attr) < 0)
		ft_error("invalid scene file");
	data = ft_strsub(attr, 0, i);
	to_free = data;
	data = ft_strtrim(data);
	free(to_free);
	if (type == BYTE)
		*((t_byte *)dst) = (t_byte)ft_atoi(data);
	else if (type == DOUBLE)
		*((double *)dst) = ft_atod(data);
	else if (type == STRING)
		*((char **)dst) = ft_strdup(data);
	else if (type == POINT)
		*((t_point **)dst) = ft_atopoint(data);
	else
		(*((t_color *)dst)).val = ft_atoi_base(data);
}
