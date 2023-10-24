#ifndef CUB3D_H
# define CUB3D_H

#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <math.h>

#include "MLX42.h"
// #include "libft.h"
// #include "ft_printf.h"
// #include "get_next_line_bonus.h"

typedef struct s_node
{
	char			*str;
	struct s_node	*next;
}							t_node;
//***********************************STRUCTS***********************************
typedef struct s_map
{
	int						map_height;
	int						map_width;
	int						total_points;
	char					*allowed_values;
	t_node					**llist;
	char					**arr;
	mlx_image_t				*img;
	mlx_t					*mlx;
}							t_map;


//***********************************PROTOTYPES***********************************
// 				MAP_CHECK
int				check_filename(char *map_name);
void			check_values(char *line, const char *allowed_values);

// 				FILE_TO_LLIST
void			file_to_llist(int fd, t_map *map);
t_node			*add_node(char *line, t_map *map, t_node *prev_node);
t_node			*list_add_back(t_node **llist, t_node *new_node, t_node *prev_node);

// 				LLIST_TO_ARR
void			llist_to_array(t_map *map);
t_node 			*fill_row(char *row, t_node *curr, t_map *map);
int				ft_isspace(int c);

// 				PARSE
t_map 			*parse_map(char *filename);

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
