#include "cub3d.h"

void	cub3d_hooks(t_cub3d *cub3d)
{
	mlx_cursor_hook(cub3d->mlx, &mouse_func_cb, cub3d);
	mlx_resize_hook(cub3d->mlx, &resize_func_cb, cub3d);
	mlx_loop_hook(cub3d->mlx, &player_controls, cub3d);
	mlx_key_hook(cub3d->mlx, &key_hooks, cub3d);
	mlx_loop_hook(cub3d->mlx, &close_mlx, cub3d);
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

void	player_controls(void *param)
{
	t_cub3d		*cub3d;
	double		frametime;
	double		move_speed;
	double		rot_speed;

	cub3d = (t_cub3d *)param;
	frametime = show_fps(cub3d);
	move_speed = cub3d->player.move_speed * frametime;
	rot_speed = cub3d->player.rot_speed * frametime;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_A))
		move_strafe(&cub3d->player, cub3d->int_arr, move_speed, false);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_D))
		move_strafe(&cub3d->player, cub3d->int_arr, move_speed, true);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_W))
		move_straight(&cub3d->player, cub3d->int_arr, move_speed, true);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_S))
		move_straight(&cub3d->player, cub3d->int_arr, move_speed, false);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_RIGHT))
		move_rotate(&cub3d->player, rot_speed, true);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_LEFT))
		move_rotate(&cub3d->player, rot_speed, false);
	cub3d_draw_image(cub3d, cub3d->img->width, cub3d->img->height);
}

void	resize_func_cb(int32_t width, int32_t height, void *param)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)param;
	mlx_resize_image(cub3d->img, width, height);
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
