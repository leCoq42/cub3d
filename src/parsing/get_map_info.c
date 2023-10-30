#include "cub3d.h"

bool	get_dimensions(char **arr, t_cub3d *cub3d)
{
	size_t	x;
	size_t	y;

	y = 0;
	cub3d->map_width = 0;
	while (arr[y] != NULL)
	{
		x = 0;
		while (arr[y][x] != '\0')
		{
			if (is_present("NESW", arr[y][x]))
			{
				cub3d->st_pos.x_pos = x;
				cub3d->st_pos.y_pos = y;
				cub3d->st_pos.dir = arr[y][x];
			}
			x++;
		}
		if (x > cub3d->map_width)
			cub3d->map_width = x;
		y++;
	}
	cub3d->map_height = y;
	if (cub3d->st_pos.dir != 0)
		return (true);
	return (false);
}

// bool find_start_pos(char **arr, t_cub3d *cub3d)
// {
// 	for (int i = 0; arr[i] != NULL; i++)
// 	{
// 		for (int j = 0; arr[i][j] != '\0'; j++)
// 		{
// 			if (is_present("NESW", arr[i][j]))
// 			{
// 				cub3d->st_pos.x_pos = i;
// 				cub3d->st_pos.y_pos = j;
// 				cub3d->st_pos.dir = arr[i][j];
// 				return (true);
// 			}
// 		}
// 	}
// 	return(false);
// }