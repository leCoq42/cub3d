#include "MLX42.h"
#include "cub3d.h"

static void	init_view(t_player *player, t_point_cub st_pos);

bool	init_cub3d(t_cub3d	*cub3d)
{
	cub3d->mlx = mlx_init(screenWidth, screenHeight, "cub3D", true);
	if (!cub3d->mlx)
		return (false);
	cub3d->img = mlx_new_image(cub3d->mlx, screenWidth, screenHeight);
	if (!cub3d->img)
		return (false);
	init_player(&cub3d->player, cub3d->st_pos);
	cub3d->bg_color = 0x00000000;
	return (cub3d);
}

void	init_player(t_player *player, t_point_cub st_pos)
{
	player->x_pos = st_pos.x_pos;
	player->y_pos = st_pos.y_pos;
	player->move_speed = 5.0;
	player->rot_speed = 5.0;
	init_view(player, st_pos);
}

static void	init_view(t_player *player, t_point_cub st_pos)
{
	if (st_pos.dir == 'N')
	{
		player->y_dir = -1;
		player->x_plane = -1;
	}
	if (st_pos.dir == 'E')
	{
		player->x_dir = 1;
		player->y_plane = -1;
	}
	if (st_pos.dir == 'S')
	{
		player->y_dir = 1;
		player->x_plane = 1;
	}
	if (st_pos.dir == 'W')
	{
		player->x_dir = -1;
		player->y_plane = 1;
	}
}

t_ray	init_ray(t_player player, int x, int w)
{
	t_ray	ray;

	ray.camera_x = 2 * x / (double)w - 1;
	ray.ray_dir_x = player.x_dir + player.x_plane * ray.camera_x;
	ray.ray_dir_y = player.y_dir + player.y_plane * ray.camera_x;
	ray.map_x = (int)player.x_pos;
	ray.map_y = (int)player.y_pos;
	if (ray.ray_dir_x == 0)
		ray.delta_dist_x = 1e30;
	else
		ray.delta_dist_x = fabs(1 / ray.ray_dir_x);
	if (ray.ray_dir_y == 0)
		ray.delta_dist_y = 1e30;
	else
		ray.delta_dist_y = fabs(1 / ray.ray_dir_y);
	return (ray);
}
