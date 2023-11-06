/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaan <mhaan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:20:33 by mhaan             #+#    #+#             */
/*   Updated: 2023/11/06 16:20:35 by mhaan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	flood_fill_check(t_cub3d *cub3d, size_t pos_x, size_t pos_y, char tar)
{
	char	wall;
	char	rep;

	wall = '1';
	rep = 'c';
	if (pos_x >= cub3d->map_width || pos_x < 0)
		return (1);
	if (pos_y >= cub3d->map_height || pos_y < 0)
		return (1);
	if (cub3d->char_arr[pos_y][pos_x] == wall || \
				cub3d->char_arr[pos_y][pos_x] == rep)
		return (0);
	else if (cub3d->char_arr[pos_y][pos_x] != cub3d->st_pos.dir && \
							cub3d->char_arr[pos_y][pos_x] != tar)
		return (1);
	cub3d->char_arr[pos_y][pos_x] = rep;
	if (flood_fill_check(cub3d, pos_x + 1, pos_y, tar) == 1)
		return (1);
	if (flood_fill_check(cub3d, pos_x - 1, pos_y, tar) == 1)
		return (1);
	if (flood_fill_check(cub3d, pos_x, pos_y + 1, tar) == 1)
		return (1);
	if (flood_fill_check(cub3d, pos_x, pos_y - 1, tar) == 1)
		return (1);
	return (0);
}

int	flood_fill_repair(t_cub3d *cub3d, size_t pos_x, size_t pos_y, char tar)
{
	char	wall;
	char	rep;

	wall = '1';
	rep = '0';
	if (pos_x >= cub3d->map_width || pos_x < 0)
		return (1);
	if (pos_y >= cub3d->map_height || pos_y < 0)
		return (1);
	if (cub3d->char_arr[pos_y][pos_x] == wall || \
				cub3d->char_arr[pos_y][pos_x] == rep)
		return (0);
	else if (cub3d->char_arr[pos_y][pos_x] != cub3d->st_pos.dir && \
							cub3d->char_arr[pos_y][pos_x] != tar)
		return (1);
	cub3d->char_arr[pos_y][pos_x] = rep;
	if (flood_fill_repair(cub3d, pos_x + 1, pos_y, tar) == 1)
		return (1);
	if (flood_fill_repair(cub3d, pos_x - 1, pos_y, tar) == 1)
		return (1);
	if (flood_fill_repair(cub3d, pos_x, pos_y + 1, tar) == 1)
		return (1);
	if (flood_fill_repair(cub3d, pos_x, pos_y - 1, tar) == 1)
		return (1);
	return (0);
}
