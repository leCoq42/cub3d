#include "cub3d.h"

// static void print_char_array(char **arr);
// static void print_int_array(int **arr, size_t h, size_t w);

// static void print_char_array(char **arr)
// {
// 	for (int i = 0; arr[i] != NULL; i++)
// 	{
// 		for (int j = 0; arr[i][j] != '\0'; j++)
// 		{
// 			// printf("(%d, %d) = %c", i, j, arr[i][j]);
// 			printf("%c", arr[i][j]);
// 		}
// 		printf("\n");
// 	}
// 	printf("\n");
// }

// static void print_int_array(int **arr, size_t h, size_t w)
// {
// 	for (size_t i = 0; i < h; i++)
// 	{
// 		for (size_t j = 0; j < w; j++)
// 		{
// 			// printf("(%d, %d) = %c", i, j, arr[i][j]);
// 			printf("%d", arr[i][j]);
// 		}
// 		printf("\n");
// 	}
// 	printf("\n");
// }

bool	create_int_arr(t_cub3d *cub3d)
{
	int	**int_arr;

	int_arr = malloc(cub3d->map_height * sizeof(int *));
	for (size_t i = 0; i < cub3d->map_height; i++)
	{
		int_arr[i] = malloc(cub3d->map_width * sizeof(int));
	}
	for (size_t i = 0; i < cub3d->map_height; i++)
	{
		for (size_t j = 0; j < cub3d->map_width; j++)
		{
			if (cub3d->char_arr[i][j] == '0')
				int_arr[i][j] = 0;
			else
				int_arr[i][j] = 1;
		}
	}
	cub3d->int_arr = int_arr;
	return (true);
}

bool	parse_map(t_cub3d *cub3d)
{
	if (!validate_values(cub3d->map_str))
		return (false);
	cub3d->char_arr = ft_split(cub3d->map_str, '\n');
	if (!get_dimensions(cub3d->char_arr, cub3d))
		return(perror("no start position found\n"), false);
	if (flood_fill(cub3d, cub3d->st_pos.x_pos, cub3d->st_pos.y_pos, '0', 'c'))
		return(perror("invalid map\n"), false);
	flood_fill(cub3d, cub3d->st_pos.x_pos, cub3d->st_pos.y_pos, 'c', '0');
	// print_char_array(cub3d->char_arr);
	create_int_arr(cub3d);
	// print_int_array(cub3d->int_arr, cub3d->map_height, cub3d->map_width);
	return (true);
}

bool	validate_values(char *str)
{
	size_t	i;
	uint8_t	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		skip_chars(str, &i, " 10\n");
		if (is_present("NESW", str[i]))
		{
			if (flag == 0)
				flag = 1;
			else if (flag == 1)
				return (perror("too many start positions\n"), false);
			i++;
		}
		else if (str[i] == '\0')
			break;
		else
			return (perror("invalid start position\n"), false);
	}
	if (flag == 1)
		return (true);
	return (false);
}

int flood_fill(t_cub3d *cub3d, size_t pos_x, size_t pos_y, char tar, char rep)
{
	char	wall;

	wall = '1';
	if (pos_x >= cub3d->map_width || pos_x < 0)
		return (1);
	if (pos_y >= cub3d->map_height || pos_y < 0)
		return (1);
	if (cub3d->char_arr[pos_y][pos_x] == wall || cub3d->char_arr[pos_y][pos_x] == rep)
		return (0);
	else if (cub3d->char_arr[pos_y][pos_x] != cub3d->st_pos.dir && cub3d->char_arr[pos_y][pos_x] != tar)
		return (1);
	cub3d->char_arr[pos_y][pos_x] = rep;
	if (flood_fill(cub3d, pos_x + 1, pos_y, tar, rep) == 1)
		return (1);
	if (flood_fill(cub3d, pos_x - 1, pos_y, tar, rep) == 1)
		return (1);
	if (flood_fill(cub3d, pos_x, pos_y + 1, tar, rep) == 1)
		return (1);
	if (flood_fill(cub3d, pos_x, pos_y - 1, tar, rep) == 1)
		return (1);
	return (0);
}
