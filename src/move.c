#include "cub3d.h"
#include <math.h>

void	close_mlx(void *param);

void	user_controls(t_cub3d *cub3d)
{
	mlx_loop_hook(cub3d->mlx, &player_move_hooks, cub3d);
	mlx_loop_hook(cub3d->mlx, &close_mlx, cub3d);
}

void	player_move_hooks(void *param)
{
	t_cub3d		*cub3d;
	t_player	*player;
	float		moveSpeed = 0.05;
	float		rotSpeed = 0.05;
	float		strafeSpeed = 0.05;

	cub3d = (t_cub3d *)param;
	player = &cub3d->player;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_A))
	{
		if (worldMap[(int)(player->x_pos - (player->y_dir) * strafeSpeed)][(int)player->y_pos] == false)
			player->x_pos -= (player->y_dir) * strafeSpeed;
		if (worldMap[(int)player->x_pos][(int)(player->y_pos + (player->x_dir) * strafeSpeed)] == false)
			player->y_pos += (player->x_dir) * strafeSpeed;
	}
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_D))
	{
		if (worldMap[(int)(player->x_pos + (player->y_dir) * strafeSpeed)][(int)player->y_pos] == false)
			player->x_pos += (player->y_dir) * strafeSpeed;
		if (worldMap[(int)player->x_pos][(int)(player->y_pos - (player->x_dir) * strafeSpeed)] == false)
			player->y_pos -= (player->x_dir) * strafeSpeed;
	}
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_W))
	{
		if (worldMap[(int)(player->x_pos + player->x_dir * moveSpeed)][(int)player->y_pos] == false)
			player->x_pos += player->x_dir * moveSpeed;
		if (worldMap[(int)player->x_pos][(int)(player->y_pos + player->y_dir * moveSpeed)] == false)
			player->y_pos += player->y_dir * moveSpeed;
	}
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_S))
	{
		if (worldMap[(int)(player->x_pos - player->x_dir * moveSpeed)][(int)player->y_pos] == false)
			player->x_pos -= player->x_dir * moveSpeed;
		if (worldMap[(int)player->x_pos][(int)(player->y_pos - player->y_dir * moveSpeed)] == false)
			player->y_pos -= player->y_dir * moveSpeed;
	}
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_RIGHT))
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = player->x_dir;
		player->x_dir = player->x_dir * cos(-rotSpeed) - player->y_dir * sin(-rotSpeed);
		player->y_dir = oldDirX * sin(-rotSpeed) + player->y_dir * cos(-rotSpeed);
		double oldPlaneX = player->x_plane;
		player->x_plane = player->x_plane * cos(-rotSpeed) - player->y_plane * sin(-rotSpeed);
		player->y_plane = oldPlaneX * sin(-rotSpeed) + player->y_plane * cos(-rotSpeed);
	}
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_LEFT))
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = player->x_dir;
		player->x_dir = player->x_dir * cos(rotSpeed) - player->y_dir * sin(rotSpeed);
		player->y_dir = oldDirX * sin(rotSpeed) + player->y_dir * cos(rotSpeed);
		double oldPlaneX = player->x_plane;
		player->x_plane = player->x_plane * cos(rotSpeed) - player->y_plane * sin(rotSpeed);
		player->y_plane = oldPlaneX * sin(rotSpeed) + player->y_plane * cos(rotSpeed);
	}
	cub3d_draw_image(cub3d, screenWidth, screenHeight);
}

void	close_mlx(void *param)
{
	t_cub3d	*cub3d;

	cub3d = param;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_ESCAPE))
	{
		printf("Closing.\n");
		mlx_close_window(cub3d->mlx);
	}
}
