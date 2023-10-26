#include "cub3d.h"

// void	swap_points(t_point *p1, t_point *p2, int steep);
// void	draw_pix(t_cub3d *cub3d, t_color c, t_line line, int steep);
// void	ft_swap(int *a, int *b);

float	fpart(float x);
int		ipart(float x);

/* Xiaolin Wu's line drawing algorithm */
void	wu_line(t_cub3d *cub3d, t_point p1, t_point p2)
{
	float	dx = p2.x - p1.x;
	float	dy = p2.y - p1.y;
	float	gradient = dy / dx;
	t_color	p_color;

	float error = 0.0f;
	for (int x = p1.x; x <= p2.x; x++)
	{
		int y = round(p1.y + gradient * (x - p1.x));

		// Calculate the intensity values for the subpixels
		float intensity = 1.0f - fpart(error);
		float subpixelIntensity = fpart(error);

		// Perform anti-aliasing by gradually blending the intensity values of subpixels
		p_color.c = (uint32_t)(p1.c.c * intensity + (p1.c.c * subpixelIntensity));

		// Draw the pixel
		cub3d_put_pixel(cub3d->img, x, y, p_color);
	}
}

/* Calculate the fractional part of a number */
float	fpart(float x)
{
	return (x - ipart(x));
}

/* Calculate the integer part of a number */
int	ipart(float x)
{
	return ((int)x);
}




// void	wu_line(t_cub3d *cub3d, t_point p1, t_point p2)
// {
// 	t_point		delta;
// 	t_line		line;
// 	const int	steep = ft_abs(p2.y - p1.y) >= ft_abs(p2.x - p1.x);
//
// 	if (steep)
// 		swap_points(&p1, &p2, 1);
// 	if (p1.x > p2.x)
// 		swap_points(&p1, &p2, 0);
// 	delta.x = p2.x - p1.x;
// 	delta.y = p2.y - p1.y;
// 	if (delta.x != 0)
// 		line.grad = (double)delta.y / delta.x;
// 	else
// 		line.grad = 0;
// 	line.intery = p1.y + line.grad;
// 	line.x = p1.x + 1;
// 	while (line.x <= p2.x)
// 	{
// 		draw_pix(cub3d, p2.c, line, steep);
// 		line.intery += line.grad;
// 		line.x++;
// 	}
// }
//
// void	swap_points(t_point *p1, t_point *p2, int steep)
// {
// 	t_color	tmp;
//
// 	if (steep)
// 	{
// 		ft_swap(&p1->x, &p1->y);
// 		ft_swap(&p2->x, &p2->y);
// 	}
// 	else
// 	{
// 		ft_swap(&p1->x, &p2->x);
// 		ft_swap(&p1->y, &p2->y);
// 		tmp = p1->c;
// 		p1->c = p2->c;
// 		p2->c = tmp;
// 	}
// }
//
// void	draw_pix(t_cub3d *cub3d, t_color c, t_line line, int steep)
// {
// 	if (steep)
// 	{
// 		// c.t_rgba.a = (uint8_t)((1 - (line.intery - floor(line.intery))) * 255);
// 		fdf_put_pixel(cub3d->img, (int)line.intery, line.x, c);
// 		// c.t_rgba.a = (uint8_t)((line.intery - floor(line.intery)) * 255);
// 		fdf_put_pixel(cub3d->img, (int)line.intery + 1, line.x, c);
// 	}
// 	else
// 	{
// 		// c.t_rgba.a = (uint8_t)((1 - (line.intery - floor(line.intery))) * 255);
// 		fdf_put_pixel(cub3d->img, line.x, (int)line.intery, c);
// 		// c.t_rgba.a = (uint8_t)((line.intery - floor(line.intery)) * 255);
// 		fdf_put_pixel(cub3d->img, line.x, (int)line.intery + 1, c);
// 	}
// }
//
// void	ft_swap(int *a, int *b)
// {
// 	int	tmp;
//
// 	tmp = *a;
// 	*a = *b;
// 	*b = tmp;
// }
