/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaan <mhaan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:21:02 by mhaan             #+#    #+#             */
/*   Updated: 2023/11/06 16:21:03 by mhaan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_color	get_pixel_color(t_cub3d *cub3d, int32_t x, int32_t y)
{
	t_color		color;
	uint32_t	start;

	color.c = 0;
	if (x < 0 || x >= (int)(cub3d->img->width))
		return (color);
	if (y < 0 || y >= (int)(cub3d->img->height))
		return (color);
	start = (y * cub3d->img->width + x) * 4;
	if (start > (cub3d->img->width * cub3d->img->height * 4) - 5)
		return (color);
	color.t_rgba.r = cub3d->img->pixels[start];
	color.t_rgba.g = cub3d->img->pixels[start + 1];
	color.t_rgba.b = cub3d->img->pixels[start + 2];
	color.t_rgba.a = cub3d->img->pixels[start + 3];
	return (color);
}

void	set_pixel_color(t_cub3d *cub3d, t_color color, uint32_t img_idx)
{
	cub3d->img->pixels[img_idx] = color.t_rgba.a;
	cub3d->img->pixels[img_idx + 1] = color.t_rgba.b;
	cub3d->img->pixels[img_idx + 2] = color.t_rgba.g;
	cub3d->img->pixels[img_idx + 3] = color.t_rgba.r;
}
