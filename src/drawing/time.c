/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaan <mhaan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:21:26 by mhaan             #+#    #+#             */
/*   Updated: 2023/11/06 16:21:30 by mhaan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	show_fps(t_cub3d *cub3d)
{
	static double	old_time = 0;
	double			new_time;
	double			frametime;

	new_time = mlx_get_time();
	frametime = (new_time - old_time);
	if (cub3d->show_fps == true)
		printf("FPS: %.0f\n", 1 / frametime);
	return (old_time = new_time, frametime);
}
