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
		return (ft_putstr_fd("Error\n", STDERR_FILENO), -1);
	x = ft_strlen(map_name) - 4;
	if (ft_strncmp(&map_name[x], ".cub", 5) != 0)
		return (ft_putstr_fd("Error\n", STDERR_FILENO), -1);
	return (open(map_name, O_RDONLY));
}

char	*strjoin_free(char *s1, char *s2)
{
	char			*mem;
	const size_t	s1len = gnl_strlen(s1);
	const size_t	s2len = gnl_strlen(s2);

	mem = (char *)malloc((s1len + s2len + 1) * sizeof(char));
	if (!mem)
		return (free(s1), free(s2), NULL);
	gnl_memcpy(mem, s1, s1len);
	gnl_memcpy(mem + s1len, s2, s2len + 1);
	if (ft_strncmp(s1, "", 1) != 0)
		free(s1);
	return (free(s2), mem);
}
