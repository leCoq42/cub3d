/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaan <mhaan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:21:17 by mhaan             #+#    #+#             */
/*   Updated: 2023/11/06 16:21:18 by mhaan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_straight(t_player *player, int **map, double move_speed, bool fwd)
{
	double	*x_pos;
	double	*y_pos;

	x_pos = &player->x_pos;
	y_pos = &player->y_pos;
	if (!fwd)
		move_speed *= -1;
	if (map[(int)*y_pos][(int)(*x_pos + player->x_dir * move_speed)] == 0)
		*x_pos += player->x_dir * move_speed;
	if (map[(int)(*y_pos + player->y_dir * move_speed)][(int)*x_pos] == 0)
		*y_pos += player->y_dir * move_speed;
}

void	move_strafe(t_player *player, int **map, double move_speed, bool right)
{
	double	*x_pos;
	double	*y_pos;

	x_pos = &player->x_pos;
	y_pos = &player->y_pos;
	if (!right)
		move_speed *= -1;
	if (map[(int)*y_pos][(int)(*x_pos + player->x_plane * move_speed)] == 0)
		*x_pos += player->x_plane * move_speed;
	if (map[(int)(*y_pos + player->y_plane * move_speed)][(int)*x_pos] == 0)
		*y_pos += player->y_plane * move_speed;
}

void	move_rotate(t_player *player, double rot_spd, bool right)
{
	double	old_dir_x;
	double	old_plane_x;

	if (!right)
		rot_spd *= -1;
	old_dir_x = player->x_dir;
	player->x_dir = player->x_dir * cos(-rot_spd)
		- player->y_dir * sin(-rot_spd);
	player->y_dir = old_dir_x * sin(-rot_spd) + player->y_dir * cos(-rot_spd);
	old_plane_x = player->x_plane;
	player->x_plane = player->x_plane * cos(-rot_spd)
		- player->y_plane * sin(-rot_spd);
	player->y_plane = old_plane_x * sin(-rot_spd)
		+ player->y_plane * cos(-rot_spd);
}
