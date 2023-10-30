#include "cub3d.h"

// static size_t	strlen(const char *s);
// static char	*strjoin(char const *s1, char const *s2);

bool	parse_header(int fd, t_cub3d *cub3d)
{
	size_t	i;
	int		count;
	char	*file_str;

	file_str = file_to_str(fd);
	close(fd);
	i = 0;
	count = 0;
	while (count < 6)
	{
		skip_chars(file_str, &i, " \n");
		if (is_identifier(&file_str[i]))
		{
			if (!extract_info(file_str, &i, cub3d))
				return (false);
		}
		else
			return (perror("invalid map info\n"), false);
		count++;
	}
	// printf("floor = %u \n", cub3d->f_col);
	// printf("ceiling = %u \n", cub3d->c_col);
	if (info_is_valid(cub3d, &i, file_str))
		return (true);
	return (false); // one of the 6 headers is not filled
}

bool	info_is_valid(t_cub3d *cub3d, size_t *i, char *file_str)
{
	if (cub3d->c_col != 0 && cub3d->f_col != 0)
	{
		if (cub3d->textures[0] != 0 && cub3d->textures[1] != 0 \
			&& cub3d->textures[2] != 0 && cub3d->textures[3] != 0)
			{
				skip_chars(file_str, i, "\n");
				cub3d->map_str = &file_str[*i];
				// printf("file_str = \n%s \n", &file_str[*i]);
				return (true);
			}
	}
	return (false);
}

bool	extract_info(char *file_str, size_t *i, t_cub3d *cub3d)
{
	char c;

	if (file_str[*i] == 'C' || file_str[*i] == 'F')
	{
		c = file_str[*i];
		(*i)++; 
		if (!get_color_header(file_str, cub3d, c, i))
			return (false);
	}
	else if (is_present("NESW", file_str[*i]))
	{
		c = file_str[*i];
		(*i) += 2;
		if (!get_texture(file_str, cub3d, c, i))
			return (false);
	}
	return (true);
}

char	*file_to_str(int fd)
{
	char *file_str;
	char *new_str;
	new_str = get_next_line(fd);
	file_str = "";
	while (new_str)
	{
		file_str = ft_strjoin(file_str, new_str);
		new_str = get_next_line(fd); 
	}
	return (file_str);
}

bool	is_identifier(char *str)
{
	if (ft_strncmp(str, "C ", 2) == 0)
		return (true);
	else if (ft_strncmp(str, "F ", 2) == 0)
		return (true);
	else if (ft_strncmp(str, "NO ", 3) == 0)
		return (true);
	else if (ft_strncmp(str, "EA ", 3) == 0)
		return (true);
	else if (ft_strncmp(str, "SO ", 3) == 0)
		return (true);
	else if (ft_strncmp(str, "WE ", 3) == 0)
		return (true);
	return (false);
}
