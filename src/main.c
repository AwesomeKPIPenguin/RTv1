
#include "../rtv1.h"

int 		ft_usage()
{
	ft_putendl("Usage: ./RTv1 scene_file");
	return (1);
}

int			main(int ac, char **av)
{
	t_env		*e;

//	printf("START\n\n");

	if (ac != 2)
		return (ft_usage());
	e = ft_envnew(av[1]);
	ft_render(e);
	mlx_loop(e->mlx);
	return (0);
}
