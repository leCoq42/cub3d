#include "cub3d.h"
#include <stdint.h>

void	draw_vert(t_cub3d *cub3d, int32_t x, int32_t y_start, int32_t y_end)
{
	while (y_start < y_end)
	{
		cub3d_put_pixel(cub3d->img, x, y_start, get_color(cub3d, x, y_start));
		y_start++;
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
