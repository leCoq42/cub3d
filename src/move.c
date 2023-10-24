#include "cub3d.h"

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

	cub3d = (t_cub3d *)param;
	player = &cub3d->player;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_A))
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = player->x_dir;
		player->x_dir = player->x_dir * cos(rotSpeed) - player->y_dir * sin(rotSpeed);
		player->y_dir = oldDirX * sin(rotSpeed) + player->y_dir * cos(rotSpeed);
		double oldPlaneX = player->x_plane;
		player->x_plane = player->x_plane * cos(rotSpeed) - player->y_plane * sin(rotSpeed);
		player->y_plane = oldPlaneX * sin(rotSpeed) + player->y_plane * cos(rotSpeed);
	}
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_D))
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = player->x_dir;
		player->x_dir = player->x_dir * cos(-rotSpeed) - player->y_dir * sin(-rotSpeed);
		player->y_dir = oldDirX * sin(-rotSpeed) + player->y_dir * cos(-rotSpeed);
		double oldPlaneX = player->x_plane;
		player->x_plane = player->x_plane * cos(-rotSpeed) - player->y_plane * sin(-rotSpeed);
		player->y_plane = oldPlaneX * sin(-rotSpeed) + player->y_plane * cos(-rotSpeed);
	}
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_W))
	{
		if (worldMap[(int)(player->x_pos + player->x_dir * moveSpeed)][(int)player->y_pos] == false)
			player->x_pos += player->x_dir * moveSpeed;
		if(worldMap[(int)player->x_pos][(int)(player->y_pos + player->y_dir * moveSpeed)] == false)
			player->y_pos += player->y_dir * moveSpeed;
	}
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_S))
	{
		if (worldMap[(int)(player->x_pos - player->x_dir * moveSpeed)][(int)player->y_pos] == false)
			player->x_pos -= player->x_dir * moveSpeed;
		if(worldMap[(int)player->x_pos][(int)(player->y_pos - player->y_dir * moveSpeed)] == false)
			player->y_pos -= player->y_dir * moveSpeed;
	}
	// if (mlx_is_key_down(fdf->mlx, MLX_KEY_UP))
	// else if (mlx_is_key_down(fdf->mlx, MLX_KEY_DOWN))
	// check_cam_limits(fdf->camera, fdf->map, fdf->img);
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
