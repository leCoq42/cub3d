#include "MLX42.h"
#include "cub3d.h"

void	mouse_func_cb(double xpos, double ypos, void *param)
{
	t_cub3d	*cub3d;
	int		x_shift;
	int		mid_screen;

	(void)(ypos);
	cub3d = (t_cub3d *) param;
	mid_screen = cub3d->img->width / 2;
	x_shift = xpos - cub3d->mouse_x;
	if (xpos > mid_screen && x_shift > 0)
		rotate_mouse(x_shift, &cub3d->player);
	else if (xpos < mid_screen && x_shift < 0)
		rotate_mouse(x_shift, &cub3d->player);
	cub3d->mouse_x = xpos;
}

void	rotate_mouse(int x_shift, t_player *player)
{
	float	rotSpeed;

	rotSpeed = 0.005;
	double oldDirX = player->x_dir;
	player->x_dir = player->x_dir * cos(-rotSpeed * x_shift) - player->y_dir * sin(-rotSpeed * x_shift);
	player->y_dir = oldDirX * sin(-rotSpeed * x_shift) + player->y_dir * cos(-rotSpeed * x_shift);
	double oldPlaneX = player->x_plane;
	player->x_plane = player->x_plane * cos(-rotSpeed * x_shift) - player->y_plane * sin(-rotSpeed * x_shift);
	player->y_plane = oldPlaneX * sin(-rotSpeed * x_shift) + player->y_plane * cos(-rotSpeed * x_shift);
}