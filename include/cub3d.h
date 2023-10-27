#ifndef CUB3D_H
# define CUB3D_H

#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <math.h>

#include "MLX42.h"
#include "libft.h"
#include "ft_printf.h"
#include "get_next_line_bonus.h"

#include <stdio.h>

#define screenWidth 1080
#define screenHeight 720
#define mapWidth 24
#define mapHeight 24
#define texWidth 64
#define texHeight 64

typedef union color
{
	uint32_t	c;
	struct s_rgba
	{
		uint8_t	r;
		uint8_t	g;
		uint8_t	b;
		uint8_t	a;
	}	t_rgba;
}	t_color;

typedef struct s_point
{
	int32_t	x;
	int32_t	y;
	int32_t	z;
	t_color	c;
	char	type;
}	t_point;

typedef struct s_map
{
	int32_t	width;
	int32_t	height;
	t_point	**grid;
}	t_map;

typedef struct s_player
{
	double	x_pos;
	double	x_dir;
	double	x_plane;
	double	y_pos;
	double	y_dir;
	double	y_plane;
}	t_player;

typedef struct s_cub3d
{
	t_player		player;
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_texture_t	*textures[8];
	double			time;
	double			oldtime;
	uint32_t		bg_color;
	int8_t			wu;
}	t_cub3d;

typedef struct s_line
{
	double	grad;
	double	intery;
	int		x;
}	t_line;

static int worldMap[mapWidth][mapHeight] =
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

/* static int worldMap[mapWidth][mapHeight]= */
/* { */
/*   {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7}, */
/*   {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7}, */
/*   {4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7}, */
/*   {4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7}, */
/*   {4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7}, */
/*   {4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7}, */
/*   {4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1}, */
/*   {4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8}, */
/*   {4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1}, */
/*   {4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8}, */
/*   {4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1}, */
/*   {4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1}, */
/*   {6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6}, */
/*   {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4}, */
/*   {6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6}, */
/*   {4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3}, */
/*   {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2}, */
/*   {4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2}, */
/*   {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2}, */
/*   {4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2}, */
/*   {4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2}, */
/*   {4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2}, */
/*   {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2}, */
/*   {4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3} */
/* }; */

// Function prototypes
void	cub3d_draw_image(t_cub3d *cub3d, int32_t mapwidth, int32_t mapheight);
void	draw_line(t_cub3d *cub3d, t_point p1, t_point p2);

// bresenham.c
void	bresenham_line(t_cub3d *cub3d, t_point p1, t_point p2);
void	calc_step(int *err, t_point *p, t_point *delta, t_point *s);
int		get_sign(int i, int j);

// wu_line.c
void	wu_line(t_cub3d *cub3d, t_point p1, t_point p2);

// init.c
t_cub3d	*init_cub3d(void);
void	init_player(t_player *player);
t_point	init_point(int x, int y, int z, uint32_t c);
int		init_textures(mlx_texture_t **textures);
// move.c
void	user_controls(t_cub3d *cub3d);
void	player_move_hooks(void *param);

// draw.c
void	draw_vert(t_cub3d *cub3d, int32_t x, int32_t y_start, int32_t y_end);
void	cub3d_put_pixel(mlx_image_t *img, int32_t x, int32_t y, t_color c);

// color.c
uint32_t	pixels_to_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
t_color		get_color(t_cub3d *cub3d, int32_t x, int32_t y);

#endif
