
#include "../rtv1.h"

t_env	*ft_envnew(char *file_name)
{
	t_env	*e;

	e = (t_env *)ft_smemalloc(sizeof(t_env), "ft_envnew");
	e->mlx = mlx_init();
	e->scn = ft_get_scene(file_name);
	e->win = mlx_new_window(e->mlx, WIN_WIDTH, WIN_HEIGHT, e->scn->name);
	e->img = ft_imgnew(e);
	return (e);
}
