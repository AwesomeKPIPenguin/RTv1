
#include "../rtv1.h"

int 		ft_usage()
{
	ft_putendl("Usage: ./RTv1 scene_file");
	return (1);
}

int			main(int ac, char **av)
{
	t_scene		*scn;

	if (ac != 2)
		return (ft_usage());
	scn = ft_get_scene(av[1]);

	(void)scn;
	return (0);
}
