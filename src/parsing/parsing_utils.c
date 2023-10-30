#include "cub3d.h"

void	skip_chars(char *str, size_t *i, char *set)
{
	while (is_present(set, str[*i]))
		(*i)++;
}

bool	is_present(char *set, char c)
{
	while (*set != '\0')
	{
		if (*set == c)
			return (true);
		set++;
	}
	return (false);
}

int	check_filename(char *map_name)
{
	int	x;

	if (ft_strlen(map_name) < 4)
		exit(0);
	x = ft_strlen(map_name) - 4;
	if (ft_strncmp(&map_name[x], ".cub", 5) != 0)
		exit(0);
	return (open(map_name, O_RDONLY));
}

// void	check_values(char *line, const char *allowed_values)
// {
// 	size_t	i;

// 	i = 0;
// 	while (line[i])
// 	{
// 		if (ft_strchr(allowed_values, line[i]) == NULL)
// 			exit(0);
// 		i++;
// 	}
// }