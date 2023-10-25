#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_cub3d	*cub3d;

	if (argc != 2)
		exit(0);
	cub3d = parse_file(argv[1]);
	// mlx_start(map);
	// clean_up_arr(map->points, map);
	free(cub3d);
	return (0);
}
