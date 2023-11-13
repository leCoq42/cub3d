/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaan <mhaan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:21:13 by mhaan             #+#    #+#             */
/*   Updated: 2023/11/06 16:21:14 by mhaan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		rotate_mouse(x_shift, &cub3d->player, 0.005);
	else if (xpos < mid_screen && x_shift < 0)
		rotate_mouse(x_shift, &cub3d->player, 0.005);
	cub3d->mouse_x = xpos;
}

void	rotate_mouse(int x_shift, t_player *player, double rot_speed)
{
	double			old_dirx;
	double			old_planex;
	const double	cos_rot = cos(-rot_speed * x_shift);
	const double	sin_rot = sin(-rot_speed * x_shift);

	old_dirx = player->x_dir;
	player->x_dir = player->x_dir * cos_rot - \
						player->y_dir * sin_rot;
	player->y_dir = old_dirx * sin_rot + \
						player->y_dir * cos_rot;
	old_planex = player->x_plane;
	player->x_plane = player->x_plane * cos_rot - \
						player->y_plane * sin_rot;
	player->y_plane = old_planex * sin_rot + \
					player->y_plane * cos_rot;
}
