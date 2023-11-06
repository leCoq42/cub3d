#include "cub3d.h"

bool	parse_map(t_cub3d *cub3d)
{
	if (!validate_values(cub3d->map_str))
		return (false);
	cub3d->char_arr = ft_split(cub3d->map_str, '\n');
	if (!cub3d->char_arr)
		return (false);
	if (!get_dimensions(cub3d->char_arr, cub3d))
		return (perror("Error\nno start position found"), false);
	if (flood_fill_check(cub3d, cub3d->st_pos.x_pos, cub3d->st_pos.y_pos, '0'))
		return (perror("Error\ninvalid map"), false);
	flood_fill_repair(cub3d, cub3d->st_pos.x_pos, cub3d->st_pos.y_pos, 'c');
	create_int_arr(cub3d);
	fill_int_arr(cub3d);
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
				return (perror("Error\ntoo many start positions"), false);
			i++;
		}
		else if (str[i] == '\0')
			break ;
		else
			return (perror("Error\ninvalid start position"), false);
	}
	if (flag == 1)
		return (true);
	return (false);
}

bool	create_int_arr(t_cub3d *cub3d)
{
	int		**int_arr;
	size_t	i;

	int_arr = malloc(cub3d->map_height * sizeof(int *));
	if (!int_arr)
		return (false);
	i = 0;
	while (i < cub3d->map_height)
	{
		int_arr[i] = malloc(cub3d->map_width * sizeof(int));
		if (!int_arr[i])
			return (false);
		i++;
	}
	cub3d->int_arr = int_arr;
	return (true);
}

bool	fill_int_arr(t_cub3d *cub3d)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < cub3d->map_height)
	{
		j = 0;
		while (j < cub3d->map_width && cub3d->char_arr[i][j] != '\0')
		{
			if (cub3d->char_arr[i][j] == '0')
				cub3d->int_arr[i][j] = 0;
			else
				cub3d->int_arr[i][j] = 1;
			j++;
		}
		i++;
	}
	return (true);
}
