#include "MLX42.h"
#include "cub3d.h"

void	close_mlx(void *param);

void	user_controls(t_cub3d *cub3d)
{
	mlx_loop_hook(cub3d->mlx, &player_move_hooks, cub3d);
	mlx_key_hook(cub3d->mlx, &key_hooks, cub3d);
	mlx_loop_hook(cub3d->mlx, &close_mlx, cub3d);
}

void	player_move_hooks(void *param)
{
	t_cub3d		*cub3d;
	t_player	*player;
	double		frametime;
	float		moveSpeed;
	float		rotSpeed;

	cub3d = (t_cub3d *)param;
	player = &cub3d->player;
	frametime = show_fps(cub3d);
	moveSpeed = player->move_speed * frametime;
	rotSpeed = player->rot_speed * frametime;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_A))
	{
		if (cub3d->int_arr[(int)player->y_pos][(int)(player->x_pos - player->x_plane * moveSpeed)] == false)
			player->x_pos -= player->x_plane * moveSpeed;
		if (cub3d->int_arr[(int)(player->y_pos - player->y_plane * moveSpeed)][(int)player->x_pos] == false)
			player->y_pos -= player->y_plane * moveSpeed;
	}
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_D))
	{
		if (cub3d->int_arr[(int)player->y_pos][(int)(player->x_pos + player->x_plane * moveSpeed)] == false)
			player->x_pos += player->x_plane * moveSpeed;
		if (cub3d->int_arr[(int)(player->y_pos + player->y_plane * moveSpeed)][(int)player->x_pos] == false)
			player->y_pos += player->y_plane * moveSpeed;
	}
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_W))
	{
		if (cub3d->int_arr[(int)player->y_pos][(int)(player->x_pos + player->x_dir * moveSpeed)] == false)
			player->x_pos += player->x_dir * moveSpeed;
		if (cub3d->int_arr[(int)(player->y_pos + player->y_dir * moveSpeed)][(int)player->x_pos] == false)
			player->y_pos += player->y_dir * moveSpeed;
	}
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_S))
	{
		if (cub3d->int_arr[(int)player->y_pos][(int)(player->x_pos - player->x_dir * moveSpeed)] == false)
			player->x_pos -= player->x_dir * moveSpeed;
		if (cub3d->int_arr[(int)(player->y_pos - player->y_dir * moveSpeed)][(int)player->x_pos] == false)
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
	cub3d_draw_image(cub3d, cub3d->mlx->width, cub3d->mlx->height);
}

void	key_hooks(mlx_key_data_t keydata, void *param)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)param;
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_F)
		{
			if (cub3d->show_fps == false)
				cub3d->show_fps = true;
			else if (cub3d->show_fps == true)
				cub3d->show_fps = false;
		}
	}
}

void	close_mlx(void *param)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)param;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_ESCAPE))
	{
		printf("Closing.\n");
		mlx_close_window(cub3d->mlx);
	}
}
