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
#include "ft_printf.h"
#include "get_next_line_bonus.h"

#define screenWidth 1920
#define screenHeight 1080
#define mapWidth 24
#define mapHeight 24
#define texWidth 64
#define texHeight 64
#define FONT_WIDTH 90
#define FONT_HEIGHT 90

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

//***********************************STRUCTS***********************************

typedef struct s_line
{
	int32_t	y_start;
	int32_t	y_end;
	int32_t	x;
}	t_line;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int32_t	map_x;
	int32_t	map_y;
	int32_t	step_x;
	int32_t	step_y;
	int32_t	side;
	int32_t	line_height;
	int32_t	tex_num;
	double	wall_x;
	int32_t	tex_x;
	int32_t	tex_y;
	double	step;
	double	tex_pos;
}	t_ray;

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

typedef struct s_player
{
	double	x_pos;
	double	x_dir;
	double	x_plane;
	double	y_pos;
	double	y_dir;
	double	y_plane;
	double	move_speed;
	double	rot_speed;
}	t_player;

typedef struct s_point_cub
{
	size_t	x_pos;
	size_t	y_pos;
	char	dir;
}	t_point_cub;

typedef struct s_cub3d
{
	char			*map_str;
	mlx_texture_t	*textures[4];
	uint32_t		c_col;
	uint32_t		f_col;
	char			**char_arr;
	int				**int_arr;
	t_point_cub		st_pos;
	size_t			map_width;
	size_t			map_height;
	t_player		player;
	mlx_t			*mlx;
	mlx_image_t		*img;
	uint32_t		bg_color;
	double			time;
	double			oldtime;
	bool			show_fps;
	double			mouse_x;
}	t_cub3d;

//***********************************PROTOTYPES***********************************
// 				PARSE
t_cub3d 		*parse_file(char *filename);

// 				PARSING_UTILS
int				check_filename(char *map_name);
void			skip_chars(char *str, size_t *i, char *set);
bool			is_present(char *set, char c);
char			*strjoin_free(char *s1, char *s2);

// 				PARSE_HEADER
bool			parse_header(int fd, t_cub3d *cub3d);
char 			*file_to_str(int fd);
bool			is_identifier(char *str);
bool			extract_info(char *str, size_t *i, t_cub3d *cub3d);
bool			info_is_valid(t_cub3d *cub3d, size_t *i, char *file_str);

// 				COLOR
bool			get_color_header(char *file_str, t_cub3d *cub3d, char c, size_t *i);
int				get_r_g_b(char *file_str, size_t *i);
uint32_t		combine_rgb(int r, int g, int b);
void			set_pixel_color(t_cub3d *cub3d, t_color color, uint32_t img_idx);

// 				TEXTURE
bool			get_texture(char *file_str, t_cub3d *cub3d, char c, size_t *i);
bool			check_path(t_cub3d *cub3d, char identifier, char *tex_path);
int				ft_isspace(int c);

// 				PARSE_MAP
bool			parse_map(t_cub3d *cub3d);
bool			validate_values(char *str);
bool			create_int_arr(t_cub3d *cub3d);
bool			fill_int_arr(t_cub3d *cub3d);

// 				GET_MAP_INFO
bool			get_dimensions(char **arr, t_cub3d *cub3d);
// void 			print_char_array(char **arr);
// void 			print_int_array(int **arr, size_t h, size_t w);
int				flood_fill_check(t_cub3d *cub3d, size_t pos_x, size_t pos_y, char tar);
int				flood_fill_repair(t_cub3d *cub3d, size_t pos_x, size_t pos_y, char tar);

//				raycasting.c
void			cast_floor_ceiling(t_cub3d *cub3d, int32_t w, int32_t h);
void			cast_walls(t_cub3d *cub3d, int32_t w, int32_t h, int32_t x);

//				init.c
bool			init_cub3d(t_cub3d	*cub3d);
void			init_player(t_player *player, t_point_cub st_pos);
int				init_textures(mlx_texture_t **textures);
t_ray			init_ray(t_player player, int x, int w);

//				move.c
void			move_straight(t_player *player, int **map, double move_speed, bool fwd);
void			move_strafe(t_player *player, int **map, double move_speed, bool right);
void			move_rotate(t_player *player, double rot_spd, bool right);

//				hooks.c
void			cub3d_hooks(t_cub3d *cub3d);
void			player_controls(void *param);
void			key_hooks(mlx_key_data_t keydata, void *param);
void			resize_func_cb(int32_t width, int32_t height, void *param);
void			close_mlx(void *param);

//				draw.c
void			cub3d_draw_image(t_cub3d *cub3d, int32_t mapwidth, int32_t mapheight);
void			draw_vert(t_cub3d *cub3d, t_line line);
void			cub3d_put_pixel(mlx_image_t *img, int32_t x, int32_t y, t_color c);

//				color.c
t_color			get_pixel_color(t_cub3d *cub3d, int32_t x, int32_t y);

//				drawing/textures.c
int				get_tex_num(int side, int stepX, int stepY);
void			tex_to_img(t_cub3d *cub3d, t_ray *ray, t_line *line, int32_t w);

// time.c
double			show_fps(t_cub3d *cub3d);

// 				GET_MAP_INFO
void			clean_cub3d(t_cub3d *cub3d);
void			clean_textures(t_cub3d *cub3d);
void			clean_char_arr(char **arr);
void			clean_int_arr(int **arr, int h);

// 				MOUSE
void			mouse_func_cb(double xpos, double ypos, void *param);
void			rotate_mouse(int x_shift, t_player *player);

#endif
