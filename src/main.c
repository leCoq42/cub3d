#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_map	*map;

	if (argc != 2)
		exit(0);
	map = parse_map(argv[1]);
	// mlx_start(map);
	// clean_up_arr(map->points, map);
	free(map);
	return (0);
}
