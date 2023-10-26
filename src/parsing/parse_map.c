#include "cub3d.h"

// static void print_array(char **arr);
// static void print_array(char **arr)
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

bool	parse_map(t_cub3d *cub3d)
{
	if (!validate_values(cub3d->map_str))
		return (false);
	cub3d->arr = ft_split(cub3d->map_str, '\n');
	if (!get_dimensions(cub3d->arr, cub3d))
		return(perror("no start position found\n"), false);
	if (flood_fill(cub3d, cub3d->st_pos.x_pos, cub3d->st_pos.y_pos, '0', 'c'))
		return(perror("invalid map\n"), false);
	flood_fill(cub3d, cub3d->st_pos.x_pos, cub3d->st_pos.y_pos, 'c', '0');
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
	if (cub3d->arr[pos_y][pos_x] == wall || cub3d->arr[pos_y][pos_x] == rep)
		return (0);
	else if (cub3d->arr[pos_y][pos_x] != cub3d->st_pos.dir && cub3d->arr[pos_y][pos_x] != tar)
		return (1);
	cub3d->arr[pos_y][pos_x] = rep;
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
