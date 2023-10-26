#ifndef CUB3D_H
# define CUB3D_H

#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <math.h>
#include <fcntl.h>
#include <stdio.h>

#include "MLX42.h"
#include "libft.h"
// #include "ft_printf.h"
#include "get_next_line_bonus.h"

//***********************************STRUCTS***********************************
typedef struct s_node
{
	char			*str;
	struct s_node	*next;
}
							t_node;
typedef struct s_point_cub
{
	size_t	x_pos;
	size_t	y_pos;
	char	dir;
}							t_point_cub;
typedef struct s_map
{
	size_t					height;
	size_t					width;
	size_t					total_points;
	char					*allowed_values;
	char					*file_str;
	t_node					**llist;
	char					**arr;
	mlx_image_t				*img;
	mlx_t					*mlx;
}							t_map;

typedef struct s_cub3d
{
	t_map			*map;
	char			*map_str;
	char			**arr;
	t_point_cub		st_pos;
	size_t			map_width;
	size_t			map_height;
	uint32_t		c_col;
	uint32_t		f_col;
	mlx_texture_t	*n_texture;
	mlx_texture_t	*e_texture;
	mlx_texture_t	*s_texture;
	mlx_texture_t	*w_texture;
	// t_player	player;
	// mlx_t		*mlx;
	// mlx_image_t	*img;
	// double		time;
	// double		oldtime;
}	t_cub3d;

//***********************************PROTOTYPES***********************************
// 				PARSE
t_cub3d 		*parse_file(char *filename);

// 				PARSING_UTILS
int				check_filename(char *map_name);
void			skip_chars(char *str, size_t *i, char *set);
bool			is_present(char *set, char c);
// void			check_values(char *line, const char *allowed_values);

// 				PARSE_HEADER
bool			parse_header(int fd, t_cub3d *cub3d);
char 			*file_to_str(int fd);
bool			is_identifier(char *str);
bool			extract_info(char *str, size_t *i, t_cub3d *cub3d);
bool			info_is_valid(t_cub3d *cub3d, size_t *i, char *file_str);

// 				COLOR
bool			get_color(char *file_str, t_cub3d *cub3d, char c, size_t *i);
int				get_r_g_b(char *file_str, size_t *i);
uint32_t		combine_rgb(int r, int g, int b);

// 				TEXTURE
bool			get_texture(char *file_str, t_cub3d *cub3d, char c, size_t *i);
bool			check_path(t_cub3d *cub3d, char identifier, char *tex_path);

// 				PARSE_MAP
bool			parse_map(t_cub3d *cub3d);
bool			validate_values(char *str);
int				flood_fill(t_cub3d *cub3d, size_t pos_x, size_t pos_y, char tar, char rep);


// 				GET_MAP_INFO
bool			get_dimensions(char **arr, t_cub3d *cub3d);
// bool 			find_start_pos(char **arr, t_cub3d *cub3d);


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
	int32_t	z;
	t_color	c;
	char	type;
}	t_point;

// typedef struct s_map
// {
// 	int32_t	width;
// 	int32_t	height;
// 	t_point	**grid;
// }	t_map;

typedef struct s_player
{
	double	x_pos;
	double	y_pos;
}	t_player;


#endif
