#include "cub3d.h"

t_cub3d *parse_file(char *filename)
{
	int		fd;
	t_cub3d *cub3d;

	fd = check_filename(filename);
	if (fd < 0)
		exit(EXIT_FAILURE);
	cub3d = ft_calloc(1, sizeof(t_cub3d));
	if (!cub3d)
		exit(EXIT_FAILURE);
	if (!parse_header(fd, cub3d))
		return (NULL);
	parse_map(cub3d);
	return(cub3d);
	// file_to_llist(fd, map);
	// llist_to_arr(map);
	// close(fd);
	// return(map);
}