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
	cub3d->bg_color = 200;
	// init_textures(cub3d->textures);
	return (cub3d);
}

void	init_player(t_player *player, t_point_cub st_pos)
{
	player->x_pos = st_pos.x_pos;
	player->y_pos = st_pos.y_pos;
	player->move_speed = 5.0;
	player->rot_speed = 5.0;
	player->strafe_speed = 3.0;
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
