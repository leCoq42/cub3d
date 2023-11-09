/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaan <mhaan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:21:04 by mhaan             #+#    #+#             */
/*   Updated: 2023/11/06 16:21:06 by mhaan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub3d_draw_image(t_cub3d *cub3d, int32_t screen_w, int32_t screen_h)
{
	mlx_image_t	*img;
	int32_t		bg_color;
	int32_t		x;

	img = cub3d->img;
	bg_color = cub3d->bg_color;
	ft_memset(img->pixels, bg_color, screen_w * screen_h * 4);
	cast_floor_ceiling(cub3d, screen_w, screen_h);
	x = 0;
	while (x < screen_w)
	{
		cast_walls(cub3d, screen_w, screen_h, x);
		x++;
	}
}

void	draw_vert(t_cub3d *cub3d, t_line line)
{
	while (line.y_start < line.y_end)
	{
		cub3d_put_pixel(cub3d->img, line.x, line.y_start,
			get_pixel_color(cub3d, line.x, line.y_start));
		line.y_start++;
	}
}

void	cub3d_put_pixel(mlx_image_t *img, int32_t x, int32_t y, t_color c)
{
	if (x < 0 || x >= (int)(img->width))
		return ;
	if (y < 0 || y >= (int)(img->height))
		return ;
	mlx_put_pixel(img, x, y, c.c);
}
