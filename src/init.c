#include "cub3d.h"

t_cub3d	*init_cub3d(void)
{
	t_cub3d	*cub3d;

	cub3d = ft_calloc(1, sizeof(t_cub3d));
	if (!cub3d)
		return (NULL);
	
	cub3d->mlx = mlx_init(screenWidth, screenHeight, "cub3D", true);
	if (!cub3d->mlx)
		return (NULL);
	cub3d->img = mlx_new_image(cub3d->mlx, screenWidth, screenHeight);
	if (!cub3d->img)
		return (NULL);
	init_player(&cub3d->player);
	cub3d->bg_color = 200;
	cub3d->wu = 0;
	return (cub3d);
}

void	init_player(t_player *player)
{
	player->x_pos = 22.0;
	player->y_pos = 12.0;
	player->x_dir = -1.0;
	player->y_dir = 0.0;
	player->x_plane = 0.0;
	player->y_plane = 0.66;
}

t_point	init_point(int x, int y, int z, uint32_t c)
{
	t_point	point;

	point.x = x;
	point.y = y;
	point.z = z;
	point.c.c = c;
	return (point);
}
