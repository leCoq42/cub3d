#include "cub3d.h"

uint32_t	pixels_to_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	uint32_t	color;
	color = 0;
	color |= (uint32_t)r << 24;
	color |= (uint32_t)g << 16;
	color |= (uint32_t)b << 8;
	color |= (uint32_t)a;
	return (color);
}
// TODO: img->width and img->height should not be > INT_MAX
t_color	get_color(t_cub3d *cub3d, int32_t x, int32_t y)
{
	t_color	color;
	int32_t	start;

	color.c = 0;
	if (x < 0 || x >= (int)(cub3d->img->width))
		return (color);
	if (y < 0 || y >= (int)(cub3d->img->height))
		return (color);
	start = y * cub3d->img->width + x;
	if (start > (int32_t)(cub3d->img->width * cub3d->img->height - 3))
		return (color);
	color.t_rgba.r = cub3d->img->pixels[start];
	color.t_rgba.g = cub3d->img->pixels[start + 1];
	color.t_rgba.b = cub3d->img->pixels[start + 2];
	color.t_rgba.a = cub3d->img->pixels[start + 3];
	return (color);
}
