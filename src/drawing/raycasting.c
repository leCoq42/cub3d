#include "cub3d.h"

void	calc_step(t_ray *ray, t_player *player);
void	calc_line(t_line *line, t_ray *ray, int32_t h, int32_t x);
void	perform_dda(t_cub3d *cub3d, t_ray *ray);

void	cast_floor_ceiling(t_cub3d *cub3d, int32_t w, int32_t h)
{
	t_color		color;
	int			x;
	int			y;
	uint32_t	img_idx;

	y = h / 2 + 1;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			img_idx = (y * w + x) * 4;
			color.c = cub3d->f_col;
			set_pixel_color(cub3d, color, img_idx);
			color.c = cub3d->c_col;
			img_idx = ((h - y - 1) * w + x) * 4;
			set_pixel_color(cub3d, color, img_idx);
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
	ray = init_ray(player, x, w);
	calc_step(&ray, &player);
	perform_dda(cub3d, &ray);
	calc_line(&line, &ray, h, x);
	ray.tex_num = get_tex_num(ray.side, ray.step_x, ray.step_y);
	if (ray.side == 0)
		ray.wall_x = player.y_pos + ray.perp_wall_dist * ray.ray_dir_y;
	else
		ray.wall_x = player.x_pos + ray.perp_wall_dist * ray.ray_dir_x;
	ray.wall_x -= floor(ray.wall_x);
	ray.tex_x = (int)(ray.wall_x * (double)cub3d->textures[ray.tex_num]->width);
	if (ray.side == 0 && ray.ray_dir_x > 0)
		ray.tex_x = cub3d->textures[ray.tex_num]->width - ray.tex_x - 1;
	if (ray.side == 1 && ray.ray_dir_y < 0)
		ray.tex_x = cub3d->textures[ray.tex_num]->width - ray.tex_x - 1;
	ray.step = 1.0 * cub3d->textures[ray.tex_num]->height / ray.line_height;
	ray.tex_pos = (line.y_start - (h / 2) + (ray.line_height / 2)) * ray.step;
	tex_to_img(cub3d, &ray, &line, w);
	draw_vert(cub3d, line);
}

void	calc_step(t_ray *ray, t_player *player)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->x_pos - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->x_pos)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->y_pos - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->y_pos)
			* ray->delta_dist_y;
	}
}

void	perform_dda(t_cub3d *cub3d, t_ray *ray)
{
	bool	hit;

	hit = false;
	while (hit == false)
	{
		if (ray->side_dist_x < ray->side_dist_y)
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
		if (cub3d->int_arr[ray->map_y][ray->map_x] > 0)
			hit = true;
	}
}

void	calc_line(t_line *line, t_ray *ray, int32_t h, int32_t x)
{
	line->x = x;
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	ray->line_height = (int)(h / ray->perp_wall_dist);
	line->y_start = -ray->line_height / 2 + h / 2;
	if (line->y_start < 0)
		line->y_start = 0;
	line->y_end = ray->line_height / 2 + h / 2;
	if (line->y_end >= h)
		line->y_end = h - 1;
}
