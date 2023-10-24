#include "cub3d.h"

void	bresenham_line(t_cub3d *cub3d, t_point p1, t_point p2)
{
	t_point	delta;
	t_point	sign;
	t_point	cur;
	int		err[2];

	delta.x = ft_abs(p2.x - p1.x);
	delta.y = ft_abs(p2.y - p1.y);
	sign.x = get_sign(p1.x, p2.x);
	sign.y = get_sign(p1.y, p2.y);
	err[0] = delta.x - delta.y;
	cur = p1;
	while (cur.x != p2.x || cur.y != p2.y)
	{
		cub3d_put_pixel(cub3d->img, cur.x, cur.y, cur.c);
		calc_step(err, &cur, &delta, &sign);
	}
	cub3d_put_pixel(cub3d->img, cur.x, cur.y, cur.c);
}

void	calc_step(int *err, t_point *p, t_point *delta, t_point *s)
{
	err[1] = 2 * err[0];
	if (err[1] > -delta->y)
	{
		err[0] -= delta->y;
		p->x += s->x;
	}
	if (err[1] < delta->x)
	{
		err[0] += delta->x;
		p->y += s->y;
	}
}

int	get_sign(int i, int j)
{
	if (i < j)
		return (1);
	return (-1);
}

void	cub3d_put_pixel(mlx_image_t *img, int x, int y, t_color c)
{
	if (x < 0 || x >= (int)(img->width))
		return ;
	if (y < 0 || y >= (int)(img->height))
		return ;
	mlx_put_pixel(img, x, y, c.c);
}
