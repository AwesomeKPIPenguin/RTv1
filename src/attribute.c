//
// Created by Dimon on 23.06.2018.
//

#include "../rtv1.h"

char		*ft_search_attr(char *content, char *attr, int ftsa_mode)
{
	int		curve_count;
	int		is_comment;

	if (!ft_strcmp(attr, ""))
		return (content);
	curve_count = ftsa_mode;
	is_comment = 0;
	while (*content)
	{
		if (*content == '{')
			++curve_count;
		else if (*content == '}')
			--curve_count;
		else if (*content == '#')
			is_comment = 1;
		else if (is_comment && *content == '\n')
			is_comment = 0;
		if (curve_count == ftsa_mode && !is_comment && *content == *attr)
			if (!ft_strncmp(content, attr, ft_strlen(attr)))
				return (content);
		++content;
	}
	return (NULL);
}

void		ft_read_attr(void *dst, char *attr, int type)
{
	char			*data;
	char			*to_free;
	long long		i;

	while (*attr && *attr != ':')
		++attr;
	++attr;
	if ((i = (long long)ft_strchr(attr, ';') - (long long)attr) < 0)
		ft_error("invalid scene file");
	data = ft_strsub(attr, 0, i);
	to_free = data;
	data = ft_strtrim(data);
	free(to_free);
	if (type == KOEF)
		*((double *)dst) = ft_limitf(0, 1, ft_atod(data));
	else if (type == DOUBLE)
		*((double *)dst) = ft_atod(data);
	else if (type == STRING)
		*((char **)dst) = ft_strdup(data);
	else if (type == POINT)
		*((t_point *)dst) = ft_atopoint(data);
	else
		(*((t_color *)dst)).val = ft_atoi_base(data, 16);
}
