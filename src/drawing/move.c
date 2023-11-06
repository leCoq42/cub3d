#include "MLX42.h"
#include "cub3d.h"

void	close_mlx(void *param);

static void resize_func_cb(int32_t width, int32_t height, void *param)
{
	t_cub3d *cub3d;
	cub3d = (t_cub3d *)param;
	// printf("new width = %d and new height =  %d\n", width,  height);
	mlx_resize_image(cub3d->img, width, height);
}

void	user_controls(t_cub3d *cub3d)
{
	mlx_cursor_hook(cub3d->mlx, &mouse_func_cb, cub3d);
	mlx_resize_hook(cub3d->mlx, &resize_func_cb, cub3d);
	mlx_loop_hook(cub3d->mlx, &player_move_hooks, cub3d);
	mlx_key_hook(cub3d->mlx, &key_hooks, cub3d);
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
		if (cub3d->int_arr[(int)player->y_pos][(int)(player->x_pos - (player->y_dir) * strafeSpeed)] == false)
			player->x_pos -= (player->y_dir) * strafeSpeed;
		if (cub3d->int_arr[(int)(player->y_pos + (player->x_dir) * strafeSpeed)][(int)player->x_pos] == false)
			player->y_pos += (player->x_dir) * strafeSpeed;
	}
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_D))
	{
		if (cub3d->int_arr[(int)player->y_pos][(int)(player->x_pos + (player->y_dir) * strafeSpeed)] == false)
			player->x_pos += (player->y_dir) * strafeSpeed;
		if (cub3d->int_arr[(int)(player->y_pos - (player->x_dir) * strafeSpeed)][(int)player->x_pos] == false)
			player->y_pos -= (player->x_dir) * strafeSpeed;
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
	show_fps(cub3d, 0);
	cub3d_draw_image(cub3d, cub3d->img->width, cub3d->img->height);
}

void	key_hooks(mlx_key_data_t keydata, void *param)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)param;

	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_F)
			show_fps(cub3d, true);
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
