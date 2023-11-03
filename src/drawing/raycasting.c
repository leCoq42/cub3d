#include "MLX42.h"
#include "cub3d.h"
#include <stdint.h>

void	cast_floor_and_ceiling(t_cub3d *cub3d, int32_t w, int32_t h);
void	cast_walls(t_cub3d *cub3d, int32_t w, int32_t h, int32_t x);
int		get_tex_num(int side, int stepX, int stepY);
void	calc_step(t_ray *ray, t_player *player);
void	calc_line(t_line *line, t_ray *ray, int32_t h);
void	tex_to_img(t_cub3d *cub3d, t_ray *ray, int32_t w, int32_t x);
t_ray	*init_ray(t_player player, int x, int w);

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

void	perform_dda(t_cub3d *cub3d, t_ray *ray)
{
	bool	hit;

	//perform DDA
	hit = false;
	while (hit == false)
	{
		//jump to next map square, either in x-direction, or in y-direction
		if(ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		//Check if ray has hit a wall
		if (cub3d->int_arr[ray->map_y][ray->map_x] > 0)
			hit = true;
	}
}

void cast_floor_and_ceiling(t_cub3d *cub3d, int32_t w, int32_t h)
{
	t_color		color;
	int			x;
	int			y;
	uint32_t	img_idx;

	// for(int y = h / 2 + 1; y < h; ++y)
	y = h / 2 + 1;
	while (y < h)
	{
		// for(int x = 0; x < w; ++x)
		x = 0;
		while (x < w)
		{
			img_idx = (y * w + x) * 4;
			color.c = cub3d->f_col;
			cub3d->img->pixels[img_idx + 3] = color.t_rgba.r;
			cub3d->img->pixels[img_idx + 2] = color.t_rgba.g;
			cub3d->img->pixels[img_idx + 1] = color.t_rgba.b;
			cub3d->img->pixels[img_idx + 0] = color.t_rgba.a;

			color.c = cub3d->c_col;
			img_idx = ((h - y - 1) * w + x) * 4;
			cub3d->img->pixels[img_idx + 3] = color.t_rgba.r;
			cub3d->img->pixels[img_idx + 2] = color.t_rgba.g;
			cub3d->img->pixels[img_idx + 1] = color.t_rgba.b;
			cub3d->img->pixels[img_idx + 0] = color.t_rgba.a;
			x++;
		}
		y++;
	}
}

void	cast_walls(t_cub3d *cub3d, int32_t w, int32_t h, int32_t x)
{
	t_player	player;
	t_ray		ray;
	t_line		line;

	player = cub3d->player;
	ray = init_ray(cub3d, player, x, w);
	calc_step(&ray, &player);
	if (ray.side == 0)
		ray.perp_wall_dist = (ray.side_dist_x - ray.delta_dist_x);
	else
		ray.perp_wall_dist = (ray.side_dist_y - ray.delta_dist_y);
	calc_line(&line, &ray, h);

	//texturing calculations
	ray.tex_num = get_tex_num(ray.side, ray.step_x, ray.step_y);

	//calculate value of wallX
	if (ray.side == 0)
		ray.wall_x = player.y_pos + ray.perp_wall_dist * ray.ray_dir_y;
	else
		ray.wall_x = player.x_pos + ray.perp_wall_dist * ray.ray_dir_x;
	ray.wall_x -= floor(ray.wall_x);

	//x coordinate on the texture
	ray.tex_x = (int)(ray.wall_x * (double)cub3d->textures[ray.tex_num]->width);
	if (ray.side == 0 && ray.ray_dir_x > 0)
		ray.tex_x = cub3d->textures[ray.tex_num]->width - ray.tex_x - 1;
	if (ray.side == 1 && ray.ray_dir_y < 0)
		ray.tex_x = cub3d->textures[ray.tex_num]->width - ray.tex_x - 1;

	// An integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
	// How much to increase the texture coordinate per screen pixel
	ray.step = 1.0 * cub3d->textures[ray.tex_num]->height / ray.line_height;
	// Starting texture coordinate
	ray.tex_pos = ((double)line.start - (double)h / 2 + (double)ray.line_height / 2) * ray.step;
	// double texPos = (drawStart - h / 2 + lineHeight / 2) * step;
	tex_to_img(cub3d, &ray, w, x);
	draw_vert(cub3d, x, line);
}

t_ray	*init_ray(t_player player, int x, int w)
{
	t_ray	*ray;

	ray = NULL;
	ray->camera_x = 2 * x / (double)w - 1;
	ray->ray_dir_x = player.x_dir + player.x_plane * ray->camera_x;
	ray->ray_dir_y = player.y_dir + player.y_plane * ray->camera_x;
	ray->map_x = (int)player.x_pos;
	ray->map_y = (int)player.y_pos;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	return (ray);
}


void	calc_step(t_ray *ray, t_player *player)
{

	if(ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->x_pos - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->x_pos) * ray->delta_dist_x;
	}

	if(ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->y_pos - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->y_pos) * ray->delta_dist_y;
	}
}

void	calc_line(t_line *line, t_ray *ray, int32_t h)
{
	ray->line_height = (int)(h / ray->perp_wall_dist);

	//calculate lowest and highest pixel to fill in current stripe
	line->start = -ray->line_height / 2 + h / 2;
	if (line->start < 0)
		line->start = 0;
	line->end = ray->line_height / 2 + h / 2;
	if (line->end >= h)
		line->end = h - 1;
}

void	tex_to_img(t_cub3d *cub3d, t_ray *ray, int32_t w, int32_t x)
{
	// for (int y = drawStart; y < drawEnd; y++)
	int32_t y;
	t_color color;
	uint32_t tex_idx;
	uint32_t img_idx;

	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		ray->tex_y = (int)ray->tex_pos & (cub3d->textures[ray->tex_num]->height - 1);
		ray->tex_pos += ray->step;
		tex_idx = (cub3d->textures[ray->tex_num]->width * ray->tex_y + ray->tex_x) * 4;
		img_idx = (y * w + x) * 4;
		color.t_rgba.a = cub3d->textures[ray->tex_num]->pixels[tex_idx];
		color.t_rgba.b = cub3d->textures[ray->tex_num]->pixels[tex_idx + 1];
		color.t_rgba.g = cub3d->textures[ray->tex_num]->pixels[tex_idx + 2];
		color.t_rgba.r = cub3d->textures[ray->tex_num]->pixels[tex_idx + 3];
		// make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		// if (side == 1)
		// 	color.c = (color.c >> 1) & 8355711;
		cub3d->img->pixels[img_idx] = color.t_rgba.r;
		cub3d->img->pixels[img_idx + 1] = color.t_rgba.g;
		cub3d->img->pixels[img_idx + 2] = color.t_rgba.b;
		cub3d->img->pixels[img_idx + 3] = color.t_rgba.a;
		y++;
	}
}

void	cub3d_draw_image(t_cub3d *cub3d, int32_t w, int32_t h)
{
	mlx_image_t	*img;
	int32_t		bg_color;
	int32_t		x;

	img = cub3d->img;
	bg_color = cub3d->bg_color;
	ft_memset(img->pixels, bg_color, w * h * 4);
	cast_floor_and_ceiling(cub3d, w, h);
	x = 0;
	while (x < w)
	{
		cast_walls(cub3d, w, h, x);
		x++;
	}
}
