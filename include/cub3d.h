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

#define screenWidth 1080
#define screenHeight 720

typedef union color
{
	uint32_t	c;
	struct s_rgba
	{
		uint8_t	a;
		uint8_t	b;
		uint8_t	g;
		uint8_t	r;
	}	t_rgba;
}	t_color;

typedef struct s_point
{
	int32_t	x;
	int32_t	y;
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
	double	y_pos;
}	t_player;

typedef struct s_cub3d
{
	t_map		*map;
	t_player	player;
	mlx_t		*mlx;
	mlx_image_t	*img;
	double		time;
	double		oldtime;
}	t_cub3d;

#endif
