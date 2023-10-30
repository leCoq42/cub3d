#include "MLX42.h"
#include "cub3d.h"

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
	// player->x_pos = 22.0;
	// player->y_pos = 12.0;
	player->x_pos = st_pos.x_pos;
	player->y_pos = st_pos.y_pos;
	player->x_dir = -1.0;
	player->y_dir = 0.0;
	player->x_plane = 0.0;
	player->y_plane = 0.66;
	player->move_speed = 5.0;
	player->rot_speed = 5.0;
	player->strafe_speed = 3.0;
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

// int	init_textures(mlx_texture_t **textures)
// {
// 	textures[0] = mlx_load_png("./textures/pics/eagle.png");
// 	textures[1] = mlx_load_png("./textures/pics/redbrick.png");
// 	textures[2] = mlx_load_png("./textures/pics/purplestone.png");
// 	textures[3] = mlx_load_png("./textures/pics/greystone.png");
// 	textures[4] = mlx_load_png("./textures/pics/bluestone.png");
// 	textures[5] = mlx_load_png("./textures/pics/mossy.png");
// 	textures[6] = mlx_load_png("./textures/pics/wood.png");
// 	textures[7] = mlx_load_png("./textures/pics/colorstone.png");
// 	return (0);
// }
