/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaan <mhaan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:21:22 by mhaan             #+#    #+#             */
/*   Updated: 2023/11/06 16:21:24 by mhaan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_tex_num(int side, int stepX, int stepY)
{
	if (side == 0)
	{
		if (stepX > 0)
			return (EAST);
		else
			return (WEST);
	}
	else
	{
		if (stepY > 0)
			return (SOUTH);
		else
			return (NORTH);
	}
}

void	tex_to_img(t_cub3d *cub3d, t_ray *ray, t_line *line, int32_t w)
{
	int32_t		y;
	t_color		color;
	uint32_t	tex_idx;
	uint32_t	img_idx;

	y = line->y_start;
	while (y < line->y_end)
	{
		ray->tex_y = (int)ray->tex_pos
			& (cub3d->textures[ray->tex_num]->height - 1);
		ray->tex_pos += ray->step;
		tex_idx = (cub3d->textures[ray->tex_num]->width * ray->tex_y
				+ ray->tex_x) * 4;
		img_idx = (y * w + line->x) * 4;
		color.t_rgba.a = cub3d->textures[ray->tex_num]->pixels[tex_idx + 3];
		color.t_rgba.b = cub3d->textures[ray->tex_num]->pixels[tex_idx + 2];
		color.t_rgba.g = cub3d->textures[ray->tex_num]->pixels[tex_idx + 1];
		color.t_rgba.r = cub3d->textures[ray->tex_num]->pixels[tex_idx];
		set_pixel_color(cub3d, color, img_idx);
		y++;
	}
}
